#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Pagamento.hpp"

using ::testing::Return;

// Mock para a classe Filme
class MockFilme {
public:
    MOCK_METHOD(double, getPreco, (), (const));
};

// Mock para a classe Locacao
class MockLocacao {
public:
    MOCK_METHOD(MockFilme, getFilme, (), (const));
    MOCK_METHOD(int, calcularDiasAtraso, (const std::string&), (const));
};

TEST(PagamentoTest, PagamentoDinheiro_Sucesso)
{
    MockLocacao locacao;
    MockFilme filme;
    
    EXPECT_CALL(filme, getPreco()).WillOnce(Return(50.0));
    EXPECT_CALL(locacao, getFilme()).WillOnce(Return(filme));
    
    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;
    
    // Simular entrada padrão
    std::istringstream input("50.0\n");
    std::cin.rdbuf(input.rdbuf());
    
    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    EXPECT_TRUE(pagamentoRealizado);
}

TEST(PagamentoTest, PagamentoCartaoCredito_Sucesso)
{
    MockLocacao locacao;
    MockFilme filme;
    
    EXPECT_CALL(filme, getPreco()).WillOnce(Return(100.0));
    EXPECT_CALL(locacao, getFilme()).WillOnce(Return(filme));
    
    PagamentoCartaoCredito pagamento;
    bool pagamentoRealizado = false;
    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    
    EXPECT_TRUE(pagamentoRealizado);
}

TEST(PagamentoTest, Multa_CalculoCorreto)
{
    MockLocacao locacao;
    MockFilme filme;
    
    EXPECT_CALL(filme, getPreco()).WillOnce(Return(200.0));
    EXPECT_CALL(locacao, getFilme()).WillOnce(Return(filme));
    EXPECT_CALL(locacao, calcularDiasAtraso(testing::_)).WillOnce(Return(5));
    
    double multa = Multa::calcularMulta(locacao, 2);
    EXPECT_GT(multa, 0.0);
}