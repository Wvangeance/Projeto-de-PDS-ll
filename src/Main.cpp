#include "Main.hpp"
#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include <algorithm>

// Funções do menu principal
void registrarCliente(std::vector<Pessoa>& clientes) {
    Pessoa cliente;
    cliente.coletarDados();
    cliente.cadastrarNoArquivo();
    clientes.push_back(cliente);
}

void listarClientes(const std::vector<Pessoa>& clientes) {
    if (clientes.empty()) {
        std::cout << "Nenhum cliente cadastrado.\n";
        return;
    }
    std::cout << "\n--- Lista de Clientes ---\n";
    for (const auto& cliente : clientes) {
        std::cout << "Nome: " << cliente.getNome() << "\n";
        std::cout << "ID: " << cliente.getId() << "\n";
        std::cout << "-----------------------------\n";
    }
}

void cadastrarFilme(std::vector<Filme>& filmes) {
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;
    double preco;
    int quantidadeGeneros;
    
    std::cout << "Digite o título do filme: ";
    std::getline(std::cin >> std::ws, titulo);
    std::cout << "Digite a quantidade de gêneros: ";
    std::cin >> quantidadeGeneros;
    std::cin.ignore();
    for (int i = 0; i < quantidadeGeneros; ++i) {
        std::string genero;
        std::cout << "Digite o gênero " << i + 1 << ": ";
        std::getline(std::cin, genero);
        generos.push_back(genero);
    }
    std::cout << "Digite a classificação etária: ";
    std::cin >> classificacaoEtaria;
    std::cout << "Digite o ano de lançamento: ";
    std::cin >> anoLancamento;
    std::cout << "Digite o preço do filme: ";
    std::cin >> preco;
    
    Filme filme(titulo, generos, classificacaoEtaria, anoLancamento, preco);
    filme.registrarNoArquivo();
    filmes.push_back(filme);
}

void listarFilmes(const std::vector<Filme>& filmes) {
    if (filmes.empty()) {
        std::cout << "Nenhum filme cadastrado.\n";
        return;
    }
    std::cout << "\n--- Lista de Filmes ---\n";
    for (const auto& filme : filmes) {
        std::cout << "ID: " << filme.getId() << "\n";
        std::cout << "Título: " << filme.getTitulo() << "\n";
        std::cout << "Gêneros: ";
        for (const auto& genero : filme.getGeneros()) {
            std::cout << genero << " ";
        }
        std::cout << "\n";
        std::cout << "Classificação Etária: " << filme.getClassificacaoEtaria() << "+\n";
        std::cout << "Ano de Lançamento: " << filme.getAnoLancamento() << "\n";
        std::cout << "Preço: R$ " << filme.getPreco() << "\n";
        std::cout << "-----------------------------\n";
    }
}

void realizarLocacao(std::vector<Pessoa>& clientes, std::vector<Filme>& filmes, std::vector<Locacao>& locacoes, Historico& historico) {
    int idCliente, idFilme;
    std::string dataLocacao, dataDevolucao;
    
    listarClientes(clientes);
    std::cout << "Digite o ID do cliente: ";
    std::cin >> idCliente;
    auto itCliente = std::find_if(clientes.begin(), clientes.end(), [&idCliente](const Pessoa& cliente) {
        return cliente.getId() == idCliente;
    });
    if (itCliente == clientes.end()) {
        std::cout << "Cliente não encontrado!\n";
        return;
    }
    
    listarFilmes(filmes);
    std::cout << "Digite o ID do filme: ";
    std::cin >> idFilme;
    auto itFilme = std::find_if(filmes.begin(), filmes.end(), [&idFilme](const Filme& filme) {
        return filme.getId() == idFilme;
    });
    if (itFilme == filmes.end()) {
        std::cout << "Filme não encontrado!\n";
        return;
    }
    
    std::cout << "Digite a data de locação (dd-mm-yyyy): ";
    std::cin >> dataLocacao;
    std::cout << "Digite a data de devolução (dd-mm-yyyy): ";
    std::cin >> dataDevolucao;
    
    Locacao locacao(*itCliente, *itFilme, dataLocacao, dataDevolucao);
    locacoes.push_back(locacao);
    historico.adicionarRegistro("Locação - Cliente: " + itCliente->getNome() + ", Filme: " + itFilme->getTitulo() + ", Data: " + dataLocacao + " a " + dataDevolucao);
    std::cout << "Locação realizada com sucesso!\n";
}

