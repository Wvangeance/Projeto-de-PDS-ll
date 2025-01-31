#include "Historico.hpp"
#include <iostream>

// Adiciona um registro ao histórico
void Historico::adicionarRegistro(const std::string& registro) {
    registros.push_back(registro);
}

// Exibe todo o histórico armazenado
void Historico::exibirHistorico() const {
    std::cout << "===== Histórico de Locações e Pagamentos =====" << std::endl;
    if (registros.empty()) {
        std::cout << "Nenhum registro encontrado." << std::endl;
    } else {
        for (const auto& registro : registros) {
            std::cout << registro << std::endl;
        }
    }
}
