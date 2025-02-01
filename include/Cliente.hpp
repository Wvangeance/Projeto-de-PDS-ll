#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <limits>

class Pessoa {
private:
    std::string nome;
    std::string cpf;
    bool permitidoLocacao;
    int id;

public:
    Pessoa(); // Construtor padrão

    void coletarDados();
    void cadastrarNoArquivo();
    void exibirDados() const;  // Adicionar const aqui

    std::string getNome() const;
    int getId() const;
};

#endif // CLIENTE_HPP
