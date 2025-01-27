#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <utility>
#include "Locações.hpp"
#include "Cliente.hpp"
#include "Filmes.hpp"

// Mock para Cliente
class MockCliente : public Pessoa {
public:
    MOCK_METHOD(std::string, getNome, (), (const));
    MOCK_METHOD(std::string, getCPF, (), (const));
};

// Mock para Filme
class MockFilme : public Filme {
public:
    MOCK_METHOD(std::string, getTitulo, (), (const));
    MOCK_METHOD(std::string, getGenero, (), (const));
    MOCK_METHOD(int, getDuracao, (), (const));
};

// Testes para a classe Locacao
TEST(LocacaoTest, ConstrutorPadrao) {
    Locacao locacao;
    EXPECT_EQ(locacao.getDataLocacao(), "");
    EXPECT_EQ(locacao.getDataDevolucao(), "");
}

TEST(LocacaoTest, ConstrutorParametrizado) {
    MockCliente cliente;
    MockFilme filme;

    EXPECT_CALL(cliente, getNome()).WillRepeatedly(::testing::Return("Joao"));
    EXPECT_CALL(cliente, getCPF()).WillRepeatedly(::testing::Return("12345678900"));

    EXPECT_CALL(filme, getTitulo()).WillRepeatedly(::testing::Return("Matrix"));
    EXPECT_CALL(filme, getGenero()).WillRepeatedly(::testing::Return("Ficcao"));
    EXPECT_CALL(filme, getDuracao()).WillRepeatedly(::testing::Return(120));

    Locacao locacao(cliente, filme, "2025-01-01", "2025-01-10");

    EXPECT_EQ(locacao.getDataLocacao(), "2025-01-01");
    EXPECT_EQ(locacao.getDataDevolucao(), "2025-01-10");
}

TEST(LocacaoTest, SettersAndGetters) {
    MockCliente cliente;
    MockFilme filme;

    EXPECT_CALL(cliente, getNome()).WillRepeatedly(::testing::Return("Ana"));
    EXPECT_CALL(cliente, getCPF()).WillRepeatedly(::testing::Return("09876543211"));

    EXPECT_CALL(filme, getTitulo()).WillRepeatedly(::testing::Return("Inception"));
    EXPECT_CALL(filme, getGenero()).WillRepeatedly(::testing::Return("Aventura"));
    EXPECT_CALL(filme, getDuracao()).WillRepeatedly(::testing::Return(150));

    Locacao locacao;
    locacao.setCliente(cliente);
    locacao.setFilme(filme);
    locacao.setDataLocacao("2025-02-01");
    locacao.setDataDevolucao("2025-02-15");

    EXPECT_EQ(locacao.getDataLocacao(), "2025-02-01");
    EXPECT_EQ(locacao.getDataDevolucao(), "2025-02-15");
}


