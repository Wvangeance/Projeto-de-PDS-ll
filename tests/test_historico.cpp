#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Historico.hpp"
#include <sstream>

// Mock para std::ostream
class MockOstream : public std::ostream {
public:
    MOCK_METHOD(void, write, (const char* s, std::streamsize n), (override));
};

// Teste para adicionar registros ao histórico com mock
TEST(HistoricoTest, TesteAdicionarRegistroComMock) {
    Historico historico;
    
    // Adicionando registros
    historico.adicionarRegistro("Locação de filme: Aventura");
    historico.adicionarRegistro("Pagamento realizado: $10");

    // Mock do ostream
    MockOstream mockOstream;
    
    // Expectation para verificar se a função write é chamada corretamente
    EXPECT_CALL(mockOstream, write(testing::Contains("Locação de filme: Aventura"), testing::_));
    EXPECT_CALL(mockOstream, write(testing::Contains("Pagamento realizado: $10"), testing::_));

    // Redireciona o cout para o mock
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(&mockOstream); 

    historico.exibirHistorico();

    // Restaura o fluxo de saída padrão
    std::cout.rdbuf(cout_backup);
}

// Teste para exibir histórico vazio com mock
TEST(HistoricoTest, TesteExibirHistoricoVazioComMock) {
    Historico historico;

    // Mock do ostream
    MockOstream mockOstream;

    // Expectation para verificar se a função write é chamada com a mensagem de "Nenhum registro encontrado"
    EXPECT_CALL(mockOstream, write(testing::Contains("Nenhum registro encontrado."), testing::_));

    // Redireciona o cout para o mock
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(&mockOstream);

    historico.exibirHistorico();

    // Restaura o fluxo de saída padrão
    std::cout.rdbuf(cout_backup);
}

// Teste para adicionar e exibir múltiplos registros com mock
TEST(HistoricoTest, TesteAdicionarVariosRegistrosComMock) {
    Historico historico;

    // Adicionando múltiplos registros
    historico.adicionarRegistro("Locação de filme: Drama");
    historico.adicionarRegistro("Pagamento realizado: $15");
    historico.adicionarRegistro("Locação de filme: Comédia");

    // Mock do ostream
    MockOstream mockOstream;

    // Expectations para verificar se a função write é chamada corretamente
    EXPECT_CALL(mockOstream, write(testing::Contains("Locação de filme: Drama"), testing::_));
    EXPECT_CALL(mockOstream, write(testing::Contains("Pagamento realizado: $15"), testing::_));
    EXPECT_CALL(mockOstream, write(testing::Contains("Locação de filme: Comédia"), testing::_));

    // Redireciona o cout para o mock
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(&mockOstream);

    historico.exibirHistorico();

    // Restaura o fluxo de saída padrão
    std::cout.rdbuf(cout_backup);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);  // Inicializa o Google Mock
    return RUN_ALL_TESTS();
}