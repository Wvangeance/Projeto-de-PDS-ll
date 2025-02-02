#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Main.hpp"

using ::testing::Return;

// Mock para a classe Pessoa
class MockPessoa : public Pessoa {
public:
    MOCK_METHOD(void, coletarDados, (), (override));
    MOCK_METHOD(void, cadastrarNoArquivo, (), (override));
    MOCK_METHOD(void, exibirDados, (), (const, override));
    MOCK_METHOD(int, getId, (), (const, override));
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

// Mock para a classe Filme
class MockFilme : public Filme {
public:
    MOCK_METHOD(void, registrarNoArquivo, (), (override));
    MOCK_METHOD(void, exibirInformacoes, (), (const, override));
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
};

// Mock para a classe Locacao
class MockLocacao : public Locacao {
public:
    MOCK_METHOD(Pessoa&, getCliente, (), (override));
    MOCK_METHOD(Filme&, getFilme, (), (override));
};

// Mock para a classe Pagamento
class MockPagamento : public Pagamento {
public:
    MOCK_METHOD(void, realizarPagamento, (Locacao&, bool&), (override));
};

TEST(MenuPrincipalTest, RegistrarCliente) {
    std::vector<Pessoa> clientes;
    MockPessoa clienteMock;
    
    EXPECT_CALL(clienteMock, coletarDados()).Times(1);
    EXPECT_CALL(clienteMock, cadastrarNoArquivo()).Times(1);
    
    clientes.push_back(clienteMock);
    EXPECT_EQ(clientes.size(), 1);
}

TEST(MenuPrincipalTest, ListarClientes) {
    std::vector<Pessoa> clientes;
    MockPessoa clienteMock;
    
    EXPECT_CALL(clienteMock, exibirDados()).Times(1);
    clientes.push_back(clienteMock);
    
    testing::internal::CaptureStdout();
    listarClientes(clientes);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_FALSE(output.empty());
}

TEST(MenuPrincipalTest, RealizarPagamento) {
    std::vector<Locacao> locacoes;
    Historico historico;
    MockLocacao locacaoMock;
    MockPagamento pagamentoMock;
    
    locacoes.push_back(locacaoMock);
    
    bool pagamentoRealizado = false;
    EXPECT_CALL(pagamentoMock, realizarPagamento(::testing::_, ::testing::_)).WillOnce(::testing::SetArgReferee<1>(true));
    
    testing::internal::CaptureStdout();
    realizarPagamento(locacoes, historico);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Pagamento realizado com sucesso!") != std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
