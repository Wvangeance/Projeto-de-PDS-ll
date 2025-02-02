#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Cliente.hpp"
#include <sstream>

using ::testing::AtLeast; // Para checar chamadas mínimas
using ::testing::Return;

// Mock para simular o comportamento de arquivos
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(void, coletarDados, (), (override));
    MOCK_METHOD(void, cadastrarNoArquivo, (), (override));
    MOCK_METHOD(void, exibirDados, (), (const, override));
    MOCK_METHOD(std::string, getNome, (), (const, override));
    MOCK_METHOD(int, getId, (), (const, override));
};

// Teste para verificar o cadastro no arquivo
test(PessoaTest, CadastroNoArquivo) {
    Pessoa pessoa;
    pessoa.nome = "Joao Teste";
    pessoa.cpf = "12345678900";
    pessoa.permitidoLocacao = true;
    pessoa.id = 1;

    // Redireciona o fluxo para um arquivo temporário
    std::ofstream tempFile("temp_dados.txt", std::ios::trunc);
    tempFile.close(); // Fecha para permitir a escrita pela função

    // Substitui o nome do arquivo temporariamente
    std::ofstream originalFile("dados.txt");
    std::rename("dados.txt", "backup_dados.txt");
    std::rename("temp_dados.txt", "dados.txt");

    pessoa.cadastrarNoArquivo();

    // Verifica se os dados foram escritos corretamente
    std::ifstream arquivo("dados.txt");
    std::stringstream buffer;
    buffer << arquivo.rdbuf();

    std::string esperado = "Nome: Joao Teste\nCPF: 12345678900\nPermitido Locação: Sim\nID: 1\n-----------------------------\n";
    EXPECT_EQ(buffer.str(), esperado);

    // Restaura o arquivo original
    std::remove("dados.txt");
    std::rename("backup_dados.txt", "dados.txt");
}

// Teste para verificar exibição dos dados
test(PessoaTest, ExibirDados) {
    // Cria um arquivo com dados de teste
    std::ofstream arquivo("dados.txt");
    arquivo << "Nome: Maria Teste\nCPF: 98765432100\nPermitido Locação: Não\nID: 2\n-----------------------------\n";
    arquivo.close();

    Pessoa pessoa;

    // Redireciona a saída padrão para capturar a saída da função
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    pessoa.exibirDados();

    std::cout.rdbuf(oldCout); // Restaura std::cout

    std::string esperado = "\nClientes cadastrados:\nNome: Maria Teste\nCPF: 98765432100\nPermitido Locação: Não\nID: 2\n-----------------------------\n\n";
    EXPECT_EQ(buffer.str(), esperado);

    // Limpa o arquivo de teste
    std::remove("dados.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}