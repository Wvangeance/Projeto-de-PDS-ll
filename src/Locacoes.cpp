#include "Locacoes.hpp"
#include <sstream>
#include <iomanip>
#include <ctime>
#include <stdexcept>

Locacao::Locacao() : cliente(Pessoa()), filme(Filme("Título Padrão", {"Gênero Padrão"}, 0, 1900, 0.0)), dataLocacao(""), dataDevolucao("") {}

Locacao::Locacao(const Pessoa& cliente, const Filme& filme, const std::string& dataLocacao, const std::string& dataDevolucao)
    : cliente(cliente), filme(filme), dataLocacao(dataLocacao), dataDevolucao(dataDevolucao) {}

const Pessoa& Locacao::getCliente() const { return cliente; }
const Filme& Locacao::getFilme() const { return filme; }
const std::string& Locacao::getDataLocacao() const { return dataLocacao; }
const std::string& Locacao::getDataDevolucao() const { return dataDevolucao; }

double Locacao::getPreco() const { return filme.getPreco(); }

int Locacao::calcularDiasAtraso(const std::string& dataAtual) const {
    auto parseData = [](const std::string& data) -> std::tm {
        std::tm tm = {};
        std::istringstream ss(data);
        ss >> std::get_time(&tm, "%d-%m-%Y");
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
    return  static_cast<int>(diffSegundos / (60 * 60 * 24));
}

void Locacao::exibirInformacoes() const {
    std::cout << "Cliente: " << cliente.getNome() << "\n";
    std::cout << "Filme: " << filme.getTitulo() << "\n";
    std::cout << "Data de Locação: " << dataLocacao << "\n";
    std::cout << "Data de Devolução: " << dataDevolucao << "\n";
    std::cout << "Preço da Locação: R$ " << getPreco() << "\n";
};