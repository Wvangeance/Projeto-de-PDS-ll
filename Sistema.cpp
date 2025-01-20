#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <Sistema.hpp>

class Filme {
private:
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;
    int quantidadeDisponivel;

public:
    Filme(const std::string& titulo, const std::string& genero, int anoLancamento, int classificacaoEtaria, int quantidadeDisponivel)
        :  titulo(titulo), generos(generos), anoLancamento(anoLancamento), classificacaoEtaria(classificacaoEtaria), quantidadeDisponivel(quantidadeDisponivel);

    std::string getTitulo() const { return titulo; }
    bool estaDisponivel() const { return classificacaoEtaria > 0; }
    void alugar() { if (classificacaoEtaria > 0) --classificacaoEtaria; }
    void devolver() { ++classificacaoEtaria; }
};

class Cadastro_Cliente {
private:
    int pessoa;
    std::string nome;
    std::string cpf;

public:
    Cadastro_Cliente(int pessoa, const std::string& nome, const std::string& cpf)
        : pessoa(pessoa), nome(nome), cpf(cpf) {}

    int getPessoa() const { return pessoa; }
    std::string getNome() const { return nome; }
};

class Locacao {
private:
    int id;
    int idCliente;
    int idFilme;
    std::string dataLocacao;
    std::string dataDevolucao;
    bool devolvido;

public:
    Locacao(int id, int idCliente, int idFilme, const std::string& dataLocacao, const std::string& dataDevolucao)
        : id(id), idCliente(idCliente), idFilme(idFilme), dataLocacao(dataLocacao), dataDevolucao(dataDevolucao), devolvido(false) {}

    int getId() const { return id; }
    int getIdCliente() const { return idCliente; }
    int getIdFilme() const { return idFilme; }
};

class Pagamento {
private:
    int id;
    int idCliente;
    double valor;
    std::string dataPagamento;

public:
    Pagamento(int id, int idCliente, double valor, const std::string& dataPagamento)
        : id(id), idCliente(idCliente), valor(valor), dataPagamento(dataPagamento) {}

    int getId() const { return id; }
    double getValor() const { return valor; }
};


class Sistema {
private:
    std::vector<Filme> filmes;
    std::vector<Cadastro_Cliente> clientes;
    std::vector<Locacao> locacoes;
    std::vector<Pagamento> pagamentos;

    int proxIdLocacao = 1;
    int proxIdPagamento = 1;

public:
    // Adicionar entidades
    void adicionarFilme(const Filme& filme) { filmes.push_back(filme); }
    void adicionarCliente(const Cliente& cliente) { clientes.push_back(cliente); }

    // Listar filmes
    void listarFilmes() const {
        for (const auto& filme : filmes) {
            std::cout << "ID: " << filme.getId() << ", Título: " << filme.getTitulo()
                      << ", Disponível: " << (filme.estaDisponivel() ? "Sim" : "Não") << '\n';
        }
    }

    // Realizar locação
    void realizarLocacao(int idCliente, int idFilme, const std::string& dataLocacao, const std::string& dataDevolucao) {
        auto itCliente = std::find_if(clientes.begin(), clientes.end(), [idCliente](const Cliente& c) {
            return c.getId() == idCliente;
        }); 

        auto itFilme = std::find_if(filmes.begin(), filmes.end(), [idFilme](const Filme& f) {
            return f.getId() == idFilme && f.estaDisponivel();
        });

        if (itCliente != clientes.end() && itFilme != filmes.end()) {
            locacoes.emplace_back(proxIdLocacao++, idCliente, idFilme, dataLocacao, dataDevolucao);
            itFilme->alugar();
            std::cout << "Locação realizada com sucesso!\n";
        } else {
            std::cout << "Locação não pôde ser realizada. Verifique os dados.\n";
        }
    }

    // Processar pagamento
    void registrarPagamento(int idCliente, double valor, const std::string& dataPagamento) {
        auto itCliente = std::find_if(clientes.begin(), clientes.end(), [idCliente](const Cliente& c) {
            return c.getId() == idCliente;
        });

        if (itCliente != clientes.end()) {
            pagamentos.emplace_back(proxIdPagamento++, idCliente, valor, dataPagamento);
            std::cout << "Pagamento registrado com sucesso!\n";
        } else {
            std::cout << "Cliente não encontrado.\n";
        }
    }
};