#include <string>
#include <regex>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

// Funcao para validar formato de telefone
bool validarTelefone(const std::string& telefone) {
    std::regex telefoneRegex("\\(\\d{2}\\)\\d{5}-\\d{4}");
    return std::regex_match(telefone, telefoneRegex);
}

// Funcao para validar formato de email
bool validarEmail(const std::string& email) {
    std::regex emailRegex("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
    return std::regex_match(email, emailRegex);
}

// Funcao para salvar dados em um arquivo
void salvarDadosEmArquivo(const std::string& nomeArquivo, const std::vector<std::string>& dados) {
    std::ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        for (const auto& linha : dados) {
            arquivo << linha << "\n";
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para escrita: " << nomeArquivo << "\n";
    }
}

// Funcao para ler dados de um arquivo
std::vector<std::string> lerDadosDeArquivo(const std::string& nomeArquivo) {
    std::vector<std::string> dados;
    std::ifstream arquivo(nomeArquivo);
    std::string linha;
    if (arquivo.is_open()) {
        while (std::getline(arquivo, linha)) {
            dados.push_back(linha);
        }
        arquivo.close();
    } else {
        std::cerr << "Erro ao abrir o arquivo para leitura: " << nomeArquivo << "\n";
    }
    return dados;
}

// Funcao para calcular diferenca de dias entre duas datas
int calcularDiasDeDiferenca(const std::tm& data1, const std::tm& data2) {
    std::time_t t1 = std::mktime(const_cast<std::tm*>(&data1));
    std::time_t t2 = std::mktime(const_cast<std::tm*>(&data2));
    return static_cast<int>(std::difftime(t2, t1) / (60 * 60 * 24));
}

// Funcao para calcular multa por atraso
double calcularMultaPorAtraso(int diasAtraso, double valorPorDia) {
    return diasAtraso * valorPorDia;
}

// Funcao para validar CPF
bool validarCPF(const std::string& cpf) {
    // Verifica se o CPF tem exatamente 11 digitos
    std::regex regexCpf("\\d{11}");
    if (!std::regex_match(cpf, regexCpf)) {
        return false;
    }

    // Calculo do primeiro digito verificador
    int soma1 = 0;
    int peso1[] = {10, 9, 8, 7, 6, 5, 4, 3, 2};
    for (int i = 0; i < 9; ++i) {
        soma1 += (cpf[i] - '0') * peso1[i];
    }
    int digito1 = 11 - (soma1 % 11);
    if (digito1 >= 10) digito1 = 0;

    // Calculo do segundo digito verificador
    int soma2 = 0;
    int peso2[] = {11, 10, 9, 8, 7, 6, 5, 4, 3, 2};
    for (int i = 0; i < 10; ++i) {
        soma2 += (cpf[i] - '0') * peso2[i];
    }
    int digito2 = 11 - (soma2 % 11);
    if (digito2 >= 10) digito2 = 0;

    // Verifica se os digitos calculados estao corretos
    return (cpf[9] - '0' == digito1 && cpf[10] - '0' == digito2);
}

// Programa principal para testar as funcoes
int main() {
    std::string telefone, email, cpf;

    // Solicita o telefone do cliente
    std::cout << "Digite o telefone do cliente no formato (XX)XXXXX-XXXX: ";
    std::cin >> telefone;
    if (validarTelefone(telefone)) {
        std::cout << "Telefone valido.\n";
    } else {
        std::cout << "Telefone invalido.\n";
    }

    // Solicita o email do cliente
    std::cout << "Digite o email do cliente: ";
    std::cin >> email;
    if (validarEmail(email)) {
        std::cout << "Email valido.\n";
    } else {
        std::cout << "Email invalido.\n";
    }

    // Solicita o CPF do cliente
    std::cout << "Digite o CPF do cliente (somente numeros): ";
    std::cin >> cpf;
    if (validarCPF(cpf)) {
        std::cout << "CPF valido.\n";
    } else {
        std::cout << "CPF invalido.\n";
    }

    return 0;
}

