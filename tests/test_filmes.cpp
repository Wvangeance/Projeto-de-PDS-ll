#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Filmes.hpp"

using ::testing::Return;
using ::testing::_;

// Teste de criação de Filme
TEST(FilmeTest, CriacaoFilme) {
    Filme filme("Matrix", {"Ação", "Ficção Científica"}, 14, 1999, 19.90);
    EXPECT_EQ(filme.getTitulo(), "Matrix");
    EXPECT_EQ(filme.getClassificacaoEtaria(), 14);
    EXPECT_EQ(filme.getAnoLancamento(), 1999);
    EXPECT_EQ(filme.getPreco(), 19.90);
    EXPECT_EQ(filme.getGeneros().size(), 2);
}

// Teste de lançamento recente
TEST(FilmeTest, FilmeRecemLancado) {
    Filme filmeNovo("Avatar 3", {"Aventura", "Ficção"}, 12, 2024, 29.90);
    EXPECT_TRUE(filmeNovo.isRecemLancado());
    
    Filme filmeAntigo("Titanic", {"Romance", "Drama"}, 12, 1997, 15.00);
    EXPECT_FALSE(filmeAntigo.isRecemLancado());
}

// Teste de alteração de preço
TEST(FilmeTest, AlterarPreco) {
    Filme filme("Inception", {"Ação", "Ficção Científica"}, 12, 2010, 25.00);
    filme.setPreco(30.00);
    EXPECT_EQ(filme.getPreco(), 30.00);
}

// Mock para testar interações com arquivos
class MockSistemaFilmes : public SistemaFilmes {
public:
    MOCK_METHOD(void, salvarFilmes, (), (const, override));
    MOCK_METHOD(void, carregarFilmes, (), (override));
};

// Teste de cadastro de filme
TEST(SistemaFilmesTest, CadastroFilme) {
    MockSistemaFilmes mockSistema;
    EXPECT_CALL(mockSistema, salvarFilmes()).Times(1);
    
    mockSistema.cadastrarFilme();
}

// Teste de listagem de filmes (simulando que há filmes cadastrados)
TEST(SistemaFilmesTest, ListarFilmes) {
    SistemaFilmes sistema;
    sistema.cadastrarFilme();
    EXPECT_NO_THROW(sistema.listarFilmes());
}
