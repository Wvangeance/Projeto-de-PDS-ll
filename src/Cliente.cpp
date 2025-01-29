#include "Cliente.hpp"

// Construtor padrão
Pessoa::Pessoa() : nome(""), cpf(""), permitidoLocacao(false), id(0) {} // Inicializando id

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
        arquivo << "Nome: " << nome << std::endl;
        arquivo << "CPF: " << cpf << std::endl;
        arquivo << "Permitido Locação: " << (permitidoLocacao ? "Sim" : "Não") << std::endl;
        arquivo << "ID: " << id << std::endl; // Adicionando o ID ao arquivo
        arquivo << "-----------------------------" << std::endl;
        arquivo.close();
        std::cout << "Cadastro realizado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }
}

// Listar conteúdo do arquivo
void Pessoa::listarArquivo() {
    std::ifstream arquivo("dados.txt");
    if (arquivo.is_open()) {
        std::string linha;
        std::cout << "\nClientes cadastrados:\n";
        while (std::getline(arquivo, linha)) {
            std::cout << linha << std::endl;
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura!" << std::endl;
    }
}

// Editar permissão de locação
void Pessoa::editarPermissaoLocacao() {
    std::string cpfBusca;
    std::cout << "Digite o CPF do cliente que deseja editar: ";
    std::getline(std::cin, cpfBusca);

    std::ifstream arquivo("dados.txt");
    std::ostringstream temp;
    bool encontrado = false;
    std::string linha;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            temp << linha << std::endl;

            if (linha.find("CPF: " + cpfBusca) != std::string::npos) {
                encontrado = true;

                char opcao;
                std::cout << "O cliente está permitido a pegar locação? (S para Sim, N para Não): ";
                std::cin >> opcao;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                permitidoLocacao = (opcao == 'S' || opcao == 's');
                temp << "Permitido Locação: " << (permitidoLocacao ? "Sim" : "Não") << std::endl;

                // Pular a linha antiga do status no arquivo original
                std::getline(arquivo, linha);
            }
        }
        arquivo.close();

        if (encontrado) {
            std::ofstream arquivoOut("dados.txt", std::ios::trunc);
            if (arquivoOut.is_open()) {
                arquivoOut << temp.str();
                arquivoOut.close();
                std::cout << "Status de permissão de locação atualizado com sucesso!" << std::endl;
            } else {
                std::cerr << "Erro ao abrir o arquivo para regravar!" << std::endl;
            }
        } else {
            std::cout << "Cliente não encontrado!" << std::endl;
        }
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }
}

// Getter para o nome
std::string Pessoa::getNome() const {
    return nome;
}

// Getter para o ID
int Pessoa::getId() const {
    return id; // Adicionando o getter para o ID
}

// Função principal
int main() {
    Pessoa pessoa;
    int selecao;

    while (true) {
        std::cout << "\nMenu Principal - Sistema de Cadastro\n";
        std::cout << "1. Cadastrar Novo Cliente\n";
        std::cout << "2. Listar Clientes Cadastrados\n";
        std::cout << "3. Editar Permissão de Locação\n";
        std::cout << "4. Sair\n";
        std::cout << "Escolha uma opção: ";

        while (!(std::cin >> selecao) || selecao < 1 || selecao > 4) {
            std::cout << "Opção inválida. Tente novamente: ";
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
                pessoa.listarArquivo();
                break;
            case 3:
                pessoa.editarPermissaoLocacao();
                break;
            case 4:
                std::cout << "Encerrando o sistema. Até mais!\n";
                return 0;
        }
    }
}

