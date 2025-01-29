#include <iostream>
#include <vector>
#include <string>
#include <Sistema.hpp>

// Classe Pessoa
class Pessoa {
public:
    std::string nome;
    Pessoa(std::string nome) : nome(nome) {}
};

// Classe Filme
class Filme {
public:
    std::string titulo;
    int ano;
    bool disponivel;
    Filme(std::string titulo, int ano) : titulo(titulo), ano(ano), disponivel(true) {}
};

// Classe Historico
class Historico {
public:
    std::vector<std::string> registros;
    void adicionarRegistro(std::string registro) {
        registros.push_back(registro);
    }
    void mostrarHistorico() {
        for (const auto& registro : registros) {
            std::cout << registro << std::endl;
        }
    }
};

// Classe Locacao
class Locacao {
public:
    static void alugarFilme(Pessoa& cliente, Filme& filme, Historico& historico) {
        if (filme.disponivel) {
            filme.disponivel = false;
            historico.adicionarRegistro(cliente.nome + " alugou o filme: " + filme.titulo);
            std::cout << "Filme alugado com sucesso!\n";
        } else {
            std::cout << "Filme indisponível!\n";
        }
    }

    static void devolverFilme(Pessoa& cliente, Filme& filme, Historico& historico) {
        filme.disponivel = true;
        historico.adicionarRegistro(cliente.nome + " devolveu o filme: " + filme.titulo);
        std::cout << "Filme devolvido com sucesso!\n";
    }
};

// Classe Sistema de Locadora
class SistemaLocadora {
private:
    std::vector<Pessoa> clientes;
    std::vector<Filme> filmes;
    Historico historico;

public:
    void adicionarCliente(std::string nome) {
        clientes.push_back(Pessoa(nome));
    }
    
    void adicionarFilme(std::string titulo, int ano) {
        filmes.push_back(Filme(titulo, ano));
    }
    
    void listarFilmes() {
        for (const auto& filme : filmes) {
            std::cout << filme.titulo << " (" << filme.ano << ") - "
                      << (filme.disponivel ? "Disponível" : "Indisponível") << std::endl;
        }
    }
    
    void alugarFilme(std::string nomeCliente, std::string tituloFilme) {
        for (auto& cliente : clientes) {
            if (cliente.nome == nomeCliente) {
                for (auto& filme : filmes) {
                    if (filme.titulo == tituloFilme) {
                        Locacao::alugarFilme(cliente, filme, historico);
                        return;
                    }
                }
            }
        }
        std::cout << "Cliente ou filme não encontrado!\n";
    }
    
    void devolverFilme(std::string nomeCliente, std::string tituloFilme) {
        for (auto& cliente : clientes) {
            if (cliente.nome == nomeCliente) {
                for (auto& filme : filmes) {
                    if (filme.titulo == tituloFilme) {
                        Locacao::devolverFilme(cliente, filme, historico);
                        return;
                    }
                }
            }
        }
        std::cout << "Cliente ou filme não encontrado!\n";
    }
    
    void mostrarHistorico() {
        historico.mostrarHistorico();
    }
};

int main() {
    SistemaLocadora sistema;
    sistema.adicionarCliente("João");
    sistema.adicionarFilme("Matrix", 1999);
    sistema.adicionarFilme("Vingadores", 2012);
    
    sistema.listarFilmes();
    
    sistema.alugarFilme("João", "Matrix");
    sistema.listarFilmes();
    
    sistema.devolverFilme("João", "Matrix");
    sistema.listarFilmes();
    
    sistema.mostrarHistorico();
    
    return 0;
}