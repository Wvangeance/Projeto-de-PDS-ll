#include "Filmes.hpp"

// Implementação da classe Filme
Filme::Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
    : titulo(titulo), generos(generos), classificacaoEtaria(classificacaoEtaria), anoLancamento(anoLancamento), preco(preco) {}

std::string Filme::getTitulo() const {
    return titulo;
}

std::vector<std::string> Filme::getGeneros() const {
    return generos;
}

int Filme::getClassificacaoEtaria() const {
    return classificacaoEtaria;
}

int Filme::getAnoLancamento() const {
    return anoLancamento;
}

double Filme::getPreco() const {
    return preco;
}

void Filme::setPreco(double preco) {
    this->preco = preco;
}

void Filme::exibirInformacoes() const {
    std::cout << "Título: " << titulo << "\n";
    std::cout << "Gêneros: ";
    for (const auto& genero : generos) {
        std::cout << genero << " ";
    }
    std::cout << "\n";
    std::cout << "Classificação Etária: " << classificacaoEtaria << "+\n";
    std::cout << "Ano de Lançamento: " << anoLancamento << "\n";
    std::cout << "Preço: R$ " << preco << "\n";
}
