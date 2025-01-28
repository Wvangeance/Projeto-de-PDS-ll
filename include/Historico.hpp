#ifndef HISTORICO_HPP
#define HISTORICO_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class Historico {
private:
std::vector<std::string> atividades;

public:
//Adicionar atividade
void adicionarAtividade(const std::string& atividade);

//Listar atividades
void listarAtividades() const;

//Salvar histórico 
void salvarHistoricoEmArquivo(const std::string& nomeArquivo) const;

//Carregar histórico 
void carregarHistoricoDeArquivo(const std::string& nomeArquivo);
};

#endif // HISTORICO_HPP
