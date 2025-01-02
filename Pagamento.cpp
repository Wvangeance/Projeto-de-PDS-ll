#include <iostream>
#include <memory>
#include <cmath>
#include <string>

// Classe base abstrata Pagamento
class Pagamento {
public:
    virtual void realizarPagamento(double valor, bool &pagamentoRealizado) = 0;
    virtual ~Pagamento() {}
};

// Classe PagamentoDinheiro
class PagamentoDinheiro : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override {
        double valorPago;
        std::cout << "O valor total e R$ " << valor << ".\nInsira o valor dado pelo cliente: ";
        std::cin >> valorPago;

        if (valorPago > valor) {
            std::cout << "Pagamento realizado com sucesso. Troco: R$ " << valorPago - valor << ".\n";
            pagamentoRealizado = true;
        } else if (valorPago == valor) {
            std::cout << "Pagamento realizado com sucesso.\n";
            pagamentoRealizado = true;
        } else {
            std::cout << "Valor insuficiente! Pagamento nao realizado.\n";
            pagamentoRealizado = false;
        }
    }
};

// Classe PagamentoCartaoCredito
class PagamentoCartaoCredito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override {
        std::cout << "Pagamento de R$ " << valor << " realizado com cartao de credito.\n";
        pagamentoRealizado = true;
    }
};

// Classe PagamentoCartaoDebito
class PagamentoCartaoDebito : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override {
        std::cout << "Pagamento de R$ " << valor << " realizado com cartao de debito.\n";
        pagamentoRealizado = true;
    }
};

// Classe PagamentoPix
class PagamentoPix : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override {
        std::cout << "Pagamento de R$ " << valor << " realizado via Pix.\n";
        pagamentoRealizado = true;
    }
};

// Classe PagamentoEscambo
class PagamentoEscambo : public Pagamento {
public:
    void realizarPagamento(double valor, bool &pagamentoRealizado) override {
        int escolhaItem;
        std::cout << "Escolha o item de troca para realizar o escambo:\n";
        std::cout << "1. Livro do Pablo Marcal (adicional de 6 meses de carne de R$ 120)\n";
        std::cout << "2. Tres espetinhos de carne de gato\n";
        std::cout << "3. Pista Hot Wheels (30 dias sem multa, multa apos esse periodo)\n";
        std::cout << "4. Carrinho de compras\n";
        std::cout << "5. 1g de antimateria\n";
        std::cin >> escolhaItem;

        switch (escolhaItem) 
        {
        case 1:
            std::cout << "Escambo aceito: Livro do Pablo Marcal. Alem do livro voce devera pagar um carne de R$ 120 por 6 meses.\n";
            pagamentoRealizado = true;
            break;
        case 2:
            std::cout << "Escambo aceito: Tres espetinhos de carne de gato. Pagamento realizado com sucesso.\n";
            pagamentoRealizado = true;
            break;
        case 3:
            std::cout << "Escambo aceito: Pista Hot Wheels. Voce tem 30 dias para devolver o filme sem multa.\n";
            pagamentoRealizado = true;
            break;
        case 4:
            std::cout << "Escambo aceito: Carrinho de compras. Pagamento realizado com sucesso.\n";
            pagamentoRealizado = true;
            break;
        case 5:
            std::cout << "Escambo aceito: 1g de antimateria. Pagamento realizado com sucesso. Cuidado com reacoes perigosas.\n";
            pagamentoRealizado = true;
            break;
        default:
            std::cout << "Opcao invalida. Tente novamente.\n";
            pagamentoRealizado = false;
        }
    }
};

// Classe para calculo de multas por atraso
class Multa {
public:
    static double calcularMulta(double valorEmprestimo, int diasAtraso, int diasPermitidos) {
        if (diasAtraso <= diasPermitidos) {
            return 0.0; // Sem multa dentro do prazo
        }
        double multaFixa = valorEmprestimo * 0.4; // Multa fixa de 40%
        double juros = valorEmprestimo * 0.01 * (diasAtraso - diasPermitidos); // Juros de 1% por dia apos o prazo permitido
        double multaTotal = multaFixa + juros;
        return (multaTotal > valorEmprestimo) ? valorEmprestimo : multaTotal; // Limite da multa
    }
};

// Classe Locadora
class Locadora {
private:
    std::unique_ptr<Pagamento> metodoPagamento;

public:
    Locadora(std::unique_ptr<Pagamento> metodo)
        : metodoPagamento(std::move(metodo)) {}

