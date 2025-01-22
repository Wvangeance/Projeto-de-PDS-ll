#include "utilitarios.hpp"
#include <regex>
#include <fstream>

#include <string>
#include <iostream>

//Função para validar formato de telefone
bool validarTelefone (const std::string& telefone) {
  std::regex telefoneRegex ("\\d{3}-\\d{3}-\\d{4}");
  return std::regex_match (telefone, telefoneRegex);
}

//Função para validar formato de email
bool validarEmail (const std::string& email) {
  std::regex emailRegex ("(\\x+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
  return std::regex_match (email, emailRegex);
}

//Função para salvar dados em um arquivo
void salvarDadosEmArquivo (const std::string& nomeArquivo, const std::vector<std::string>& dados) {
  std::ofstream arquivo (nomeArquivo);
  if (arquivo.is_open()) {
    for (const auto& linha : dados) {
      arquivo << linha << "\n";
    }
    arquivo.close ();
  }
}

//Função para ler dados de um arquivo
std::vector<std::string> lerDadosDeArquivo (const std::string& nomeArquivo) {
  std::vector<std::string> dados;
std::ifstream arquivo (nomrArquivo);
std::string linha;
if (arquivo.is_open()) {
  while(std::getline(arquivo, linha)){
    dados.push_back (linha);
  }
}
arquivo.close();
}
return dados;
}

//Função para calcular diferença de dias entre duas datas
int calcularDiasDeDiferenca (const std::tm& data1, const std::tm& data2) {
  std::time_t t1 = std::mktime(const_cast<std::tm*>(&data1));
  std::time_t t2 = std::mktime(const_cast<std::tm*>(&data2));
return std::difftime (t2,t1)/(60*60*24);
}

//Função para calcular multa por atraso
double calcularMultaPorAtraso (int diasAtraso, double valorPorDia) {
  return diasAtraso * valorPorDia;
}

//Validação de CPF
bool validarCPF (conststd::string& cpf){
  //Verifica o tamanho do CPF
  std::regex regexCpf("\\d{11}");
  if(!std::regex_match(cpf,regexCpf)){
    return false;
  }

//Calculo do primeiro digito verificador
int soma1 = 0;
int peso[] = {10,9,8,7,6,5,4,3,2}
for (int i = 0; i < 9; ++i){
  soma1 += (cpf[i] - '0' * peso1[i];
}

int digito1 = 11 - (soma1 % 11);
if (digito1 >= 10) digito1 = 0;

//Calculo do segundo digito verificador
int soma2 = 0;
int peso2[] = {11,10,9,8,7,6,5,4,3,2};
for (int i = 0; i < 10; ++i){
  soma2 += (cpf[i] - '0') * peso2[i];
}
int digito2 = 11 - (soma2 % 11);
if (digito2 >= 10) digito2 = 0;

//Verifica se os digitos calculados estão corretos
return (cpf[9] - '0' == digito1 && cpf[10] - '0' == digita2);
}
//Fim do verificação de CPF
