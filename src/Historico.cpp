#include "Historico.hpp"

//Nova atividade
vpid Historico::adicionarAtividade(const std::string& atividade) {
  atividade.push_back(atividade);
}

//Listar atividades
void Historico::listarAtividades() const {
  std::cout<<"Histórico de Atividades:\n";
for (const auto& atividade : atividades) {
std::cout<<"- "<<atividade<<"\n";
}
}

\\Salvar histórico
void Historico::salvarHistoricoEmArquivo(const std::string& nomeArquivo) const {
  std::ofstream arquivo(nomeArquivo);
if (arquivo.is_open()) {
for (const auto& atividade : atividades) {
arquivo << atividade << "\n";
}
arquivo.close();
} else {
std::cerr << "Erro ao abrir arquivo para salvar o histórico.\n";
}
}

//Carregar histórico 
void Historico::carregarHistoricoDeArquivo(const std::string& nomeArquivo) {
  std::ifstream arquivo(nomeArquivo);
std::string linha;
if (arquivo.is_open()) {
while (std::getline(arquivo, linha)) {
atividades.push_back(linha);
}
arquivo.close();
} else {
std::cerr << "Erro ao abrir o arquivo para carregar histórico.\n";
}
}
