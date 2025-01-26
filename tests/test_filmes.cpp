#include "Filmes.hpp" 
#include <gtest/gtest.h>


// Teste básico para o construtor da classe Filme e métodos getters
TEST(FilmeTest, ConstrutorEGetters) {
    // Criando um filme de teste com dados predefinidos
    std::vector<std::string> generos = {"Ação", "Aventura"};
    Filme filme("Filme Teste", generos, 12, 2023);

    // Verificando se os getters retornam os valores corretos
    EXPECT_EQ(filme.getTitulo(), "Filme Teste");
    EXPECT_EQ(filme.getGeneros(), generos);
    EXPECT_EQ(filme.getClassificacaoEtaria(), 12);
    EXPECT_EQ(filme.getAnoLancamento(), 2023);
}

// Teste para verificar a função que identifica se o filme é recém-lançado
TEST(FilmeTest, RecemLancado) {
    // Criando um filme com ano de lançamento recente (assume que estamos em 2025)
    Filme filmeRecente("Filme Novo", {"Drama"}, 16, 2025);
    EXPECT_TRUE(filmeRecente.isRecemLancado()); /

    // Criando um filme com ano de lançamento antigo
    Filme filmeAntigo("Filme Velho", {"Comédia"}, 10, 2020);
    EXPECT_FALSE(filmeAntigo.isRecemLancado()); 
}

// Teste para verificar o cadastro e a listagem de filmes no SistemaFilmes
TEST(SistemaFilmesTest, CadastroEListagem) {
    SistemaFilmes sistema;

    // Simulando o cadastro de um filme (mocks podem ser usados aqui para substituir entradas do usuário)
    std::istringstream input("Filme Drama\nDrama, Romance\n12\n2023\n");
    std::cin.rdbuf(input.rdbuf()); 
    sistema.cadastrarFilme();

    // Capturando a saída do método listarFilmes para validação
    std::ostringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf()); 
    sistema.listarFilmes(); 
    std::cout.rdbuf(prevcoutbuf); 

    // Validando a saída
    std::string resultado = buffer.str();
    EXPECT_NE(resultado.find("Lista de Filmes Cadastrados:"), std::string::npos);
}

// Teste para verificar a busca de filmes por gênero
TEST(SistemaFilmesTest, BuscaPorGenero) {
    SistemaFilmes sistema;

    // Simulando o cadastro de filmes
    std::istringstream input("Filme Drama\nDrama, Romance\n12\n2023\n");
    std::cin.rdbuf(input.rdbuf());
    sistema.cadastrarFilme();

    // Simulando entrada do gênero buscado
    std::istringstream generoInput("Drama\n");
    std::cin.rdbuf(generoInput.rdbuf());

    // Capturando a saída do método buscarPorGenero para validação
    std::ostringstream buffer;
    std::streambuf* prevcoutbuf = std::cout.rdbuf(buffer.rdbuf());
    sistema.buscarPorGenero();
    std::cout.rdbuf(prevcoutbuf);

    // Validando a saída
    std::string resultado = buffer.str();
    EXPECT_NE(resultado.find("Filmes encontrados"), std::string::npos);
}

// Função principal para rodar os testes
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}
