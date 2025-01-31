#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Sistema main.hpp"


// Mock da classe de pagamento para evitar dependência em classes reais
class PagamentoMock : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override {
        pagamentoRealizado = true; // Simula pagamento realizado com sucesso
    }
};

// Teste para o menu principal
TEST(SistemaTest, TesteMenuPrincipal) {
    std::stringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Chamando o menu principal e testando a interação com o usuário
    menuPrincipal();

    std::cout.rdbuf(cout_backup);

    // Verificando se as opções do menu aparecem
    EXPECT_TRUE(output.str().find("1. Realizar Locação") != std::string::npos);
    EXPECT_TRUE(output.str().find("2. Exibir Histórico") != std::string::npos);
    EXPECT_TRUE(output.str().find("3. Sair") != std::string::npos);
}

// Teste para realizar locação
TEST(SistemaTest, TesteRealizarLocacao) {
    // Criando um histórico de locações
    Historico historico;

    // Simulando entrada de dados
    std::istringstream input("Cliente Teste\n123\nFilme Teste\n15.0\n2025-01-01\n2025-01-07\n");
    std::streambuf* cin_backup = std::cin.rdbuf();
    std::cin.rdbuf(input.rdbuf());

    // Chama a função de locação
    realizarLocacao(historico);

    std::cin.rdbuf(cin_backup);

    // Verifica se o histórico contém o registro de locação
    std::stringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    historico.exibirHistorico();

    std::cout.rdbuf(cout_backup);

    EXPECT_TRUE(output.str().find("Locação de filme: Filme Teste") != std::string::npos);
    EXPECT_TRUE(output.str().find("Pagamento realizado: $15.0") != std::string::npos);
}

// Teste para processar pagamento
TEST(SistemaTest, TesteProcessarPagamento) {
    // Criando locação e histórico
    Pessoa cliente("Cliente Teste", 123);
    Filme filme("Filme Teste", {"Gênero"}, 120, 2022, 15.0);
    Locacao locacao(cliente, filme, "2025-01-01", "2025-01-07");
    Historico historico;

    // Usando o pagamento mock para simular um pagamento
    PagamentoMock pagamentoMock;
    bool pagamentoRealizado = false;

    // Processando o pagamento com o mock
    pagamentoMock.realizarPagamento(locacao, pagamentoRealizado);

    // Verificando se o pagamento foi marcado como realizado
    EXPECT_TRUE(pagamentoRealizado);

    // Adicionando registro ao histórico
    if (pagamentoRealizado) {
        historico.adicionarRegistro("Locação de " + filme.getTitulo() + " paga com sucesso.");
    }

    // Verificando se o histórico tem o registro correto
    std::stringstream output;
    std::streambuf* cout_backup = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    historico.exibirHistorico();

    std::cout.rdbuf(cout_backup);

    EXPECT_TRUE(output.str().find("Locação de Filme Teste paga com sucesso.") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
