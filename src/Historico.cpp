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

