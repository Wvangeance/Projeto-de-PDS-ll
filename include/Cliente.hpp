#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

class Pessoa {
private:
    std::string nome;
    std::string cpf;
    bool permitidoLocacao;

public:
    Pessoa();
    void coletarDados();
    void cadastrarNoArquivo();
    void listarArquivo();
    void editarPermissaoLocacao();
    
    // Método getter para o nome
    std::string getNome() const;
};

#endif