    void processarPagamento(double valor, bool &pagamentoRealizado) {
        metodoPagamento->realizarPagamento(valor, pagamentoRealizado);
    }

    void alterarMetodoPagamento(std::unique_ptr<Pagamento> novoMetodo) {
        metodoPagamento = std::move(novoMetodo);
    }
};

int main() {
    const double precoLancamento = 15.0;
    const double precoForaCartaz = 10.0;

    while (true) {
        int escolhaFilme;
        double valorEmprestimo = 0;

        std::cout << "\nBem-vindo a locadora!\n";
        std::cout << "Escolha o tipo de filme que deseja alugar:\n";
        std::cout << "1. Filme recem-lancado (R$ 15.00 por 2 dias)\n";
        std::cout << "2. Filme fora de cartaz (R$ 10.00 por 2 dias)\n";
        std::cin >> escolhaFilme;

        if (escolhaFilme == 1) {
            valorEmprestimo = precoLancamento;
        } else if (escolhaFilme == 2) {
            valorEmprestimo = precoForaCartaz;
        } else {
            std::cout << "Opcao invalida. Tente novamente.\n";
            continue;
        }

        std::cout << "O valor do emprestimo e R$ " << valorEmprestimo << ".\n";

        Locadora locadora(std::make_unique<PagamentoDinheiro>());

        int metodoPagamento;
        bool pagamentoRealizado = false;
        int diasPermitidos = 2; // Por padrão, 2 dias permitidos

        while (!pagamentoRealizado) {
            std::cout << "\nEscolha o metodo de pagamento:\n";
            std::cout << "1. Dinheiro\n";
            std::cout << "2. Cartao de credito\n";
            std::cout << "3. Cartao de debito\n";
            std::cout << "4. Pix\n";
            std::cout << "5. Escambo\n";
            std::cin >> metodoPagamento;

            if (metodoPagamento == 5) {
                locadora.alterarMetodoPagamento(std::make_unique<PagamentoEscambo>());
                locadora.processarPagamento(valorEmprestimo, pagamentoRealizado);
                if (pagamentoRealizado) {
                    std::cout << "Pagamento concluido por escambo.\n";
                    if (diasPermitidos == 30) {
                        diasPermitidos = 30; // Configurar 30 dias apenas para escambo com pista de Hot Wheels
                    }
                }
            } else {
                switch (metodoPagamento) {
                case 1:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoDinheiro>());
                    break;
                case 2:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoCartaoCredito>());
                    break;
                case 3:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoCartaoDebito>());
                    break;
                case 4:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoPix>());
                    break;
                default:
                    std::cout << "Opcao invalida. Tente novamente.\n";
                    continue;
                }

                locadora.processarPagamento(valorEmprestimo, pagamentoRealizado);
            }
        }

        // Simulação de devolução
        int diasAtraso;
        std::cout << "\nDevolucao do filme:\n";
        std::cout << "Quantos dias apos o emprestimo o filme foi devolvido? ";
        std::cin >> diasAtraso;

        double multa = Multa::calcularMulta(valorEmprestimo, diasAtraso, diasPermitidos);
        if (multa > 0) {
            std::cout << "Multa por atraso: R$ " << multa << ".\n";

            pagamentoRealizado = false;
            while (!pagamentoRealizado) {
                std::cout << "Escolha o metodo de pagamento para a multa:\n";
                std::cout << "1. Dinheiro\n";
                std::cout << "2. Cartao de credito\n";
                std::cout << "3. Cartao de debito\n";
                std::cout << "4. Pix\n";
                std::cin >> metodoPagamento;

                switch (metodoPagamento) {
                case 1:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoDinheiro>());
                    break;
                case 2:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoCartaoCredito>());
                    break;
                case 3:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoCartaoDebito>());
                    break;
                case 4:
                    locadora.alterarMetodoPagamento(std::make_unique<PagamentoPix>());
                    break;
                default:
                    std::cout << "Opcao invalida. Tente novamente.\n";
                    continue;
                }

                locadora.processarPagamento(multa, pagamentoRealizado);
            }
        } else {
            std::cout << "Devolucao realizada sem multas.\n";
        }

        int continuar;
        std::cout << "Deseja realizar outro emprestimo? (1. Sim, 2. Nao): ";
        std::cin >> continuar;
        if (continuar != 1) {
            break;
        }
    }

    std::cout << "Obrigado por utilizar a locadora. Ate a proxima!\n";
    return 0;
}
