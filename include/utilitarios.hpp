#ifndef UTILITARIOS_HPP
#define UTILITARIOS_HPP

#include <string>
#include <vector>
#include <ctime>

bool validarTelefone (const std::string& telefone);
bool validarEmail (const std::string& email);
void salvarDadosEmArquivo (const std::string& nomeArquivo, const std::vector<std::string>& dados);
std::vector<std::string> lerDadosArquivo (const std::string& nomeArquivo);
int calcularDiasDeDiferenca (const std::tm& data1, const std::tm& data2);
double calcularMultaPorAtraso (int diasAtraso, double valorPorDia);

#endif // ULTILITARIOS_HPP
