#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Locacoes.hpp"

// Mock para a classe Filme
class MockFilme : public Filme {
public:
    MockFilme() : Filme("Mock Filme", {"Aventura"}, 12, 2023, 10.0) {}
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Mock para a classe Pessoa
class MockPessoa : public Pessoa {
public:
    MockPessoa() : Pessoa("Mock Cliente", 25) {}
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

TEST(LocacaoTest, CriacaoLocacao) {
    MockPessoa cliente;
    MockFilme filme;
    
    EXPECT_CALL(cliente, getNome()).WillOnce(testing::Return("Mock Cliente"));
    EXPECT_CALL(filme, getPreco()).WillOnce(testing::Return(10.0));
    
    Locacao locacao(cliente, filme, "2024-01-01", "2024-01-07");
    
    EXPECT_EQ(locacao.getCliente().getNome(), "Mock Cliente");
    EXPECT_EQ(locacao.getFilme().getTitulo(), "Mock Filme");
    EXPECT_EQ(locacao.getDataLocacao(), "2024-01-01");
    EXPECT_EQ(locacao.getDataDevolucao(), "2024-01-07");
    EXPECT_EQ(locacao.getPreco(), 10.0);
}

TEST(LocacaoTest, CalcularDiasAtraso) {
    MockPessoa cliente;
    MockFilme filme;
    Locacao locacao(cliente, filme, "2024-01-01", "2024-01-07");
    
    EXPECT_EQ(locacao.calcularDiasAtraso("2024-01-08"), 1);
    EXPECT_EQ(locacao.calcularDiasAtraso("2024-01-10"), 3);
    EXPECT_EQ(locacao.calcularDiasAtraso("2024-01-07"), 0);
}

TEST(LocacaoTest, ExibirInformacoes) {
    MockPessoa cliente;
    MockFilme filme;
    
    EXPECT_CALL(cliente, getNome()).WillRepeatedly(testing::Return("Mock Cliente"));
    EXPECT_CALL(filme, getTitulo()).WillRepeatedly(testing::Return("Mock Filme"));
    EXPECT_CALL(filme, getPreco()).WillRepeatedly(testing::Return(10.0));
    
    Locacao locacao(cliente, filme, "2024-01-01", "2024-01-07");
    
    testing::internal::CaptureStdout();
    locacao.exibirInformacoes();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_THAT(output, testing::HasSubstr("Mock Cliente"));
    EXPECT_THAT(output, testing::HasSubstr("Mock Filme"));
    EXPECT_THAT(output, testing::HasSubstr("2024-01-01"));
    EXPECT_THAT(output, testing::HasSubstr("2024-01-07"));
    EXPECT_THAT(output, testing::HasSubstr("R$ 10.0"));
}
