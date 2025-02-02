#ifndef HISTORICO_HPP
#define HISTORICO_HPP

#include <vector>
#include <string>

class Historico {
private:
    std::vector<std::string> registros;

public:
    // Adiciona um registro ao histórico
    void adicionarRegistro(const std::string& registro);
    // Exibe todo o histórico armazenado
    void exibirHistorico() const;
};

#endif // HISTORICO_HPP
