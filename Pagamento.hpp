#ifndef PAGAMENTO_HPP
#define PAGAMENTO_HPP

#include <memory>
#include <string>

// Classe base abstrata Pagamento
class Pagamento {
public:
    virtual void realizarPagamento(double valor, bool &pagamentoRealizado) = 0;
    virtual ~Pagamento() {}
};

// Classes derivadas de Pagamento
class PagamentoDinheiro : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

class PagamentoCartaoCredito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

class PagamentoCartaoDebito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

class PagamentoPix : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

class PagamentoEscambo : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override;
};

// Classe para cálculo de multas por atraso
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

#endif // PAGAMENTO_HPP
