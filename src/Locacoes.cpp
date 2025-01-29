#include "Locacoes.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

// Construtor padrão
Locacao::Locacao() 
    : cliente(Pessoa()), 
      filme(Filme("Título Padrão", {"Gênero Padrão"}, 0, 1900, 0.0)), 
      dataLocacao(""), 
      dataDevolucao("") {}

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

// Métodos adicionais
double Locacao::getPreco() const {
    return filme.getPreco(); // Retorna o preço do filme associado à locação
}

int Locacao::calcularDiasAtraso(const std::string& dataAtual) const {
    auto parseData = [](const std::string& data) -> std::tm {
        std::tm tm = {};
        std::istringstream ss(data);
        ss >> std::get_time(&tm, "%Y-%m-%d");
        if (ss.fail()) {
            throw std::invalid_argument("Formato de data inválido!");
        }
        return tm;
    };

    std::tm tmDevolucao = parseData(dataDevolucao);
    std::tm tmAtual = parseData(dataAtual);

    auto timeDevolucao = std::mktime(&tmDevolucao);
    auto timeAtual = std::mktime(&tmAtual);

    if (timeAtual < timeDevolucao) {
        return 0; // Sem atraso
    }

    double diffSegundos = difftime(timeAtual, timeDevolucao);
    return static_cast<int>(diffSegundos / (60 * 60 * 24));
}

void Locacao::exibirInformacoes() const {
    std::cout << "Cliente: " << cliente.getNome() << "\n";
    std::cout << "Filme: " << filme.getTitulo() << "\n";
    std::cout << "Data de Locação: " << dataLocacao << "\n";
    std::cout << "Data de Devolução: " << dataDevolucao << "\n";
    std::cout << "Preço da Locação: R$ " << getPreco() << "\n";
}
