#include <gtest/gtest.h>
#include "main.hpp"

TEST(ClienteTest, CadastroDeCliente) {
    Pessoa cliente("João Silva", 1);
    EXPECT_EQ(cliente.getNome(), "João Silva");
    EXPECT_EQ(cliente.getId(), 1);
}

TEST(FilmeTest, CadastroDeFilme) {
    std::vector<std::string> generos = {"Ação", "Aventura"};
    Filme filme("Vingadores", generos, 12, 2012, 10.0);
    EXPECT_EQ(filme.getTitulo(), "Vingadores");
    EXPECT_EQ(filme.getGeneros().size(), 2);
    EXPECT_EQ(filme.getClassificacaoEtaria(), 12);
    EXPECT_EQ(filme.getAnoLancamento(), 2012);
    EXPECT_EQ(filme.getPreco(), 10.0);
}

TEST(LocacaoTest, CriacaoDeLocacao) {
    Pessoa cliente("Maria Souza", 2);
    std::vector<std::string> generos = {"Drama"};
    Filme filme("A Procura da Felicidade", generos, 10, 2006, 8.0);
    Locacao locacao(cliente, filme, "01-02-2024", "07-02-2024");
    
    EXPECT_EQ(locacao.getCliente().getNome(), "Maria Souza");
    EXPECT_EQ(locacao.getFilme().getTitulo(), "A Procura da Felicidade");
    EXPECT_EQ(locacao.getDataLocacao(), "01-02-2024");
    EXPECT_EQ(locacao.getDataDevolucao(), "07-02-2024");
}

TEST(PromocaoTest, AplicarDesconto) {
    Pessoa cliente("Carlos Lima", 3);
    double precoOriginal = 15.0;
    double novoPreco = Promocao::aplicarDesconto(cliente, precoOriginal);
    EXPECT_LT(novoPreco, precoOriginal);
}

TEST(PagamentoTest, RealizarPagamento) {
    Pessoa cliente("Ana Paula", 4);
    std::vector<std::string> generos = {"Ficção Científica"};
    Filme filme("Interestelar", generos, 12, 2014, 12.0);
    Locacao locacao(cliente, filme, "05-02-2024", "12-02-2024");
    bool pagamentoRealizado = false;
    
    PagamentoPix pagamento;
    pagamento.realizarPagamento(locacao, pagamentoRealizado);
    EXPECT_TRUE(pagamentoRealizado);
}

TEST(HistoricoTest, RegistroDeHistorico) {
    Historico historico;
    historico.adicionarRegistro("Cliente João alugou o filme Matrix");
    std::vector<std::string> registros = historico.getRegistros();
    EXPECT_EQ(registros.size(), 1);
    EXPECT_EQ(registros[0], "Cliente João alugou o filme Matrix");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}