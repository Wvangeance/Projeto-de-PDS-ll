#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Pagamento.hpp"
#include "Locações.hpp"
#include "Cliente.hpp"
#include "Filmes.hpp"

using ::testing::NiceMock;
using ::testing::Return;

// Mock para Locacao, que será usado nos testes
class MockLocacao : public Locacao {
public:
    MOCK_METHOD(int, calcularDiasAtraso, (const std::string& dataAtual), (const, override));
};

// Teste para a classe PagamentoDinheiro
TEST(PagamentoTest, PagamentoDinheiro_ComTroco) {
    Filme filme("Filme Teste", {"Ação"}, 12, 2023, 15.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;

    // Simula o input do usuário para o pagamento
    std::istringstream input("20\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

TEST(PagamentoTest, PagamentoDinheiro_SemTroco) {
    Filme filme("Filme Teste", {"Ação"}, 12, 2023, 15.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;

    // Simula o input do usuário para o pagamento
    std::istringstream input("15\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

TEST(PagamentoTest, PagamentoDinheiro_ValorInsuficiente) {
    Filme filme("Filme Teste", {"Ação"}, 12, 2023, 15.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;

    // Simula o input do usuário para o pagamento
    std::istringstream input("10\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_FALSE(pagamentoRealizado);
}

// Teste para PagamentoCartaoCredito
TEST(PagamentoTest, PagamentoCartaoCredito) {
    Filme filme("Filme Teste", {"Comédia"}, 12, 2023, 20.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoCartaoCredito pagamento;
    bool pagamentoRealizado = false;

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para PagamentoCartaoDebito
TEST(PagamentoTest, PagamentoCartaoDebito) {
    Filme filme("Filme Teste", {"Drama"}, 12, 2023, 25.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoCartaoDebito pagamento;
    bool pagamentoRealizado = false;

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para PagamentoPix
TEST(PagamentoTest, PagamentoPix) {
    Filme filme("Filme Teste", {"Terror"}, 12, 2023, 30.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoPix pagamento;
    bool pagamentoRealizado = false;

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

// Teste para PagamentoEscambo
TEST(PagamentoTest, PagamentoEscambo_Aceito) {
    Filme filme("Filme Teste", {"Fantasia"}, 12, 2023, 50.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoEscambo pagamento;
    bool pagamentoRealizado = false;

    // Simula o input do usuário para aceitar o escambo
    std::istringstream input("S\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_TRUE(pagamentoRealizado);
}

TEST(PagamentoTest, PagamentoEscambo_Rejeitado) {
    Filme filme("Filme Teste", {"Fantasia"}, 12, 2023, 50.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    PagamentoEscambo pagamento;
    bool pagamentoRealizado = false;

    // Simula o input do usuário para rejeitar o escambo
    std::istringstream input("N\n");
    std::cin.rdbuf(input.rdbuf());

    pagamento.realizarPagamento(locacao, pagamentoRealizado);

    EXPECT_FALSE(pagamentoRealizado);
}

// Teste para Multa
TEST(MultaTest, CalculoMulta_SemAtraso) {
    Filme filme("Filme Teste", {"Ação"}, 12, 2023, 15.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(Multa::calcularMulta(locacao, 5), 0.0);
}

TEST(MultaTest, CalculoMulta_ComAtraso) {
    Filme filme("Filme Teste", {"Ação"}, 12, 2023, 15.0);
    Pessoa cliente("Cliente Teste", "12345678900");
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-05");

    MockLocacao mockLocacao;
    EXPECT_CALL(mockLocacao, calcularDiasAtraso(testing::_))
        .WillOnce(Return(7)); // Simula 7 dias de atraso

    double multa = Multa::calcularMulta(mockLocacao, 5);
    EXPECT_GT(multa, 0.0);
    EXPECT_LE(multa, filme.getPreco());
}