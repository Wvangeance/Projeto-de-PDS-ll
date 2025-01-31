#include "Promocao.hpp"

// Aplica desconto ao preço original baseado no ID do cliente
double Promocao::aplicarDesconto(const Pessoa& cliente, double precoOriginal) {
    double desconto = calcularDesconto(cliente.getId());
    return precoOriginal * (1 - desconto / 100); // Aplica desconto percentual
}

// Calcula a porcentagem de desconto com base no ID (simulando fidelidade)
double Promocao::calcularDesconto(int idCliente) {
    if (idCliente % 10 == 0) { // Exemplo: IDs múltiplos de 10 recebem 10% de desconto
        return 10.0;
    }
    return (idCliente % 10); // O desconto será baseado no último dígito do ID
}
