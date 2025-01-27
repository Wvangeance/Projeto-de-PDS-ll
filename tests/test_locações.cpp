#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Locacao.hpp"

// Mock para simular o carregamento de dados
class MockDataLoader {
public:
    MOCK_METHOD(std::vector<Cliente>, carregarUsuarios, (const std::string&), ());
    MOCK_METHOD(std::vector<std::string>, carregarFilmes, (const std::string&), ());
};

// Teste para validar o construtor da classe Cliente
TEST(ClienteTest, Construtor) {
    Cliente cliente(1, "Naruto Uzumaki", "123456789");
    EXPECT_EQ(cliente.id, 1);
    EXPECT_EQ(cliente.nome, "Naruto Uzumaki");
    EXPECT_EQ(cliente.telefone, "123456789");
}

// Teste para validar o construtor da classe Locacao
TEST(LocacaoTest, Construtor) {
    Cliente cliente(1, "Naruto Uzumaki", "123456789");
    Locacao locacao(1, cliente, "01/01/2023", "10/01/2023");

    EXPECT_EQ(locacao.id, 1);
    EXPECT_EQ(locacao.cliente.nome, "Naruto Uzumaki");
    EXPECT_EQ(locacao.dataLocacao, "01/01/2023");
    EXPECT_EQ(locacao.dataDevolucao, "10/01/2023");
    EXPECT_FALSE(locacao.devolvido);
}

// Teste para validar o método marcarComoDevolvido
TEST(LocacaoTest, MarcarComoDevolvido) {
    Cliente cliente(1, "Naruto Uzumaki", "123456789");
    Locacao locacao(1, cliente, "01/01/2023", "10/01/2023");

    locacao.marcarComoDevolvido();
    EXPECT_TRUE(locacao.devolvido);
}

// Teste para carregar usuários com sucesso
TEST(UtilityTest, CarregarUsuarios) {
    std::ofstream arquivo("usuarios_mock.txt");
    arquivo << "1;Naruto Uzumaki;123456789\n";
    arquivo << "2;Sakura Haruno;987654321\n";
    arquivo.close();

    std::vector<Cliente> clientes = carregarUsuarios("usuarios_mock.txt");
    EXPECT_EQ(clientes.size(), 2);
    EXPECT_EQ(clientes[0].nome, "Naruto Uzumaki");
    EXPECT_EQ(clientes[1].telefone, "987654321");

    std::remove("usuarios_mock.txt"); // Remover arquivo mock após teste
}

// Teste para carregar filmes com sucesso
TEST(UtilityTest, CarregarFilmes) {
    std::ofstream arquivo("filmes_mock.txt");
    arquivo << "Filme A\n";
    arquivo << "Filme B\n";
    arquivo.close();

    std::vector<std::string> filmes = carregarFilmes("filmes_mock.txt");
    EXPECT_EQ(filmes.size(), 2);
    EXPECT_EQ(filmes[0], "Filme A");
    EXPECT_EQ(filmes[1], "Filme B");

    std::remove("filmes_mock.txt"); // Remover arquivo mock após teste
}

// Teste para verificar exibição de detalhes de locação
TEST(LocacaoTest, ExibirDetalhes) {
    Cliente cliente(1, "Naruto Uzumaki", "123456789");
    Locacao locacao(1, cliente, "01/01/2023", "10/01/2023");

    testing::internal::CaptureStdout();
    locacao.exibirDetalhes();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Locacao ID: 1"), std::string::npos);
    EXPECT_NE(output.find("Cliente: Naruto Uzumaki"), std::string::npos);
    EXPECT_NE(output.find("Nao devolvido"), std::string::npos);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

