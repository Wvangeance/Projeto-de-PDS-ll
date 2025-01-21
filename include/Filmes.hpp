#ifndef SISTEMA_FILMES_H
#define SISTEMA_FILMES_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <limits>

class Filme {
private:
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;

public:
    Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento);

    std::string getTitulo() const;
    std::vector<std::string> getGeneros() const;
    int getClassificacaoEtaria() const;
    int getAnoLancamento() const;
    bool isRecemLancado() const;

    void exibirInformacoes() const;
    void salvarNoArquivo(std::ofstream& arquivo) const;
    static Filme lerDoArquivo(const std::string& linha);
};

class SistemaFilmes {
private:
    std::vector<Filme> filmes;
    const std::string arquivoFilmes;

    void salvarFilmes() const;
    void carregarFilmes();

public:
    SistemaFilmes();
    ~SistemaFilmes();

    void cadastrarFilme();
    void listarFilmes() const;
    void buscarPorGenero() const;
    void alterarOuExcluirFilme();
};

#endif // SISTEMA_FILMES_H