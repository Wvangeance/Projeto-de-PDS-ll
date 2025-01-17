#ifndef Cadastro_Cliente_HPP
#define Cadastro_Cliente_HPP

#include <iostream>
#include <string>
#include <fstream>

class Pessoa {
private:
    std::string nome;
    std::string cpf;

public:

    Pessoa();
  
 
    void coletarDados();
    void cadastrarNoArquivo();
    void ListarArquivo();
};

#endif 
