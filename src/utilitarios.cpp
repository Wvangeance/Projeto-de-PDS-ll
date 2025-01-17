#include "utilitarios.hpp"
#include <regex>
#include <fstream>

//Função para validar formato de telefone

bool validarTelefone (const std::string& telefone) {
  std::regex telefoneRegex ("\\d{3}-\\d{3}-\\d{4}");
returno std::regex_match (telefone, telefoneRegex);
}

//Função para validar formato de email

bool validarEmail (const std::string& email) {
  std::regex emailRegex ("(\\x+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
return std::regex_match (email, emailRegex);
}

Função para salvar dados em um arquivo

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
