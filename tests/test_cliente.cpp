#include <gtest/gtest.h>
#include "Cliente.hpp"

// Teste para verificar o comportamento inicial do objeto Pessoa
TEST(PessoaTest, DefaultConstructor) {
    Pessoa pessoa;

    // Teste indireto de listarArquivo para garantir que o arquivo vazio
    testing::internal::CaptureStdout();
    pessoa.listarArquivo(); // Deve imprimir "Erro ao abrir o arquivo..."
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Erro ao abrir o arquivo"), std::string::npos);
}

// Teste para verificar a coleta de dados e cadastro no arquivo
TEST(PessoaTest, CadastrarNoArquivo) {
    Pessoa pessoa;

    // Simular entrada do usuário
    std::istringstream input("Joao Silva\n12345678900\n");
    std::cin.rdbuf(input.rdbuf());

    pessoa.coletarDados();

    // Verificar o cadastro no arquivo
    pessoa.cadastrarNoArquivo();

    // Abrir o arquivo e validar se os dados foram escritos corretamente
    std::ifstream arquivo("dados.txt");
    ASSERT_TRUE(arquivo.is_open());

    std::string linha;
    bool encontrouNome = false, encontrouCpf = false;
    while (std::getline(arquivo, linha)) {
        if (linha.find("Nome: Joao Silva") != std::string::npos) {
            encontrouNome = true;
        }
        if (linha.find("CPF: 12345678900") != std::string::npos) {
            encontrouCpf = true;
        }
    }

    arquivo.close();

    ASSERT_TRUE(encontrouNome);
    ASSERT_TRUE(encontrouCpf);
}

// Teste para verificar a listagem de clientes cadastrados
TEST(PessoaTest, ListarArquivo) {
    Pessoa pessoa;

    // Capturar a saída para verificar se os dados são listados corretamente
    testing::internal::CaptureStdout();
    pessoa.listarArquivo();
    std::string output = testing::internal::GetCapturedStdout();

    ASSERT_NE(output.find("Clientes cadastrados"), std::string::npos);
}

// Teste para verificar a edição de permissão de locação
TEST(PessoaTest, EditarPermissaoLocacao) {
    Pessoa pessoa;

    // Simular um CPF existente no arquivo para testar a edição
    std::ofstream arquivo("dados.txt", std::ios::trunc);
    arquivo << "Nome: Joao Silva\n";
    arquivo << "CPF: 12345678900\n";
    arquivo << "Permitido Locacao: Nao\n";
    arquivo << "-----------------------------\n";
    arquivo.close();

    // Simular entrada do usuário
    std::istringstream input("12345678900\nS\n");
    std::cin.rdbuf(input.rdbuf());

    pessoa.editarPermissaoLocacao();

    // Abrir o arquivo novamente e verificar se a permissão foi atualizada
    std::ifstream arquivoIn("dados.txt");
    ASSERT_TRUE(arquivoIn.is_open());

    std::string linha;
    bool permissaoAtualizada = false;
    while (std::getline(arquivoIn, linha)) {
        if (linha.find("Permitido Locacao: Sim") != std::string::npos) {
            permissaoAtualizada = true;
        }
    }

    arquivoIn.close();

    ASSERT_TRUE(permissaoAtualizada);
}