void aplicarPromocao(std::vector<Filme>& filmes, const std::vector<Pessoa>& clientes) {
    listarClientes(clientes);
    int idCliente;
    std::cout << "Digite o ID do cliente: ";
    std::cin >> idCliente;
    auto itCliente = std::find_if(clientes.begin(), clientes.end(), [&idCliente](const Pessoa& cliente) {
        return cliente.getId() == idCliente;
    });
    if (itCliente == clientes.end()) {
        std::cout << "Cliente não encontrado!\n";
        return;
    }
    
    listarFilmes(filmes);
    int idFilme;
    std::cout << "Digite o ID do filme: ";
    std::cin >> idFilme;
    auto itFilme = std::find_if(filmes.begin(), filmes.end(), [&idFilme](const Filme& filme) {
        return filme.getId() == idFilme;
    });
    if (itFilme == filmes.end()) {
        std::cout << "Filme não encontrado!\n";
        return;
    }
    
    double novoPreco = Promocao::aplicarDesconto(*itCliente, itFilme->getPreco());
    itFilme->setPreco(novoPreco);
    std::cout << "Promoção aplicada! Novo preço do filme: R$ " << novoPreco << "\n";
}

void realizarPagamento(std::vector<Locacao>& locacoes, Historico& historico) {
    if (locacoes.empty()) {
        std::cout << "Nenhuma locação encontrada.\n";
        return;
    }
    
    for (auto& locacao : locacoes) {
        bool pagamentoRealizado = false;
        std::cout << "\nPagamento para locação do filme " << locacao.getFilme().getTitulo() << " para o cliente " << locacao.getCliente().getNome() << "\n";
        std::cout << "Escolha o método de pagamento:\n";
        std::cout << "1. Dinheiro\n";
        std::cout << "2. Cartão de Crédito\n";
        std::cout << "3. Cartão de Débito\n";
        std::cout << "4. Pix\n";
        std::cout << "5. Escambo\n";
        int opcao;
        std::cin >> opcao;
        
        std::unique_ptr<Pagamento> pagamento;
        
        switch (opcao) {
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
                std::cout << "Opção inválida!\n";
                continue;
        }
        
        pagamento->realizarPagamento(locacao, pagamentoRealizado);
        
        if (pagamentoRealizado) {
            historico.adicionarRegistro("Pagamento - Cliente: " + locacao.getCliente().getNome() + ", Filme: " + locacao.getFilme().getTitulo());
        } else {
            std::cout << "Falha no pagamento!\n";
        }
    }
}

void listarHistorico(const Historico& historico) {
    historico.exibirHistorico();
}

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
        std::cout << "7. Listar Histórico\n";
        std::cout << "8. Aplicar Promoção\n";
        std::cout << "9. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;
        switch (opcao) {
            case 1: registrarCliente(clientes); break;
            case 2: listarClientes(clientes); break;
            case 3: cadastrarFilme(filmes); break;
            case 4: listarFilmes(filmes); break;
            case 5: realizarLocacao(clientes, filmes, locacoes, historico); break;
            case 6: realizarPagamento(locacoes, historico); break;
            case 7: listarHistorico(historico); break;
            case 8: aplicarPromocao(filmes, clientes); break;
            case 9: std::cout << "Saindo...\n"; break;
            default: std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opcao != 9);
}

int main() {
    menuPrincipal();
    return 0;
}
