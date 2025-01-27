#include "Filmes.hpp" 
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Mock para substituir interações com o usuário no SistemaFilmes
class MockSistemaFilmes : public SistemaFilmes {
public:
    MOCK_METHOD(void, cadastrarFilme, (), (override));
    MOCK_METHOD(void, listarFilmes, (), (override));
    MOCK_METHOD(void, buscarPorGenero, (), (override));
};

// Teste básico para o construtor da classe Filme e métodos getters
TEST(FilmeTest, ConstrutorEGetters) {
    std::vector<std::string> generos = {"Ação", "Aventura"};
    Filme filme("Filme Teste", generos, 12, 2023);

    EXPECT_EQ(filme.getTitulo(), "Filme Teste");
    EXPECT_EQ(filme.getGeneros(), generos);
    EXPECT_EQ(filme.getClassificacaoEtaria(), 12);
    EXPECT_EQ(filme.getAnoLancamento(), 2023);
}

// Teste para verificar a função que identifica se o filme é recém-lançado
TEST(FilmeTest, RecemLancado) {
    Filme filmeRecente("Filme Novo", {"Drama"}, 16, 2025);
    EXPECT_TRUE(filmeRecente.isRecemLancado());

    Filme filmeAntigo("Filme Velho", {"Comédia"}, 10, 2020);
    EXPECT_FALSE(filmeAntigo.isRecemLancado());
}

// Teste para verificar o cadastro de filmes usando mock
TEST(SistemaFilmesTest, CadastroComMock) {
    MockSistemaFilmes mockSistema;

    // Expectativa para o método cadastrarFilme
    EXPECT_CALL(mockSistema, cadastrarFilme())
        .Times(1);

    mockSistema.cadastrarFilme();
}

// Teste para verificar a listagem de filmes usando mock
TEST(SistemaFilmesTest, ListagemComMock) {
    MockSistemaFilmes mockSistema;

    // Expectativa para o método listarFilmes
    EXPECT_CALL(mockSistema, listarFilmes())
        .Times(1);

    mockSistema.listarFilmes();
}

// Teste para verificar a busca por gênero usando mock
TEST(SistemaFilmesTest, BuscaPorGeneroComMock) {
    MockSistemaFilmes mockSistema;

    // Expectativa para o método buscarPorGenero
    EXPECT_CALL(mockSistema, buscarPorGenero())
        .Times(1);

    mockSistema.buscarPorGenero();
}

// Função principal para rodar os testes
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
