#ifndef PROMOCAO_HPP
#define PROMOCAO_HPP

#include <string>
#include <vector>
#include "Historico.hpp"
#include "Cliente.hpp"

class Promocao {
private:
    std::string descricao;
    std::string tipo; // Ex.: "desconto percentual", "pontos de fidelidade"
    double valor; // Ex.: 10.0 para 10% de desconto ou 100 pontos
    std::string data_inicio;
    std::string data_fim;
    std::vector<int> clientes_aplicados; // IDs dos clientes que utilizaram a promoção

public:
    Promocao(const std::string& desc, const std::string& tipo, double valor, 
             const std::string& inicio, const std::string& fim);

    void aplicarPromocao(Historico& historico);
    void adicionarCliente(int clienteId);
    void exibirDetalhes() const;
};

#endif // PROMOCAO_HPP