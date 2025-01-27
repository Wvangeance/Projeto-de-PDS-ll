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
    // Construtores
    Locacao();  // Construtor padrão
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
};

#endif
