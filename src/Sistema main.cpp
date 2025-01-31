#include "Sistema main.hpp"
#include <iostream>
#include <memory>

void menuPrincipal() {
    Historico historico;
    int opcao;

    do {
        std::cout << "\n=== Sistema de Locação de Filmes ===\n";
        std::cout << "1. Realizar Locação\n";
        std::cout << "2. Exibir Histórico\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                realizarLocacao(historico);
                break;
            case 2:
                historico.exibirHistorico();
                break;
            case 3:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 3);
}

void realizarLocacao(Historico& historico) {
    std::string nome;
    int id;
    std::string titulo;
    double preco;
    std::string dataLocacao, dataDevolucao;

    std::cout << "Nome do cliente: ";
    std::cin >> nome;
    std::cout << "ID do cliente: ";
    std::cin >> id;

    Pessoa cliente(nome, id);

    std::cout << "Título do filme: ";
    std::cin >> titulo;
    std::cout << "Preço do filme: ";
    std::cin >> preco;

    Filme filme(titulo, {"Gênero"}, 120, 2022, preco);

    std::cout << "Data da locação (YYYY-MM-DD): ";
    std::cin >> dataLocacao;
    std::cout << "Data de devolução (YYYY-MM-DD): ";
    std::cin >> dataDevolucao;

    Locacao locacao(cliente, filme, dataLocacao, dataDevolucao);

    double precoComDesconto = Promocao::aplicarDesconto(cliente, locacao.getPreco());
    std::cout << "Preço final após desconto: R$ " << precoComDesconto << "\n";

    processarPagamento(locacao, historico);
}

void processarPagamento(const Locacao& locacao, Historico& historico) {
    int metodo;
    bool pagamentoRealizado = false;
    std::unique_ptr<Pagamento> pagamento;

    std::cout << "Escolha o método de pagamento:\n";
    std::cout << "1. Dinheiro\n2. Cartão de Crédito\n3. Cartão de Débito\n4. Pix\n5. Escambo\n";
    std::cin >> metodo;

    switch (metodo) {
        case 1:
            pagamento = std::make_unique<PagamentoDinheiro>();
            break;
        case 2:
            pagamento = std::make_unique<PagamentoCartaoCredito>();
            break;
        case 3:
            pagamento = std::make_unique<PagamentoCartaoDebito>();
            break;
        case 4:
            pagamento = std::make_unique<PagamentoPix>();
            break;
        case 5:
            pagamento = std::make_unique<PagamentoEscambo>();
            break;
        default:
            std::cout << "Método inválido! Tente novamente.\n";
            return;
    }

    pagamento->realizarPagamento(locacao, pagamentoRealizado);

    if (pagamentoRealizado) {
        historico.adicionarRegistro("Locação de " + locacao.getFilme().getTitulo() + " paga com sucesso.");
    } else {
        historico.adicionarRegistro("Falha no pagamento da locação de " + locacao.getFilme().getTitulo() + ".");
    }
}

int main() {
    menuPrincipal();
    return 0;
}