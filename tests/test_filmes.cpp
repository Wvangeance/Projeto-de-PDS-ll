#include "Filmes.hpp"
#include <gtest/gtest.h>

TEST(FilmeTest, ConstrutorEGetters) {
    std::vector<std::string> generos = {"Ação", "Aventura"};
    Filme filme("Filme Teste", generos, 12, 2023);

    EXPECT_EQ(filme.getTitulo(), "Filme Teste");
    EXPECT_EQ(filme.getGeneros(), generos);
    EXPECT_EQ(filme.getClassificacaoEtaria(), 12);
    EXPECT_EQ(filme.getAnoLancamento(), 2023);
}

TEST(FilmeTest, RecemLancado) {
    Filme filmeRecente("Filme Novo", {"Drama"}, 16, 2025);
    EXPECT_TRUE(filmeRecente.isRecemLancado());

    Filme filmeAntigo("Filme Velho", {"Comédia"}, 10, 2020);
    EXPECT_FALSE(filmeAntigo.isRecemLancado());
}

TEST(SistemaFilmesTest, CadastroEListagem) {
    SistemaFilmes sistema;
    std::vector<std::string> generos = {"Drama", "Romance"};

    sistema.cadastrarFilme();

    // Validação básica (substitua por mocks para entradas dinâmicas se necessário)
    std::ostringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    sistema.listarFilmes();

    std::cout.rdbuf(prevcoutbuf);

    std::string resultado = buffer.str();
    EXPECT_NE(resultado.find("Lista de Filmes Cadastrados:"), std::string::npos);
}

TEST(SistemaFilmesTest, BuscaPorGenero) {
    SistemaFilmes sistema;
    sistema.cadastrarFilme();

    std::ostringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());

    sistema.buscarPorGenero();

    std::cout.rdbuf(prevcoutbuf);

    std::string resultado = buffer.str();
    EXPECT_NE(resultado.find("Filmes encontrados"), std::string::npos);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
