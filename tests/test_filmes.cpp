#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Filmes.hpp"
#include <fstream>
#include <sstream>

using ::testing::AtLeast; // Para checar chamadas mínimas
using ::testing::Return;

// Mock para simular o comportamento da classe Filme
class MockFilme : public Filme {
public:
    MockFilme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
        : Filme(titulo, generos, classificacaoEtaria, anoLancamento, preco) {}

    MOCK_METHOD(std::string, getTitulo, (), (const, override));
    MOCK_METHOD(std::vector<std::string>, getGeneros, (), (const, override));
    MOCK_METHOD(int, getClassificacaoEtaria, (), (const, override));
    MOCK_METHOD(int, getAnoLancamento, (), (const, override));
    MOCK_METHOD(double, getPreco, (), (const, override));
    MOCK_METHOD(void, registrarNoArquivo, (), (const, override));
    MOCK_METHOD(void, listarFilmesArquivo, (), (override));
};

// Teste para verificar o registro do filme no arquivo
test(FilmeTest, RegistroNoArquivo) {
    Filme filme("Matrix", {"Ação", "Ficção Científica"}, 16, 1999, 12.50);

    // Cria um arquivo temporário para teste
    std::ofstream tempFile("temp_filmes.txt", std::ios::trunc);
    tempFile.close();

    // Substitui o arquivo original temporariamente
    std::rename("filmes.txt", "backup_filmes.txt");
    std::rename("temp_filmes.txt", "filmes.txt");

    filme.registrarNoArquivo();

    // Verifica se os dados foram escritos corretamente
    std::ifstream arquivo("filmes.txt");
    std::stringstream buffer;
    buffer << arquivo.rdbuf();

    std::string esperado = "ID: 0\nTítulo: Matrix\nGêneros: Ação Ficção Científica \nClassificação Etária: 16+\nAno de Lançamento: 1999\nPreço: R$ 12.5\n-----------------------------\n";
    EXPECT_EQ(buffer.str(), esperado);

    // Restaura o arquivo original
    std::remove("filmes.txt");
    std::rename("backup_filmes.txt", "filmes.txt");
}

// Teste para verificar a listagem dos filmes
test(FilmeTest, ListarFilmes) {
    // Cria um arquivo com dados de teste
    std::ofstream arquivo("filmes.txt");
    arquivo << "ID: 1\nTítulo: Inception\nGêneros: Ação Ficção Científica \nClassificação Etária: 14+\nAno de Lançamento: 2010\nPreço: R$ 15\n-----------------------------\n";
    arquivo.close();

    Filme filme("Dummy", {}, 0, 0, 0.0);

    // Redireciona a saída padrão para capturar a saída da função
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    filme.listarFilmesArquivo();

    std::cout.rdbuf(oldCout); // Restaura std::cout

    std::string esperado = "\nFilmes cadastrados:\nID: 1\nTítulo: Inception\nGêneros: Ação Ficção Científica \nClassificação Etária: 14+\nAno de Lançamento: 2010\nPreço: R$ 15\n-----------------------------\n\n";
    EXPECT_EQ(buffer.str(), esperado);

    // Limpa o arquivo de teste
    std::remove("filmes.txt");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}