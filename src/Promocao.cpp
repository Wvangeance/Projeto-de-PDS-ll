#include "Promocao.hpp"
#include <iostream>

Promocao::Promocao(const std::string& desc, const std::string& tipo, double valor, 
                   const std::string& inicio, const std::string& fim)
    : descricao(desc), tipo(tipo), valor(valor), data_inicio(inicio), data_fim(fim) {}

void Promocao::aplicarPromocao(Historico& historico) {
    std::cout << "Aplicando promoção: " << descricao << std::endl;
    
    std::map<int, int>& clientesFrequentes = historico.clientesFrequentes;
    std::map<int, Pessoa>& clientes = historico.clientes;
    
    for (const auto& cliente : clientesFrequentes) {
        if (cliente.second >= 5) { // Exemplo: clientes com 5 ou mais locações
            adicionarCliente(cliente.first);
            std::cout << "Promoção aplicada ao cliente ID: " << cliente.first 
                      << " (" << clientes[cliente.first].getNome() << ")" << std::endl;
        }
    }
}

void Promocao::adicionarCliente(int clienteId) {
    clientes_aplicados.push_back(clienteId);
}

void Promocao::exibirDetalhes() const {
    std::cout << "Promoção: " << descricao << " (" << tipo << ")" << std::endl;
    std::cout << "Valor: " << valor << "\nVálida de " << data_inicio << " até " << data_fim << std::endl;
    std::cout << "Clientes aplicados: ";
    for (int id : clientes_aplicados) {
        std::cout << id << " ";
    }
    std::cout<<std::endl;
}