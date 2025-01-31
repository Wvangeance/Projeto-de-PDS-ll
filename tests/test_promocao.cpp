#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Promocao.hpp"

// Mock da classe Pessoa
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(int, getId, (), (const, override));  // Mock para o método getId()
    MOCK_METHOD(std::string, getNome, (), (const, override)); // Mock para o método getNome()
};

// Teste de aplicação de desconto com mock
TEST(PromocaoTest, TesteAplicarDescontoComMock) {
    MockPessoa clienteMock1;
    EXPECT_CALL(clienteMock1, getId())
        .WillOnce(testing::Return(10));  // Retorna ID 10 para o cliente 1
    double precoOriginal = 100.0;
    double precoComDesconto = Promocao::aplicarDesconto(clienteMock1, precoOriginal);
    EXPECT_DOUBLE_EQ(precoComDesconto, 90.0);  // Espera-se 10% de desconto
    
    MockPessoa clienteMock2;
    EXPECT_CALL(clienteMock2, getId())
        .WillOnce(testing::Return(5));   // Retorna ID 5 para o cliente 2
    precoComDesconto = Promocao::aplicarDesconto(clienteMock2, precoOriginal);
    EXPECT_DOUBLE_EQ(precoComDesconto, 95.0);  // Espera-se 5% de desconto
}

// Teste de cálculo de desconto com mock
TEST(PromocaoTest, TesteCalcularDescontoComMock) {
    // Mock de clientes para testar o cálculo do desconto
    MockPessoa clienteMock1;
    EXPECT_CALL(clienteMock1, getId())
        .WillOnce(testing::Return(10));  // ID múltiplo de 10
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(clienteMock1.getId()), 10.0);  // Espera-se 10%

    MockPessoa clienteMock2;
    EXPECT_CALL(clienteMock2, getId())
        .WillOnce(testing::Return(5));   // ID terminando em 5
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(clienteMock2.getId()), 5.0);   // Espera-se 5%

    MockPessoa clienteMock3;
    EXPECT_CALL(clienteMock3, getId())
        .WillOnce(testing::Return(23));  // ID terminando em 3
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(clienteMock3.getId()), 3.0);  // Espera-se 3%

    MockPessoa clienteMock4;
    EXPECT_CALL(clienteMock4, getId())
        .WillOnce(testing::Return(7));   // ID terminando em 7
    EXPECT_DOUBLE_EQ(Promocao::calcularDesconto(clienteMock4.getId()), 7.0);   // Espera-se 7%
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);  // Inicializa o Google Mock
    return RUN_ALL_TESTS();
}