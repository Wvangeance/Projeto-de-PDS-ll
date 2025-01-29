#ifndef LOCACAO_HPP
#define LOCACAO_HPP

#include <string>
#include <chrono>
#include <iostream>
#include "Cliente.hpp"
#include "Filmes.hpp"

class Locacao {
private:
    Pessoa cliente;              // Associado à classe Pessoa
    Filme filme;                 // Associado à classe Filme
    std::string dataLocacao;     // Data da locação (formato: "AAAA-MM-DD")
    std::string dataDevolucao;   // Data de devolução esperada (formato: "AAAA-MM-DD")

public:
    // Construtores
    Locacao();
    Locacao(const Pessoa& cliente, const Filme& filme, const std::string& dataLocacao, const std::string& dataDevolucao);

    // Semântica de cópia
    Locacao(const Locacao& other);
    Locacao& operator=(const Locacao& other);

    // Semântica de movimentação
    Locacao(Locacao&& other) noexcept;
    Locacao& operator=(Locacao&& other) noexcept;

    // Destrutor
    ~Locacao();

    // Getters e Setters
    const Pessoa& getCliente() const;
    void setCliente(const Pessoa& cliente);

    const Filme& getFilme() const;
    void setFilme(const Filme& filme);

    const std::string& getDataLocacao() const;
    void setDataLocacao(const std::string& dataLocacao);

    const std::string& getDataDevolucao() const;
    void setDataDevolucao(const std::string& dataDevolucao);

    // Métodos adicionais
    double getPreco() const;                            // Retorna o preço do filme associado à locação
    int calcularDiasAtraso(const std::string& dataAtual) const; // Calcula os dias de atraso com base na data atual
    void exibirInformacoes() const;                    // Exibe detalhes da locação
};

#endif // LOCACAO_HPP
