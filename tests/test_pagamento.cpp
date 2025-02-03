#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Pagamento.hpp"

// Mock para Locacao
class MockLocacao : public Locacao {
public:
    MOCK_METHOD(Filme, getFilme, (), (const, override));
    MOCK_METHOD(int, calcularDiasAtraso, (const std::string&), (const, override));
};

// Mock para Filme
class MockFilme : public Filme {
public:
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Teste para PagamentoDinheiro
TEST(PagamentoDinheiroTest, PagamentoSuficiente) {
    MockLocacao locacao;
    MockFilme filme;
    EXPECT_CALL(filme, getPreco()).WillRepeatedly(testing::Return(50.0));
    EXPECT_CALL(locacao, getFilme()).WillRepeatedly(testing::Return(filme));

    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;

    // Simular entrada do usuário (pagamento correto)
    std::istringstream input("50.0\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para PagamentoCartaoCredito
TEST(PagamentoCartaoCreditoTest, PagamentoBemSucedido) {
    MockLocacao locacao;
    MockFilme filme;
    EXPECT_CALL(filme, getPreco()).WillRepeatedly(testing::Return(100.0));
    EXPECT_CALL(locacao, getFilme()).WillRepeatedly(testing::Return(filme));

    PagamentoCartaoCredito pagamento;
    bool pagamentoRealizado = false;
    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    
    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para PagamentoPix
TEST(PagamentoPixTest, PagamentoBemSucedido) {
    MockLocacao locacao;
    MockFilme filme;
    EXPECT_CALL(filme, getPreco()).WillRepeatedly(testing::Return(30.0));
    EXPECT_CALL(locacao, getFilme()).WillRepeatedly(testing::Return(filme));

    PagamentoPix pagamento;
    bool pagamentoRealizado = false;
    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    
    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para Multa
TEST(MultaTest, CalculaMultaCorretamente) {
    MockLocacao locacao;
    MockFilme filme;
    
    EXPECT_CALL(filme, getPreco()).WillRepeatedly(testing::Return(100.0));
    EXPECT_CALL(locacao, getFilme()).WillRepeatedly(testing::Return(filme));
    EXPECT_CALL(locacao, calcularDiasAtraso(testing::_)).WillRepeatedly(testing::Return(5));

    double multa = Multa::calcularMulta(locacao, 2);
    EXPECT_GT(multa, 0.0);  // A multa deve ser maior que zero
}
