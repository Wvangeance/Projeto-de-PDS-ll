#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Promocao.hpp"

// Criamos um mock para a classe Pessoa
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(int, getId, (), (const, override));
};

TEST(PromocaoTest, AplicarDesconto_MultiploDe10) {
    MockPessoa cliente;
    EXPECT_CALL(cliente, getId()).WillOnce(::testing::Return(20)); // ID múltiplo de 10
    
    double precoOriginal = 100.0;
    double precoComDesconto = Promocao::aplicarDesconto(cliente, precoOriginal);
    
    EXPECT_DOUBLE_EQ(precoComDesconto, 90.0); // 10% de desconto
}

TEST(PromocaoTest, AplicarDesconto_UltimoDigito) {
    MockPessoa cliente;
    EXPECT_CALL(cliente, getId()).WillOnce(::testing::Return(23)); // Último dígito = 3
    
    double precoOriginal = 200.0;
    double precoComDesconto = Promocao::aplicarDesconto(cliente, precoOriginal);
    
    EXPECT_DOUBLE_EQ(precoComDesconto, 194.0); // 3% de desconto
}

TEST(PromocaoTest, CalcularDesconto_MultiploDe10) {
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(30), 10.0);
}

TEST(PromocaoTest, CalcularDesconto_UltimoDigito) {
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(47), 7.0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
