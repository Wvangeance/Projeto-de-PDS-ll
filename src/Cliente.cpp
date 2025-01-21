#include <iostream>
#include <string>
#include <limits>

#include "Cadastro_Cliente.hpp"  

Pessoa::Pessoa() : nome(""), cpf("") {}

void Pessoa::coletarDados() {
    std::cout << "Digite o nome da pessoa: ";
    std::getline(std::cin, nome);
    
    std::cout << "Digite o CPF da pessoa (somente numeros): ";
    std::getline(std::cin, cpf);
}


void Pessoa::cadastrarNoArquivo() {
    std::ofstream arquivo("dados.txt", std::ios::app); 
    if (arquivo.is_open()) {
        arquivo << "Nome: " << nome << std::endl;
        arquivo << "CPF: " << cpf << std::endl;
        arquivo << "-----------------------------" << std::endl;
        arquivo.close();
        std::cout << "Cadastro Realizado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }
}

void Pessoa::ListarArquivo() {
    std::ifstream arquivo("dados.txt"); 
    if (arquivo.is_open()) {
        std::string linha;
        std::cout << "\nClientes incritos:\n";
        while (std::getline(arquivo, linha)) {
            std::cout << linha << std::endl; 
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura!" << std::endl;
    }
}

int main() {
    Pessoa pessoa;
    int selecao;
    while (true) {
        std::cout << "\nMenu Principal - Sistema de Cadastro\n";
        std::cout << "1. Cadastrar Novo Cliente\n";
        std::cout << "2. Listar Clientes Cadastrados\n";
        std::cout << "3. Sair\n";
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> selecao) || selecao < 1 || selecao > 3) {
            std::cout << "Opcao invalida. Tente novamente: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        switch (selecao) {
        case 1:
            pessoa.coletarDados();
            pessoa.cadastrarNoArquivo();
            break;
        case 2:
            pessoa.ListarArquivo();
            break;
        case 3:
            std::cout << "Encerrando o sistema. Ate mais!\n";
            return 0;
        }
    }
}



