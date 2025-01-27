#include "Locações.hpp"
#include <utility>

// Construtor padrão
Locacao::Locacao() : cliente(Pessoa()), filme(Filme()), dataLocacao(""), dataDevolucao("") {}

// Construtor parametrizado
Locacao::Locacao(const Pessoa& cliente, const Filme& filme, const std::string& dataLocacao, const std::string& dataDevolucao)
    : cliente(cliente), filme(filme), dataLocacao(dataLocacao), dataDevolucao(dataDevolucao) {}

// Construtor de cópia
Locacao::Locacao(const Locacao& other)
    : cliente(other.cliente), filme(other.filme), dataLocacao(other.dataLocacao), dataDevolucao(other.dataDevolucao) {}

// Operador de atribuição por cópia
Locacao& Locacao::operator=(const Locacao& other) {
    if (this != &other) {
        cliente = other.cliente;
        filme = other.filme;
        dataLocacao = other.dataLocacao;
        dataDevolucao = other.dataDevolucao;
    }
    return *this;
}

// Construtor de movimentação
Locacao::Locacao(Locacao&& other) noexcept
    : cliente(std::move(other.cliente)), filme(std::move(other.filme)), dataLocacao(std::move(other.dataLocacao)), dataDevolucao(std::move(other.dataDevolucao)) {}

// Operador de atribuição por movimentação
Locacao& Locacao::operator=(Locacao&& other) noexcept {
    if (this != &other) {
        cliente = std::move(other.cliente);
        filme = std::move(other.filme);
        dataLocacao = std::move(other.dataLocacao);
        dataDevolucao = std::move(other.dataDevolucao);
    }
    return *this;
}

// Destrutor
Locacao::~Locacao() {}

// Getters e Setters
const Pessoa& Locacao::getCliente() const {
    return cliente;
}

void Locacao::setCliente(const Pessoa& cliente) {
    this->cliente = cliente;
}

const Filme& Locacao::getFilme() const {
    return filme;
}

void Locacao::setFilme(const Filme& filme) {
    this->filme = filme;
}

const std::string& Locacao::getDataLocacao() const {
    return dataLocacao;
}

void Locacao::setDataLocacao(const std::string& dataLocacao) {
    this->dataLocacao = dataLocacao;
}

const std::string& Locacao::getDataDevolucao() const {
    return dataDevolucao;
}

void Locacao::setDataDevolucao(const std::string& dataDevolucao) {
    this->dataDevolucao = dataDevolucao;
}
