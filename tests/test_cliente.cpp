#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Cliente.hpp"

// Classe mock para testar interações
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(void, coletarDados, (), (override));
    MOCK_METHOD(void, cadastrarNoArquivo, (), (override));
    MOCK_METHOD(void, listarArquivo, (), (override));
    MOCK_METHOD(void, editarPermissaoLocacao, (), (override));
};

// Teste de inicialização da classe Pessoa
TEST(PessoaTest, ConstrutorPadrao) {
    Pessoa pessoa;
    EXPECT_EQ(pessoa.getNome(), "");
    EXPECT_EQ(pessoa.getId(), 0);
}

// Teste de coleta de dados simulada
TEST(PessoaTest, ColetarDados) {
    MockPessoa mockPessoa;
    EXPECT_CALL(mockPessoa, coletarDados()).Times(1);
    mockPessoa.coletarDados();
}

// Teste de escrita no arquivo
TEST(PessoaTest, CadastrarNoArquivo) {
    Pessoa pessoa;
    std::ofstream arquivo("dados.txt", std::ios::trunc);
    ASSERT_TRUE(arquivo.is_open());
    arquivo.close();

    pessoa.cadastrarNoArquivo();

    std::ifstream arquivoIn("dados.txt");
    ASSERT_TRUE(arquivoIn.is_open());
    std::stringstream buffer;
    buffer << arquivoIn.rdbuf();
    arquivoIn.close();
    EXPECT_FALSE(buffer.str().empty());
}

// Teste de leitura do arquivo
TEST(PessoaTest, ListarArquivo) {
    Pessoa pessoa;
    std::ofstream arquivo("dados.txt");
    arquivo << "Nome: Teste\nCPF: 12345678900\nPermitido Locacao: Sim\nID: 1\n";
    arquivo.close();

    std::ifstream arquivoIn("dados.txt");
    ASSERT_TRUE(arquivoIn.is_open());
    arquivoIn.close();
    
    pessoa.listarArquivo();
}

// Teste de edição de permissão de locação simulada
TEST(PessoaTest, EditarPermissaoLocacao) {
    MockPessoa mockPessoa;
    EXPECT_CALL(mockPessoa, editarPermissaoLocacao()).Times(1);
    mockPessoa.editarPermissaoLocacao();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}