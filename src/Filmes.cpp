#include "Filmes.hpp"

int Filme::nextId = 0; // Inicializa o ID estático

// Implementação da classe Filme
Filme::Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
    : titulo(titulo), generos(generos), classificacaoEtaria(classificacaoEtaria), anoLancamento(anoLancamento), preco(preco), id(nextId++) {}

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

int Filme::getId() const {
    return id;
}

void Filme::setPreco(double preco) {
    this->preco = preco;
}

void Filme::exibirInformacoes() const {
    std::cout << "ID: " << id << "\n";
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

void Filme::registrarNoArquivo() const {
    std::ofstream arquivo("filmes.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "ID: " << id << "\n";
        arquivo << "Título: " << titulo << "\n";
        arquivo << "Gêneros: ";
        for (const auto& genero : generos) {
            arquivo << genero << " ";
        }
        arquivo << "\n";
        arquivo << "Classificação Etária: " << classificacaoEtaria << "+\n";
        arquivo << "Ano de Lançamento: " << anoLancamento << "\n";
        arquivo << "Preço: R$ " << preco << "\n";
        arquivo << "-----------------------------\n";
        arquivo.close();
        std::cout << "Filme registrado com sucesso no arquivo!\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo!\n";
    }
}

void Filme::listarFilmesArquivo() {
    std::ifstream arquivo("filmes.txt");
    if (arquivo.is_open()) {
        std::string linha;
        std::cout << "\nFilmes cadastrados:\n";
        while (std::getline(arquivo, linha)) {
            std::cout << linha << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura!\n";
    }
}
