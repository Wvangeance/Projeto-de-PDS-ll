#include "utilitarios.hpp"
#include <regex>
#include <fstream>

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
dados.push_back (linha);
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
  return diasAtraso*valorPorDia;
}
