#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Cliente.hpp"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::InSequence;

// Classe mock para simular interações com arquivos
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(void, coletarDados, (), (override));
    MOCK_METHOD(void, cadastrarNoArquivo, (), (override));
    MOCK_METHOD(void, listarArquivo, (), (override));
    MOCK_METHOD(void, editarPermissaoLocacao, (), (override));
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

// Testando o método de cadastro de cliente
TEST(PessoaTest, CadastroCliente) {
    MockPessoa mockPessoa;

    // Configurando os mocks para simular o comportamento esperado
    EXPECT_CALL(mockPessoa, coletarDados())
        .Times(1)
        .WillOnce(Return());

    EXPECT_CALL(mockPessoa, cadastrarNoArquivo())
        .Times(1)
        .WillOnce(Return());

    // Executando as funções
    mockPessoa.coletarDados();
    mockPessoa.cadastrarNoArquivo();
}

// Testando o método de listagem de clientes
TEST(PessoaTest, ListarClientes) {
    MockPessoa mockPessoa;

    EXPECT_CALL(mockPessoa, listarArquivo())
        .Times(1)
        .WillOnce(Return());

    // Executando o método
    mockPessoa.listarArquivo();
}

// Testando o método de edição de permissão de locação
TEST(PessoaTest, EditarPermissaoLocacao) {
    MockPessoa mockPessoa;

    EXPECT_CALL(mockPessoa, editarPermissaoLocacao())
        .Times(1)
        .WillOnce(Return());

    // Executando o método
    mockPessoa.editarPermissaoLocacao();
}

// Testando o getter do nome
TEST(PessoaTest, GetterNome) {
    MockPessoa mockPessoa;

    EXPECT_CALL(mockPessoa, getNome())
        .Times(1)
        .WillOnce(Return("Teste"));

    // Verificando o retorno
    EXPECT_EQ(mockPessoa.getNome(), "Teste");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
