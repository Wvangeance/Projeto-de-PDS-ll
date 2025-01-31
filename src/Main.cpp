#include "Main.hpp"
#include <iostream>
#include <memory>

// Função para exibir o menu principal do sistema
void menuPrincipal() {
    Historico historico;
    int opcao;

    // Loop para exibir o menu e receber a opção do usuário
    do {
        std::cout << "\n=== Sistema de Locação de Filmes ===\n";
        std::cout << "1. Realizar Locação\n";
        std::cout << "2. Exibir Histórico\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        // Executa a ação correspondente à opção escolhida
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
    } while (opcao != 3); // Continua exibindo o menu até que a opção seja sair
}

// Função para realizar a locação de um filme
void realizarLocacao(Historico& historico) {
    std::string nome;
    int id;
    std::string titulo;
    double preco;
    std::string dataLocacao, dataDevolucao;

    // Coleta dados do cliente e do filme
    std::cout << "Nome do cliente: ";
    std::cin.ignore();
    std::getline(std::cin, nome);
    std::cout << "ID do cliente: ";
    std::cin >> id;

    // Cria um objeto Pessoa e coleta mais dados do cliente
    Pessoa cliente;
    cliente.coletarDados();

    std::cout << "Título do filme: ";
    std::cin.ignore();
    std::getline(std::cin, titulo);
    std::cout << "Preço do filme: ";
    std::cin >> preco;

    // Cria um objeto Filme com os dados coletados
    Filme filme(titulo, {"Gênero"}, 120, 2022, preco);

    // Coleta as datas de locação e devolução
    std::cout << "Data da locação (YYYY-MM-DD): ";
    std::cin.ignore();
    std::getline(std::cin, dataLocacao);
    std::cout << "Data de devolução (YYYY-MM-DD): ";
    std::getline(std::cin, dataDevolucao);

    // Cria um objeto Locacao com os dados coletados
    Locacao locacao(cliente, filme, dataLocacao, dataDevolucao);

    // Aplica um desconto no preço da locação
    double precoComDesconto = Promocao::aplicarDesconto(cliente, locacao.getPreco());
    std::cout << "Preço final após desconto: R$ " << precoComDesconto << "\n";

    // Processa o pagamento da locação
    processarPagamento(locacao, historico);
}

// Função para processar o pagamento da locação
void processarPagamento(const Locacao& locacao, Historico& historico) {
    int metodo;
    bool pagamentoRealizado = false;
    std::unique_ptr<Pagamento> pagamento;

    // Solicita ao usuário que escolha um método de pagamento
    std::cout << "Escolha o método de pagamento:\n";
    std::cout << "1. Dinheiro\n2. Cartão de Crédito\n3. Cartão de Débito\n4. Pix\n5. Escambo\n";
    std::cin >> metodo;

    // Cria o objeto de pagamento correspondente ao método escolhido
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

    // Realiza o pagamento
    pagamento->realizarPagamento(locacao, pagamentoRealizado);

    // Adiciona um registro no histórico com o status do pagamento
    if (pagamentoRealizado) {
        historico.adicionarRegistro("Locação de " + locacao.getFilme().getTitulo() + " paga com sucesso.");
    } else {
        historico.adicionarRegistro("Falha no pagamento da locação de " + locacao.getFilme().getTitulo() + ".");
    }
}

// Função principal do programa
int main() {
    menuPrincipal();
    return 0;
}