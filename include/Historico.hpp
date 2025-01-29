#ifndef HISTORICO_HPP
#define HISTORICO_HPP

#include "Cliente.hpp"
#include "Locacoes.hpp"
#include "Pagamento.hpp"
#include "Filmes.hpp"
#include <vector>
#include <map>
#include <string>

class Historico {
public:
    std::map<int, Pessoa> clientes; // Dados de interação dos clientes, como locações e devoluções
    std::map<int, int> clientesFrequentes; // Contagem de locações por cliente

private:
    std::vector<Locacao> locacoes; // Registro de todas as locações realizadas
    std::vector<Pagamento> pagamentos; // Histórico de pagamentos efetuados e pendências
    std::map<std::string, int> estatisticasFilmes; // Contagem de filmes mais alugados

    void atualizarEstatisticas(const Locacao& locacao); // Atualiza estatísticas ao registrar uma locação
    void registrarPagamento(const Pagamento& pagamento); // Adiciona um novo pagamento no histórico

public:
    Historico();

    void registrarLocacao(const Locacao& locacao); // Adiciona uma nova locação
    void adicionarCliente(const Pessoa& cliente); // Adiciona um cliente no sistema
    void adicionarFilme(const Filme& filme); // Adiciona um filme no sistema
    void registrarPagamentoCliente(const Pagamento& pagamento); // Registra pagamento de um cliente

    void gerarRelatorio(const std::string& tipo); // Gera relatórios personalizados
    void gerarRelatorioFilmesMaisAlugados(); // Relatório de filmes mais alugados
    void consultarAtividade(int clienteId); // Exibe histórico detalhado de um cliente específico
};

#endif //HISTORICO_HPP