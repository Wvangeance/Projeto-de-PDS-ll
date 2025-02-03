#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Cliente.hpp"

using ::testing::Return;
using ::testing::_;

// Classe Mock para simular interações com o arquivo
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(void, coletarDados, (), (override));
    MOCK_METHOD(void, cadastrarNoArquivo, (), (override));
};

TEST(PessoaTest, TestColetarDados) {
    MockPessoa pessoa;
    EXPECT_CALL(pessoa, coletarDados()).Times(1);
    pessoa.coletarDados();
}

TEST(PessoaTest, TestCadastroArquivo) {
    MockPessoa pessoa;
    EXPECT_CALL(pessoa, cadastrarNoArquivo()).Times(1);
    pessoa.cadastrarNoArquivo();
}

TEST(PessoaTest, TestGetters) {
    Pessoa pessoa;
    pessoa.coletarDados();
    EXPECT_NE(pessoa.getNome(), "");
    EXPECT_GT(pessoa.getId(), 0);
}

TEST(PessoaTest, TestListarClientes) {
    std::ofstream arquivo("clientes.txt");
    arquivo << "Nome: Teste\nCPF: 12345678900\nPermitido Locacao: Sim\nID: 1\n";
    arquivo.close();
    
    testing::internal::CaptureStdout();
    Pessoa::listarClientes();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_NE(output.find("Nome: Teste"), std::string::npos);
}
