#ifndef PROMOCAO_HPP
#define PROMOCAO_HPP

#include "Cliente.hpp"

class Promocao {
public:
    // Aplica desconto com base no ID do cliente (simulando um programa de fidelidade)
    static double aplicarDesconto(const Pessoa& cliente, double precoOriginal);
    
    // Retorna a porcentagem de desconto com base no ID
    static double calcularDesconto(int idCliente);
};

#endif // PROMOCAO_HPP
