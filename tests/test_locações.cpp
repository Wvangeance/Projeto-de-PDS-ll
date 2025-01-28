#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Locações.hpp"
#include "Cliente.hpp"
#include "Filmes.hpp"

using ::testing::NiceMock;
using ::testing::Return;

// Mock das classes Pessoa e Filme para isolar os testes da lógica de Locacao
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

class MockFilme : public Filme {
public:
    MockFilme() : Filme("Mock", {"Ação"}, 12, 2022, 15.0) {}
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Testes para a classe Locacao
TEST(LocacaoTest, ConstrutorPadrao) {
    Locacao locacao;
    EXPECT_EQ(locacao.getDataLocacao(), "");
    EXPECT_EQ(locacao.getDataDevolucao(), "");
}

TEST(LocacaoTest, ConstrutorParametrizado) {
    MockPessoa cliente;
    MockFilme filme;

    EXPECT_CALL(cliente, getNome()).WillOnce(Return("Cliente Teste"));
    EXPECT_CALL(filme, getTitulo()).WillOnce(Return("Filme Teste"));
    EXPECT_CALL(filme, getPreco()).WillOnce(Return(15.0));

    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(locacao.getCliente().getNome(), "Cliente Teste");
    EXPECT_EQ(locacao.getFilme().getTitulo(), "Filme Teste");
    EXPECT_EQ(locacao.getDataLocacao(), "2023-01-01");
    EXPECT_EQ(locacao.getDataDevolucao(), "2023-01-10");
}

TEST(LocacaoTest, CalcularDiasAtrasoSemAtraso) {
    MockPessoa cliente;
    MockFilme filme;
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(locacao.calcularDiasAtraso("2023-01-09"), 0);
}

TEST(LocacaoTest, CalcularDiasAtrasoComAtraso) {
    MockPessoa cliente;
    MockFilme filme;
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(locacao.calcularDiasAtraso("2023-01-15"), 5);
}

TEST(LocacaoTest, CalcularDiasAtrasoDataInvalida) {
    MockPessoa cliente;
    MockFilme filme;
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_THROW(locacao.calcularDiasAtraso("2023-32-01"), std::invalid_argument);
}

TEST(LocacaoTest, ExibirInformacoes) {
    MockPessoa cliente;
    MockFilme filme;

    EXPECT_CALL(cliente, getNome()).WillOnce(Return("Cliente Teste"));
    EXPECT_CALL(filme, getTitulo()).WillOnce(Return("Filme Teste"));
    EXPECT_CALL(filme, getPreco()).WillOnce(Return(15.0));

    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    std::ostringstream saida;
    std::streambuf* coutBuffer = std::cout.rdbuf();
    std::cout.rdbuf(saida.rdbuf());

    locacao.exibirInformacoes();

    std::cout.rdbuf(coutBuffer);

    std::string esperado = "Cliente: Cliente Teste\nFilme: Filme Teste\nData de Locação: 2023-01-01\nData de Devolução: 2023-01-10\nPreço da Locação: R$ 15\n";
    EXPECT_EQ(saida.str(), esperado);
}

