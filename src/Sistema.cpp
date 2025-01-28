#include <algorithm>
#include "Sistema.hpp"

void Sistema::adicionarFilme(const Filme& filme) {
    filmes.push_back(filme);
}

void Sistema::adicionarCliente(const Pessoa& cliente) {
    clientes.push_back(cliente);
}

void Sistema::listarFilmes() const {
    for (const auto& filme : filmes) {
        std::cout << "Título: " << filme.getTitulo() 
                  << ", Gêneros: ";
        for (const auto& genero : filme.getGeneros()) {
            std::cout << genero << " ";
        }
        std::cout << ", Classificação Etária: " << filme.getClassificacaoEtaria()
                  << ", Ano de Lançamento: " << filme.getAnoLancamento()
                  << ", Disponível: " << (filme.isRecemLancado() ? "Sim" : "Não")
                  << std::endl;
    }
}

void Sistema::realizarLocacao(int idCliente, int idFilme, const std::string& dataLocacao, const std::string& dataDevolucao) {
    auto itCliente = std::find_if(clientes.begin(), clientes.end(), [idCliente](const Pessoa& cliente) {
        return cliente.id == idCliente;
    });

    auto itFilme = std::find_if(filmes.begin(), filmes.end(), [idFilme](const Filme& filme) {
        return filme.getTitulo() == idFilme && filme.isRecemLancado();
    });

    if (itCliente != clientes.end() && itFilme != filmes.end()) {
        locacoes.emplace_back(proxIdLocacao++, *itCliente, dataLocacao, dataDevolucao);
        itFilme->exibirInformacoes();
        std::cout << "Locação realizada com sucesso!\n";
    } else {
        std::cout << "Locação não pôde ser realizada. Cliente ou filme inválido.\n";
    }
}

void Sistema::registrarPagamento(int idCliente, double valor, const std::string& dataPagamento) {
    auto itCliente = std::find_if(clientes.begin(), clientes.end(), [idCliente](const Pessoa& cliente) {
        return idCliente;
    });

    if (itCliente != clientes.end()) {
        pagamentos.emplace_back(std::make_unique<PagamentoDinheiro>());
        pagamentos.back()->realizarPagamento(valor, true);
        std::cout << "Pagamento no valor de R$" << valor << " registrado com sucesso para o cliente: " << itCliente->nome << "\n";
    } else {
        std::cout << "Cliente não encontrado.\n";
    }
}
