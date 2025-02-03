#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Locacoes.hpp"

using ::testing::Return;

// Mock para Pessoa
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(std::string, getNome, (), (const, override));
    MOCK_METHOD(int, getId, (), (const, override));
};

// Mock para Filme
class MockFilme : public Filme {
public:
    MockFilme() : Filme("Mock", {"Mock"}, 0, 2000, 0.0) {}
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Teste do construtor
TEST(LocacaoTest, Construtor) {
    MockPessoa mockCliente;
    MockFilme mockFilme;

    EXPECT_CALL(mockCliente, getNome()).WillRepeatedly(Return("João"));
    EXPECT_CALL(mockFilme, getTitulo()).WillRepeatedly(Return("Matrix"));
    EXPECT_CALL(mockFilme, getPreco()).WillRepeatedly(Return(12.99));

    Locacao locacao(mockCliente, mockFilme, "10-01-2024", "15-01-2024");

    EXPECT_EQ(locacao.getCliente().getNome(), "João");
    EXPECT_EQ(locacao.getFilme().getTitulo(), "Matrix");
    EXPECT_EQ(locacao.getDataLocacao(), "10-01-2024");
    EXPECT_EQ(locacao.getDataDevolucao(), "15-01-2024");
}

// Teste do método getPreco()
TEST(LocacaoTest, GetPreco) {
    MockFilme mockFilme;
    EXPECT_CALL(mockFilme, getPreco()).WillOnce(Return(19.99));

    Locacao locacao(MockPessoa(), mockFilme, "05-01-2024", "10-01-2024");

    EXPECT_DOUBLE_EQ(locacao.getPreco(), 19.99);
}

// Teste do cálculo de atraso (sem atraso)
TEST(LocacaoTest, CalcularDiasAtrasoSemAtraso) {
    Locacao locacao(MockPessoa(), MockFilme(), "05-01-2024", "10-01-2024");
    EXPECT_EQ(locacao.calcularDiasAtraso("09-01-2024"), 0);
}

// Teste do cálculo de atraso (com atraso)
TEST(LocacaoTest, CalcularDiasAtrasoComAtraso) {
    Locacao locacao(MockPessoa(), MockFilme(), "05-01-2024", "10-01-2024");
    EXPECT_EQ(locacao.calcularDiasAtraso("15-01-2024"), 5);
}

// Teste de exibição das informações
TEST(LocacaoTest, ExibirInformacoes) {
    MockPessoa mockCliente;
    MockFilme mockFilme;

    EXPECT_CALL(mockCliente, getNome()).WillRepeatedly(Return("Maria"));
    EXPECT_CALL(mockFilme, getTitulo()).WillRepeatedly(Return("Titanic"));
    EXPECT_CALL(mockFilme, getPreco()).WillRepeatedly(Return(9.99));

    Locacao locacao(mockCliente, mockFilme, "01-02-2024", "06-02-2024");

    testing::internal::CaptureStdout();
    locacao.exibirInformacoes();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Cliente: Maria") != std::string::npos);
    EXPECT_TRUE(output.find("Filme: Titanic") != std::string::npos);
    EXPECT_TRUE(output.find("Data de Locação: 01-02-2024") != std::string::npos);
    EXPECT_TRUE(output.find("Data de Devolução: 06-02-2024") != std::string::npos);
    EXPECT_TRUE(output.find("Preço da Locação: R$ 9.99") != std::string::npos);
}
