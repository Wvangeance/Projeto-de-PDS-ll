#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Filmes.hpp"

// Mock para manipulação de arquivos
class MockFilme : public Filme {
public:
    MockFilme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
        : Filme(titulo, generos, classificacaoEtaria, anoLancamento, preco) {}

    MOCK_METHOD(void, registrarNoArquivo, (), (const, override));
};

// Teste do construtor
TEST(FilmeTest, Construtor) {
    Filme filme("Matrix", {"Ação", "Ficção Científica"}, 14, 1999, 12.99);
    EXPECT_EQ(filme.getTitulo(), "Matrix");
    EXPECT_EQ(filme.getClassificacaoEtaria(), 14);
    EXPECT_EQ(filme.getAnoLancamento(), 1999);
    EXPECT_DOUBLE_EQ(filme.getPreco(), 12.99);
}

// Teste dos getters
TEST(FilmeTest, Getters) {
    Filme filme("Titanic", {"Romance", "Drama"}, 12, 1997, 9.99);
    EXPECT_EQ(filme.getTitulo(), "Titanic");
    EXPECT_EQ(filme.getGeneros().size(), 2);
    EXPECT_EQ(filme.getClassificacaoEtaria(), 12);
    EXPECT_EQ(filme.getAnoLancamento(), 1997);
    EXPECT_DOUBLE_EQ(filme.getPreco(), 9.99);
}

// Teste do setter
TEST(FilmeTest, SetPreco) {
    Filme filme("Avatar", {"Ficção Científica", "Aventura"}, 12, 2009, 15.99);
    filme.setPreco(10.99);
    EXPECT_DOUBLE_EQ(filme.getPreco(), 10.99);
}

// Teste do método registrarNoArquivo (usando Mock)
TEST(FilmeTest, RegistrarNoArquivoMock) {
    MockFilme mockFilme("Inception", {"Ação", "Ficção Científica"}, 14, 2010, 19.99);

    EXPECT_CALL(mockFilme, registrarNoArquivo()).Times(1);

    mockFilme.registrarNoArquivo();
}

// Teste de listagem de filmes (simulação de leitura)
TEST(FilmeTest, ListarFilmes) {
    std::ofstream arquivo("filmes.txt");
    if (arquivo.is_open()) {
        arquivo << "1;Interstellar;Ficção Científica,Drama;10;2014;14.99\n";
        arquivo.close();
    }

    testing::internal::CaptureStdout();
    Filme::listarFilmes();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Interstellar") != std::string::npos);
}

