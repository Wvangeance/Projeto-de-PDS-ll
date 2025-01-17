#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <string>
#include <vector>

// Classe Cliente
class Cliente {
public:
    int id;
    std::string nome;
    std::string telefone;

    // Construtor
    Cliente(int id, const std::string& nome, const std::string& telefone);
};

// Classe Locacao
class Locacao {
public:
    int id;
    Cliente cliente;
    std::string dataLocacao;
    std::string dataDevolucao;
    bool devolvido;

    // Construtor
    Locacao(int id, Cliente cliente, const std::string& dataLocacao, const std::string& dataDevolucao);

    // Métodos
    void marcarComoDevolvido();
    void exibirDetalhes() const;
};

// Funções utilitárias
std::vector<Cliente> carregarUsuarios(const std::string& nomeArquivo);
std::vector<std::string> carregarFilmes(const std::string& nomeArquivo);

// Menu principal
void menuGerenciamentoLocacoes();

#endif // LOCACAO_HPP