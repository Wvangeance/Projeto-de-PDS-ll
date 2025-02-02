#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <string>
#include "Cliente.hpp"
#include "Filmes.hpp"

class Locacao {
private:
    Pessoa cliente;
    Filme filme;
    std::string dataLocacao;
    std::string dataDevolucao;

public:
    Locacao();
    Locacao(const Pessoa& cliente, const Filme& filme, const std::string& dataLocacao, const std::string& dataDevolucao);
    const Pessoa& getCliente() const;
    const Filme& getFilme() const;
    const std::string& getDataLocacao() const;
    const std::string& getDataDevolucao() const;
    double getPreco() const;
    int calcularDiasAtraso(const std::string& dataAtual) const;
    void exibirInformacoes() const;
};

#endif // LOCACAO_HPP
