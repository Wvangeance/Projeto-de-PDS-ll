#include "Cliente.hpp"

Pessoa::Pessoa() : nome(""), cpf(""), permitidoLocacao(false) {}

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
        arquivo << "Permitido Locacao: " << (permitidoLocacao ? "Sim" : "Nao") << std::endl;
        arquivo << "-----------------------------" << std::endl;
        arquivo.close();
        std::cout << "Cadastro Realizado com sucesso!" << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo!" << std::endl;
    }
}

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

void Pessoa::editarPermissaoLocacao() {
    std::string cpfBusca;
    std::cout << "Digite o CPF do cliente que deseja editar: ";
    std::getline(std::cin, cpfBusca);

    std::ifstream arquivo("dados.txt");
    std::ostringstream temp;
    bool encontrado = false;
    std::string linha;
    bool alterandoPermissao = false;

    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            temp << linha << std::endl;

            if (linha.find(cpfBusca) != std::string::npos) {
                encontrado = true;

                char opcao;
                std::cout << "O cliente está permitido a pegar locacao? (S para Sim, N para Nao): ";
                std::cin >> opcao;
                std::cin.ignore();

                permitidoLocacao = (opcao == 'S' || opcao == 's');

                temp << "Permitido Locacao: " << (permitidoLocacao ? "Sim" : "Nao") << std::endl;

                std::getline(arquivo, linha);
            }
        }
        arquivo.close();

        if (encontrado) {
            std::ofstream arquivoOut("dados.txt", std::ios::trunc);
            if (arquivoOut.is_open()) {
                arquivoOut << temp.str();
                arquivoOut.close();
                std::cout << "Status de permissão de locacao atualizado com sucesso!" << std::endl;
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
int main() {
    Pessoa pessoa;
    int selecao;
    while (true) {
        std::cout << "\nMenu Principal - Sistema de Cadastro\n";
        std::cout << "1. Cadastrar Novo Cliente\n";
        std::cout << "2. Listar Clientes Cadastrados\n";
        std::cout << "3. Editar Permissao de Locacao\n";
        std::cout << "4. Sair\n";
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> selecao) || selecao < 1 || selecao > 4) {
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
            pessoa.listarArquivo();
            break;
        case 3:
            pessoa.editarPermissaoLocacao();
            break;
        case 4:
            std::cout << "Encerrando o sistema. Ate mais!\n";
            return 0;
        }
    }
}
