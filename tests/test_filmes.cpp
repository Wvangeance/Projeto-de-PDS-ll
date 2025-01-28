#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Filmes.hpp"

using ::testing::NiceMock;
using ::testing::Return;

// Mock da classe Filme para isolar os testes da lógica interna
class MockFilme : public Filme {
public:
    MockFilme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento)
        : Filme(titulo, generos, classificacaoEtaria, anoLancamento) {}

    MOCK_METHOD(bool, isRecemLancado, (), (const, override));
    MOCK_METHOD(void, salvarNoArquivo, (std::ofstream& arquivo), (const, override));
};

// Mock para interagir com o sistema de arquivos
class MockSistemaFilmes : public SistemaFilmes {
public:
    MOCK_METHOD(void, salvarFilmes, (), (const, override));
    MOCK_METHOD(void, carregarFilmes, (), (override));
};

// Teste para verificar a funcionalidade de isRecemLancado
TEST(FilmeTest, IsRecemLancado) {
    Filme filmeRecente("Filme Recente", {"Drama"}, 14, 2023);
    Filme filmeAntigo("Filme Antigo", {"Ação"}, 16, 2019);

    EXPECT_TRUE(filmeRecente.isRecemLancado());
    EXPECT_FALSE(filmeAntigo.isRecemLancado());
}

// Testes para a classe SistemaFilmes
TEST(SistemaFilmesTest, CadastroDeFilme) {
    NiceMock<MockSistemaFilmes> mockSistema;
    EXPECT_CALL(mockSistema, salvarFilmes()).Times(1);

    Filme novoFilme("Filme Teste", {"Terror"}, 16, 2023);
    mockSistema.cadastrarFilme();

    // Verifique se o filme foi adicionado corretamente
    EXPECT_NO_THROW({
        const auto& filmes = mockSistema.listarFilmes();
        EXPECT_EQ(filmes.back().getTitulo(), "Filme Teste");
    });
}

TEST(SistemaFilmesTest, BuscaPorGenero) {
    SistemaFilmes sistema;
    sistema.cadastrarFilme();

    std::istringstream entrada("Filme X\nAção,Drama\n12\n2023\n");
    std::cin.rdbuf(entrada.rdbuf());

    sistema.buscarPorGenero();

    std::ostringstream saida;
    std::cout.rdbuf(saida.rdbuf());

    sistema.buscarPorGenero();

    EXPECT_TRUE(saida.str().find("Filme X") != std::string::npos);
}
