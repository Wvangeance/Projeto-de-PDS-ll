#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Promocao.hpp"

// Mock para Pessoa (Cliente)
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(int, getId, (), (const, override));
};

// Teste para calcularDesconto
TEST(PromocaoTest, CalculaDesconto_CasoMultiploDe10) {
    EXPECT_EQ(Promocao::calcularDesconto(10), 10.0);
    EXPECT_EQ(Promocao::calcularDesconto(20), 10.0);
    EXPECT_EQ(Promocao::calcularDesconto(30), 10.0);
}

TEST(PromocaoTest, CalculaDesconto_CasoNaoMultiploDe10) {
    EXPECT_EQ(Promocao::calcularDesconto(11), 1.0);
    EXPECT_EQ(Promocao::calcularDesconto(25), 5.0);
    EXPECT_EQ(Promocao::calcularDesconto(37), 7.0);
}

// Teste para aplicarDesconto
TEST(PromocaoTest, AplicaDesconto_CasoMultiploDe10) {
    MockPessoa cliente;
    EXPECT_CALL(cliente, getId()).WillRepeatedly(testing::Return(20));

    double precoOriginal = 100.0;
    double precoComDesconto = Promocao::aplicarDesconto(cliente, precoOriginal);

    EXPECT_DOUBLE_EQ(precoComDesconto, 90.0); // 10% de desconto
}

TEST(PromocaoTest, AplicaDesconto_CasoNaoMultiploDe10) {
    MockPessoa cliente;
    EXPECT_CALL(cliente, getId()).WillRepeatedly(testing::Return(23));

    double precoOriginal = 200.0;
    double precoComDesconto = Promocao::aplicarDesconto(cliente, precoOriginal);

    EXPECT_DOUBLE_EQ(precoComDesconto, 154.0); // 23% de desconto
}

