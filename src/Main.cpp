#include "Main.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>

// Funções para o menu principal
void registrarCliente(std::vector<Pessoa>& clientes);
void listarClientes(const std::vector<Pessoa>& clientes);
void cadastrarFilme(std::vector<Filme>& filmes);
void listarFilmes(const std::vector<Filme>& filmes);
void realizarLocacao(std::vector<Pessoa>& clientes, std::vector<Filme>& filmes, std::vector<Locacao>& locacoes, Historico& historico);
void realizarPagamento(std::vector<Locacao>& locacoes, Historico& historico);

// Função para exibir o menu principal do sistema
void menuPrincipal() {
    Historico historico;
    std::vector<Pessoa> clientes;
    std::vector<Filme> filmes;
    std::vector<Locacao> locacoes;
    int opcao;

    do {
        std::cout << "\n=== Sistema de Locação de Filmes ===\n";
        std::cout << "1. Registrar Cliente\n";
        std::cout << "2. Listar Clientes\n";
        std::cout << "3. Cadastrar Filme\n";
        std::cout << "4. Listar Filmes\n";
        std::cout << "5. Realizar Locação\n";
        std::cout << "6. Realizar Pagamento\n";
        std::cout << "7. Exibir Histórico\n";
        std::cout << "8. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                registrarCliente(clientes);
                break;
            case 2:
                listarClientes(clientes);
                break;
            case 3:
                cadastrarFilme(filmes);
                break;
            case 4:
                listarFilmes(filmes);
                break;
            case 5:
                realizarLocacao(clientes, filmes, locacoes, historico);
                break;
            case 6:
                realizarPagamento(locacoes, historico);
                break;
            case 7:
                historico.exibirHistorico();
                break;
            case 8:
                std::cout << "Saindo...\n";
                break;
            default:
                std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 8);
}

// Função para registrar um cliente
void registrarCliente(std::vector<Pessoa>& clientes) {
    Pessoa cliente;
    cliente.coletarDados();
    cliente.cadastrarNoArquivo();
    clientes.push_back(cliente);
    std::cout << "Cliente registrado com sucesso!\n";
}

// Função para listar clientes
void listarClientes(const std::vector<Pessoa>& clientes) {
    if (clientes.empty()) {
        std::cout << "Nenhum cliente cadastrado.\n";
        return;
    }

    std::cout << "\n=== Lista de Clientes ===\n";
    for (const auto& cliente : clientes) {
        cliente.exibirDados();
    }
}

// Função para cadastrar um filme
void cadastrarFilme(std::vector<Filme>& filmes) {
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;
    double preco;

    std::cin.ignore();
    std::cout << "Digite o título do filme: ";
    std::getline(std::cin, titulo);

    std::cout << "Digite os gêneros do filme separados por vírgula: ";
    std::string generoStr;
    std::getline(std::cin, generoStr);
    std::stringstream ss(generoStr);
    std::string genero;
    while (std::getline(ss, genero, ',')) {
        generos.push_back(genero);
    }

    std::cout << "Digite a classificação etária: ";
    std::cin >> classificacaoEtaria;

    std::cout << "Digite o ano de lançamento: ";
    std::cin >> anoLancamento;

    std::cout << "Digite o preço do filme: R$ ";
    std::cin >> preco;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    filmes.emplace_back(titulo, generos, classificacaoEtaria, anoLancamento, preco);
    std::cout << "Filme cadastrado com sucesso!\n";
}

// Função para listar filmes
void listarFilmes(const std::vector<Filme>& filmes) {
    if (filmes.empty()) {
        std::cout << "Nenhum filme cadastrado.\n";
        return;
    }

    std::cout << "\n=== Lista de Filmes ===\n";
    for (const auto& filme : filmes) {
        filme.exibirInformacoes();
    }
}

// Função para realizar uma locação
void realizarLocacao(std::vector<Pessoa>& clientes, std::vector<Filme>& filmes, std::vector<Locacao>& locacoes, Historico& historico) {
    if (clientes.empty() || filmes.empty()) {
        std::cout << "Certifique-se de ter clientes e filmes cadastrados antes de realizar uma locação.\n";
        return;
    }

    int idCliente, idFilme;
    std::string dataLocacao, dataDevolucao;

    listarClientes(clientes);
    std::cout << "Digite o ID do cliente para locação: ";
    std::cin >> idCliente;

    listarFilmes(filmes);
    std::cout << "Digite o ID do filme para locação: ";
    std::cin >> idFilme;

    std::cin.ignore();
    std::cout << "Data da locação (YYYY-MM-DD): ";
    std::getline(std::cin, dataLocacao);
    std::cout << "Data de devolução (YYYY-MM-DD): ";
    std::getline(std::cin, dataDevolucao);

    Pessoa& cliente = clientes.at(idCliente);
    Filme& filme = filmes.at(idFilme);
    Locacao locacao(cliente, filme, dataLocacao, dataDevolucao);

    locacoes.push_back(locacao);
    historico.adicionarRegistro("Locação registrada para o filme: " + filme.getTitulo());
    std::cout << "Locação registrada com sucesso!\n";
}

// Função para realizar pagamento separado
void realizarPagamento(std::vector<Locacao>& locacoes, Historico& historico) {
    if (locacoes.empty()) {
        std::cout << "Nenhuma locação registrada para pagamento.\n";
        return;
    }

    int idLocacao;
    std::cout << "\n=== Locações Pendentes ===\n";
    for (size_t i = 0; i < locacoes.size(); ++i) {
        std::cout << i << ". Filme: " << locacoes[i].getFilme().getTitulo() << ", Cliente: " << locacoes[i].getCliente().getNome() << "\n";
    }

    std::cout << "Digite o número da locação para pagamento: ";
    std::cin >> idLocacao;

    if (idLocacao < 0 || static_cast<size_t>(idLocacao) >= locacoes.size()) {
        std::cout << "Locação inválida.\n";
        return;
    }

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

    pagamento->realizarPagamento(locacoes.at(idLocacao), pagamentoRealizado);

    if (pagamentoRealizado) {
        historico.adicionarRegistro("Pagamento realizado com sucesso para o filme: " + locacoes.at(idLocacao).getFilme().getTitulo());
        std::cout << "Pagamento realizado com sucesso!\n";
    } else {
        historico.adicionarRegistro("Falha no pagamento para o filme: " + locacoes.at(idLocacao).getFilme().getTitulo());
        std::cout << "Falha no pagamento.\n";
    }
}

int main() {
    menuPrincipal();
    return 0;
}
