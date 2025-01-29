#include "Historico.hpp"

Historico::Historico() {
    // Inicialização dos membros do histórico
}

// Função privada para atualizar estatísticas de filmes quando uma nova locação é registrada
void Historico::atualizarEstatisticas(const Locacao& locacao) {
    // Incrementa a contagem do filme locado em estatisticasFilmes
    estatisticasFilmes[locacao.getFilme().getTitulo()]++;
    // Incrementa a contagem de locações do cliente em clientesFrequentes
    clientesFrequentes[locacao.getCliente().getId()]++;
}

// Função privada para registrar um novo pagamento no histórico de pagamentos
void Historico::registrarPagamento(const Pagamento& pagamento) {
    pagamentos.push_back(pagamento); // Adiciona o pagamento na lista de pagamentos
}

// função para registrar uma nova locação
void Historico::registrarLocacao(const Locacao& locacao) {
    locacoes.push_back(locacao); // Adiciona a locação na lista de locações
    atualizarEstatisticas(locacao); // Atualiza as estatísticas após registrar a locação
}

// função para adicionar um novo cliente no sistema
void Historico::adicionarCliente(const Pessoa& cliente) {
    clientes[cliente.getId()] = cliente; // Adiciona o cliente no mapa de clientes
}

// Função para adicionar um novo filme no sistema
void Historico::adicionarFilme(const Filme& filme) {
    // Adicionar filme no sistema (implementação dependendo de como os filmes são armazenados)
}

// Função para registrar o pagamento de um cliente
void Historico::registrarPagamentoCliente(const Pagamento& pagamento) {
    registrarPagamento(pagamento); // Chamando a função privada para registrar o pagamento
}

// Função para gerar relatórios personalizados 
void Historico::gerarRelatorio(const std::string& tipo) {
    if (tipo == "filmes mais alugados") {
        gerarRelatorioFilmesMaisAlugados();
    }
    // Adicionar outros tipos de relatórios se necessário
}

// Função para gerar relatório dos filmes mais alugados
void Historico::gerarRelatorioFilmesMaisAlugados() {
    for (const auto& filme : estatisticasFilmes) {
        std::cout << filme.first << ": " << filme.second << " locações" << std::endl;
    }
}

// Função para consultar a atividade de um cliente específico
void Historico::consultarAtividade(int clienteId) {
    if (clientes.find(clienteId) != clientes.end()) {
        std::cout << "Atividades do cliente " << clienteId << ":" << std::endl;
        // Mostrar detalhes das atividades (locações, pagamentos, etc)
    } else {
         std::cout << "Cliente não encontrado." << std::endl;
    }
}
