#include "Filmes.hpp"

int Filme::nextId = 0; // Inicializa o ID estático

Filme::Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
    : titulo(titulo), generos(generos), classificacaoEtaria(classificacaoEtaria), anoLancamento(anoLancamento), preco(preco), id(nextId++) {}

std::string Filme::getTitulo() const { return titulo; }
std::vector<std::string> Filme::getGeneros() const { return generos; }
int Filme::getClassificacaoEtaria() const { return classificacaoEtaria; }
int Filme::getAnoLancamento() const { return anoLancamento; }
double Filme::getPreco() const { return preco; }
int Filme::getId() const { return id; }
void Filme::setPreco(double preco) { this->preco = preco; }

// Registrar filme no arquivo
void Filme::registrarNoArquivo() const {
    std::ofstream arquivo("filmes.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << id << ";" << titulo << ";";
        for (size_t i = 0; i < generos.size(); i++) {
            arquivo << generos[i];
            if (i < generos.size() - 1) arquivo << ",";
        }
        arquivo << ";" << classificacaoEtaria << ";" << anoLancamento << ";" << preco << "\n";
        arquivo.close();
        std::cout << "Filme registrado com sucesso!\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo!\n";
    }
}

// Listar todos os filmes cadastrados
void Filme::listarFilmes() {
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
