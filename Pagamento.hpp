#ifndef LOCADORA_HPP
#define LOCADORA_HPP

#include <iostream>
#include <memory>
#include <limits>
#include <cctype>

// Classe base abstrata Pagamento
class Pagamento {
public:
    virtual void realizarPagamento(double valor, bool &pagamentoRealizado) = 0;
    virtual ~Pagamento() {}
};

// Classe PagamentoDinheiro
class PagamentoDinheiro : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe PagamentoCartaoCredito
class PagamentoCartaoCredito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe PagamentoCartaoDebito
class PagamentoCartaoDebito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe PagamentoPix
class PagamentoPix : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe PagamentoEscambo
class PagamentoEscambo : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe para calculo de multas por atraso
class Multa {
public:
    static double calcularMulta(double valorEmprestimo, int diasAtraso, int diasPermitidos);
};

// Classe Locadora
class Locadora {
private:
    std::unique_ptr<Pagamento> metodoPagamento;

public:
    Locadora(std::unique_ptr<Pagamento> metodo);

    void processarPagamento(double valor, bool &pagamentoRealizado);
    void alterarMetodoPagamento(std::unique_ptr<Pagamento> novoMetodo);
};

#endif // LOCADORA_HPP

