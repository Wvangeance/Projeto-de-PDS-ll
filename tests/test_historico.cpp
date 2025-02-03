#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Historico.hpp"
#include <sstream>

using ::testing::_;
using ::testing::Return;

// Mock para capturar saída padrão
class MockHistorico : public Historico {
public:
    MOCK_METHOD(void, adicionarRegistro, (const std::string&), (override));
    MOCK_METHOD(void, exibirHistorico, (), (const, override));
};

// Teste da adição de registros
TEST(HistoricoTest, AdicionarRegistro) {
    Historico historico;
    historico.adicionarRegistro("Locação: Matrix - 10/01/2024");
    historico.adicionarRegistro("Pagamento: R$ 19.99 - 11/01/2024");

    testing::internal::CaptureStdout();
    historico.exibirHistorico();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Locação: Matrix - 10/01/2024") != std::string::npos);
    EXPECT_TRUE(output.find("Pagamento: R$ 19.99 - 11/01/2024") != std::string::npos);
}

// Teste de histórico vazio
TEST(HistoricoTest, HistoricoVazio) {
    Historico historico;
    
    testing::internal::CaptureStdout();
    historico.exibirHistorico();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Nenhum registro encontrado.") != std::string::npos);
}

// Teste de mock para exibir histórico
TEST(HistoricoTest, MockExibirHistorico) {
    MockHistorico mockHistorico;

    EXPECT_CALL(mockHistorico, exibirHistorico()).Times(1);

    mockHistorico.exibirHistorico();
}
