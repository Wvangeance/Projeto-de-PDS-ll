#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "vector"
#include "string"
#include "Filmes.hpp"
#include "Cliente.hpp"
#include "Locacoes.hpp"
#include "Pagamento.hpp"
#include "Historico.hpp"
#include "Promocao.hpp"

class Sistema {
private:
    std::vector<Filme> filmes;
    std::vector<Pessoa> clientes;
    std::vector<Locacao> locacoes;
    std::vector<Pagamento> pagamentos;
    std::vector<Historico> historico;

    int proxIdLocacao = 1;
    int proxIdPagamento = 1;
    int proxIdLocacao = 1;
    int proxIdPagamento = 1;

public:
    // Métodos para adicionar entidades
    void adicionarFilme(const Filme& filme);
    void adicionarCliente(const Pessoa& cliente);

    // Métodos para listar
    void listarFilmes() const;

    // Métodos de operação
    void realizarLocacao(int idCliente, int idFilme, const std::string& dataLocacao, const std::string& dataDevolucao);
    void registrarPagamento(int idCliente, double valor, const std::string& dataPagamento);

    //Métodos para histórico 
    void exibirHistorico() const;
    void salvarHistorico(const std::string& nomeArquivo);
    };

#endif // SISTEMA_HPP
