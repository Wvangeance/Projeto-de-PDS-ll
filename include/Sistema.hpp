#ifndef SISTEMA_HPP
#define SISTEMA_HPP

#include "Filmes.hpp"
#include "Cliente.hpp"
#include "Locações.hpp"
#include "Pagamento.hpp"

class Sistema {
private:
    std::vector<Filme> filmes;
    std::vector<Cliente> clientes;
    std::vector<Locacao> locacoes;
    std::vector<Pagamento> pagamentos;

    int proxIdLocacao = 1;
    int proxIdPagamento = 1;

public:
    // Métodos para adicionar entidades
    void adicionarFilme(const Filme& filme);
    void adicionarCliente(const Cliente& cliente);

    // Métodos para listar
    void listarFilmes() const;

    // Métodos de operação
    void realizarLocacao(int idCliente, int idFilme, const std::string& dataLocacao, const std::string& dataDevolucao);
    void registrarPagamento(int idCliente, double valor, const std::string& dataPagamento);
};

#endif // SISTEMA_HPP

