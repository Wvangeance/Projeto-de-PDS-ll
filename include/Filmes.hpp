#ifndef FILMES_HPP
#define FILMES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Filme {
private:
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;
    double preco;
    int id;
    static int nextId;

public:
    Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco);
    std::string getTitulo() const;
    std::vector<std::string> getGeneros() const;
    int getClassificacaoEtaria() const;
    int getAnoLancamento() const;
    double getPreco() const;
    int getId() const;
    void setPreco(double preco);
    void registrarNoArquivo() const;
    static void listarFilmes();
};

#endif // FILMES_HPP
