#include "Cliente.hpp"

// Construtor padrão
Pessoa::Pessoa() : nome(""), cpf(""), permitidoLocacao(false), id(0) {}

// Coletar dados do usuário
void Pessoa::coletarDados() {
    std::cout << "Digite o nome da pessoa: ";
    std::getline(std::cin, nome);

    std::cout << "Digite o CPF da pessoa (somente números): ";
    std::getline(std::cin, cpf);

    char resposta;
    std::cout << "Permitir locação? (S/N): ";
    std::cin >> resposta;
    permitidoLocacao = (resposta == 'S' || resposta == 's');

    // Limpar buffer de entrada
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Digite o ID da pessoa: ";
    std::cin >> id;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Cadastrar dados no arquivo
void Pessoa::cadastrarNoArquivo() {
    std::ofstream arquivo("dados.txt", std::ios::app);
    if (arquivo.is_open()) {
        arquivo << "Nome: " << nome << "\n";
        arquivo << "CPF: " << cpf << "\n";
        arquivo << "Permitido Locação: " << (permitidoLocacao ? "Sim" : "Não") << "\n";
        arquivo << "ID: " << id << "\n";
        arquivo << "-----------------------------\n";
        arquivo.close();
        std::cout << "Cadastro realizado com sucesso!\n";
    } else {
        std::cerr << "Erro ao abrir o arquivo!\n";
    }
}

// Listar conteúdo do arquivo
void Pessoa::exibirDados() const {  // Adicionar const aqui
    std::ifstream arquivo("dados.txt");
    if (arquivo.is_open()) {
        std::string linha;
        std::cout << "\nClientes cadastrados:\n";
        while (std::getline(arquivo, linha)) {
            std::cout << linha << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura!\n";
    }
}

// Getters
std::string Pessoa::getNome() const {
    return nome;
}

int Pessoa::getId() const {
    return id;
}
