#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Historico.hpp"
#include <sstream>

using ::testing::Return;
using ::testing::AtLeast;

// Mock da classe Historico
class MockHistorico : public Historico {
public:
    MOCK_METHOD(void, adicionarRegistro, (const std::string& registro), (override));
    MOCK_METHOD(void, exibirHistorico, (), (const, override));
};

// Teste para verificar a adição de um registro
TEST(HistoricoTest, AdicionarRegistroTest) {
    Historico historico;
    historico.adicionarRegistro("Cliente João alugou Matrix");
    
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());
    
    historico.exibirHistorico();

    std::cout.rdbuf(oldCout); // Restaurar std::cout

    std::string esperado = "===== Histórico de Locações e Pagamentos =====\nCliente João alugou Matrix\n";
    EXPECT_EQ(buffer.str(), esperado);
}

// Teste para verificar exibição de histórico vazio
TEST(HistoricoTest, ExibirHistoricoVazioTest) {
    Historico historico;
    
    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    historico.exibirHistorico();

    std::cout.rdbuf(oldCout); // Restaurar std::cout

    std::string esperado = "===== Histórico de Locações e Pagamentos =====\nNenhum registro encontrado.\n";
    EXPECT_EQ(buffer.str(), esperado);
}

// Teste usando Mock para garantir que os métodos são chamados
TEST(HistoricoTest, MockAdicionarRegistro) {
    MockHistorico mockHistorico;
    
    EXPECT_CALL(mockHistorico, adicionarRegistro("Teste de Mock"))
        .Times(AtLeast(1));

    mockHistorico.adicionarRegistro("Teste de Mock");
}

TEST(HistoricoTest, MockExibirHistorico) {
    MockHistorico mockHistorico;

    EXPECT_CALL(mockHistorico, exibirHistorico())
        .Times(AtLeast(1));

    mockHistorico.exibirHistorico();
}

// Função principal para rodar os testes
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
