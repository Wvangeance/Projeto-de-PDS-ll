#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Locacoes.hpp"
#include <sstream>

using ::testing::Return;
using ::testing::AtLeast;

// Mock para a classe Pessoa
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

// Mock para a classe Filme
class MockFilme : public Filme {
public:
    MockFilme() : Filme("MockTitle", {"Ação"}, 12, 2020, 15.0) {}
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Teste para calcular dias de atraso
TEST(LocacaoTest, CalcularDiasAtrasoSemAtraso) {
    Pessoa cliente;
    Filme filme("Matrix", {"Ação", "Ficção"}, 16, 1999, 10.0);
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(locacao.calcularDiasAtraso("2023-01-09"), 0);  // Antes da devolução
    EXPECT_EQ(locacao.calcularDiasAtraso("2023-01-10"), 0);  // No dia da devolução
}

TEST(LocacaoTest, CalcularDiasAtrasoComAtraso) {
    Pessoa cliente;
    Filme filme("Matrix", {"Ação", "Ficção"}, 16, 1999, 10.0);
    Locacao locacao(cliente, filme, "2023-01-01", "2023-01-10");

    EXPECT_EQ(locacao.calcularDiasAtraso("2023-01-12"), 2);  // 2 dias de atraso
}

// Teste para verificar exibição de informações usando mocks
TEST(LocacaoTest, ExibirInformacoesComMock) {
    MockPessoa mockCliente;
    MockFilme mockFilme;

    EXPECT_CALL(mockCliente, getNome())
        .Times(AtLeast(1))
        .WillRepeatedly(Return("João Mock"));

    EXPECT_CALL(mockFilme, getTitulo())
        .Times(AtLeast(1))
        .WillRepeatedly(Return("Mock Movie"));

    EXPECT_CALL(mockFilme, getPreco())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(25.0));

    Locacao locacao(mockCliente, mockFilme, "2023-01-01", "2023-01-10");

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    locacao.exibirInformacoes();

    std::cout.rdbuf(oldCout); // Restaurar std::cout

    std::string esperado = 
        "Cliente: João Mock\n"
        "Filme: Mock Movie\n"
        "Data de Locação: 2023-01-01\n"
        "Data de Devolução: 2023-01-10\n"
        "Preço da Locação: R$ 25\n";

    EXPECT_EQ(buffer.str(), esperado);
}

// Função principal para rodar os testes
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
