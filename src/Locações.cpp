#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm> 
#include "Locações.hpp"

// Classe para Cliente
class Cliente {
public:
    int id;
    std::string nome;
    std::string telefone;

    Cliente(int id, const std::string& nome, const std::string& telefone)
        : id(id), nome(nome), telefone(telefone) {}
};

// Classe para Locacao
class Locacao {
public:
    int id;
    Cliente cliente;
    std::string dataLocacao;
    std::string dataDevolucao;
    bool devolvido;

    Locacao(int id, Cliente cliente, const std::string& dataLocacao, const std::string& dataDevolucao)
        : id(id), cliente(cliente), dataLocacao(dataLocacao), dataDevolucao(dataDevolucao), devolvido(false) {}

    void marcarComoDevolvido() {
        devolvido = true;
    }

    void exibirDetalhes() const {
        std::cout << "Locacao ID: " << id << "\n";
        std::cout << "Cliente: " << cliente.nome << " (Telefone: " << cliente.telefone << ")\n";
        std::cout << "Data de Locacao: " << dataLocacao << "\n";
        std::cout << "Data de Devolucao: " << dataDevolucao << "\n";
        std::cout << "Status: " << (devolvido ? "Devolvido" : "Nao devolvido") << "\n";
        std::cout << "-----------------------------\n";
    }
};

// Função para carregar dados de usuários de um arquivo
std::vector<Cliente> carregarUsuarios(const std::string& nomeArquivo) {
    std::vector<Cliente> usuarios;
    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        int id;
        std::string nome, telefone;

        while (arquivo >> id) {
            arquivo.ignore(); // Ignorar espaço ou separador
            std::getline(arquivo, nome, ';');
            std::getline(arquivo, telefone);
            usuarios.emplace_back(id, nome, telefone);
        }

        arquivo.close();
        std::cout << "Usuarios carregados do arquivo: " << nomeArquivo << "\n";
    } else {
        std::cout << "Arquivo de usuarios nao encontrado. Entrada manual sera usada.\n";
    }

    return usuarios;
}

// Função para carregar dados de filmes de um arquivo
std::vector<std::string> carregarFilmes(const std::string& nomeArquivo) {
    std::vector<std::string> filmes;
    std::ifstream arquivo(nomeArquivo);

    if (arquivo.is_open()) {
        std::string filme;

        while (std::getline(arquivo, filme)) {
            filmes.push_back(filme);
        }

        arquivo.close();
        std::cout << "Filmes carregados do arquivo: " << nomeArquivo << "\n";
    } else {
        std::cout << "Arquivo de filmes nao encontrado. Entrada manual sera usada.\n";
    }

    return filmes;
}

// Função principal para gerenciar o sistema
void menuGerenciamentoLocacoes() {
    std::vector<Cliente> usuarios = carregarUsuarios("usuarios.txt");
    std::vector<std::string> filmes = carregarFilmes("filmes.txt");
    std::vector<Locacao> locacoes;

    int escolha;
    do {
        std::cout << "\nSistema de Gerenciamento de Locacoes\n";
        std::cout << "1. Criar Nova Locacao\n";
        std::cout << "2. Listar Locacoes\n";
        std::cout << "3. Atualizar Status de Devolucao\n";
        std::cout << "4. Sair\n";
        std::cout << "Escolha uma opcao: ";
        std::cin >> escolha;

        if (escolha == 1) {
            int clienteId;
            std::string clienteNome, clienteTelefone, dataLocacao, dataDevolucao;

            if (!usuarios.empty()) {
                std::cout << "Clientes disponiveis:\n";
                for (const auto& usuario : usuarios) {
                    std::cout << usuario.id << ": " << usuario.nome << " (" << usuario.telefone << ")\n";
                }
                std::cout << "Informe o ID do Cliente: ";
                std::cin >> clienteId;

                auto it = std::find_if(usuarios.begin(), usuarios.end(),
                                       [clienteId](const Cliente& c) { return c.id == clienteId; });

                if (it != usuarios.end()) {
                    clienteNome = it->nome;
                    clienteTelefone = it->telefone;
                } else {
                    std::cout << "Cliente nao encontrado. Entrada manual sera usada.\n";
                    std::cin.ignore(); // Limpar buffer do cin
                    std::cout << "Informe o Nome do Cliente: ";
                    std::getline(std::cin, clienteNome);
                    std::cout << "Informe o Telefone do Cliente: ";
                    std::getline(std::cin, clienteTelefone);
                }
            } else {
                std::cin.ignore(); // Limpar buffer do cin
                std::cout << "Informe o Nome do Cliente: ";
                std::getline(std::cin, clienteNome);
                std::cout << "Informe o Telefone do Cliente: ";
                std::getline(std::cin, clienteTelefone);
            }

            Cliente cliente(clienteId, clienteNome, clienteTelefone);

            std::cout << "Informe a data de locacao (dd/mm/aaaa): ";
            std::cin >> dataLocacao;
            std::cout << "Informe a data de devolucao (dd/mm/aaaa): ";
            std::cin >> dataDevolucao;

            locacoes.emplace_back(locacoes.size() + 1, cliente, dataLocacao, dataDevolucao);
            std::cout << "Locacao criada com sucesso!\n";

        } else if (escolha == 2) {
            if (locacoes.empty()) {
                std::cout << "Nenhuma locacao registrada.\n";
            } else {
                for (const auto& locacao : locacoes) {
                    locacao.exibirDetalhes();
                }
            }

        } else if (escolha == 3) {
            int locacaoId;
            std::cout << "Digite o ID da Locacao para marcar como devolvida: ";
            std::cin >> locacaoId;

            if (locacaoId <= 0 || locacaoId > static_cast<int>(locacoes.size())) {
                std::cout << "ID de Locacao invalido.\n";
            } else {
                locacoes[locacaoId - 1].marcarComoDevolvido();
                std::cout << "Status atualizado para devolvido.\n";
            }
        }
    } while (escolha != 4);
}

// Função principal
int main() {
    menuGerenciamentoLocacoes();
    return 0;
}