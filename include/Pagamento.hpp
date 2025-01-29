#ifndef PAGAMENTO_HPP
#define PAGAMENTO_HPP

#include <iostream>
#include <memory>
#include <limits>
#include <string>
#include "Locacoes.hpp"

// Classe base abstrata Pagamento
class Pagamento {
public:
    virtual void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) = 0;
    virtual ~Pagamento() {}
};

// Classe PagamentoDinheiro
class PagamentoDinheiro : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override;
};

// Classe PagamentoCartaoCredito
class PagamentoCartaoCredito : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override;
};

// Classe PagamentoCartaoDebito
class PagamentoCartaoDebito : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override;
};

// Classe PagamentoPix
class PagamentoPix : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override;
};

// Classe PagamentoEscambo
class PagamentoEscambo : public Pagamento {
public:
    void realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) override;
};

// Classe para cálculo de multas por atraso
class Multa {
public:
    // Calcula a multa com base no atraso e no número de dias permitidos
    static double calcularMulta(const Locacao& locacao, int diasPermitidos);

    // Função auxiliar para obter a data atual no formato "YYYY-MM-DD"
    static std::string getDataAtual();
};

#endif // PAGAMENTO_HPP

