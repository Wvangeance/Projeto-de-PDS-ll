#include "Cliente.hpp"
#include "Filmes.hpp"
#include "Locacoes.hpp"
#include "Pagamento.hpp"
#include "Historico.hpp"
#include "Promocao.hpp"
#include "Utilitarios.hpp"

#include <iostream>
#include <vector>
#include <memory>

class SistemaLocadora {
private:
    std::vector<Pessoa> clientes;
    std::vector<Filme> filmes;
    Historico historico;
    Promocao promocao;

public:
    // Adiciona um cliente à locadora
    void cadastrarCliente(const Pessoa& cliente) {
        clientes.push_back(cliente);
    }

    // Adiciona um filme à locadora
    void cadastrarFilme(const Filme& filme) {
        filmes.push_back(filme);
    }

    // Realiza a locação de um filme
    void realizarLocacao(const Pessoa& cliente, const Filme& filme, const std::string& dataLocacao, const std::string& dataDevolucao) {
        Locacao locacao(cliente, filme, dataLocacao, dataDevolucao);
        historico.adicionarRegistro("Locação realizada: " + filme.getTitulo() + " por " + cliente.getNome());

        std::cout << "Locação realizada com sucesso para " << cliente.getNome() << "!\n";
    }

    // Realiza o pagamento de uma locação
    void realizarPagamento(const Locacao& locacao, const std::shared_ptr<Pagamento>& metodoPagamento) {
        bool pagamentoRealizado = false;
        metodoPagamento->realizarPagamento(locacao, pagamentoRealizado);

        if (pagamentoRealizado) {
            historico.adicionarRegistro("Pagamento realizado com sucesso para locação de " + locacao.getFilme().getTitulo());
            std::cout << "Pagamento realizado com sucesso!\n";
        } else {
            std::cout << "Erro no pagamento!\n";
        }
    }

    // Aplica desconto baseado no ID do cliente
    void aplicarDesconto(const Pessoa& cliente, Locacao& locacao) {
        double precoOriginal = locacao.getPreco();
        double precoComDesconto = promocao.aplicarDesconto(cliente, precoOriginal);
        std::cout << "Desconto aplicado! Novo preço: R$ " << precoComDesconto << "\n";
    }

    // Exibe o histórico de locações e pagamentos
    void exibirHistorico() const {
        historico.exibirHistorico();
    }

    // Método de utilitário para calcular multa por atraso
    void calcularMulta(const Locacao& locacao, int diasPermitidos) {
        Multa multa;
        double multaCalculada = multa.calcularMulta(locacao, diasPermitidos);
        if (multaCalculada > 0) {
            std::cout << "Multa por atraso: R$ " << multaCalculada << "\n";
        } else {
            std::cout << "Sem multa por atraso.\n";
        }
    }
};

#include "Locacoes.hpp"
#include "Pagamento.hpp"

int main() {
    // Criação de objetos
    Locadora locadora;

    // Criar cliente
    Pessoa cliente("João Silva", 12345, "(11)99999-9999", "joao@example.com");
    locadora.cadastrarCliente(cliente);

    // Criar filme
    Filme filme("O Poderoso Chefão", {"Drama", "Crime"}, 20.0, 1972, 180);
    locadora.cadastrarFilme(filme);

    // Realizar locação
    locadora.realizarLocacao(cliente, filme, "2025-01-31", "2025-02-07");

    // Realizar pagamento (exemplo com pagamento em dinheiro)
    Locacao locacao(cliente, filme, "2025-01-31", "2025-02-07");
    std::shared_ptr<Pagamento> pagamento = std::make_shared<PagamentoDinheiro>();
    locadora.realizarPagamento(locacao, pagamento);

    // Aplicar desconto
    locadora.aplicarDesconto(cliente, locacao);

    // Calcular multa
    locadora.calcularMulta(locacao, 7);  // 7 dias permitidos

    // Exibir histórico
    locadora.exibirHistorico();

    return 0;
}