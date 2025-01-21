#include <iostream>
#include <memory>
#include <limits>

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
        while (!(std::cin >> valorPago) || valorPago <= 0) {
            std::cout << "Entrada invalida. Por favor, insira um valor numerico positivo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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
        std::cout << "O valor estimado do escambo e R$ " << valor << ".\n";
        char avaliacao;
        std::cout << "O objeto para troca foi avaliado pelo balconista. Objeto aceito? (S/N): ";
        std::cin >> avaliacao;
        avaliacao = toupper(avaliacao);

        if (avaliacao == 'S') {
            std::cout << "Pagamento realizado por escambo.\n";
            pagamentoRealizado = true;
        } else {
            std::cout << "Objeto rejeitado. Pagamento nao realizado.\n";
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
        while (!(std::cin >> escolhaFilme) || (escolhaFilme != 1 && escolhaFilme != 2)) {
            std::cout << "Opcao invalida. Por favor, escolha 1 ou 2: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        valorEmprestimo = (escolhaFilme == 1) ? precoLancamento : precoForaCartaz;
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

            while (!(std::cin >> metodoPagamento) || metodoPagamento < 1 || metodoPagamento > 5) {
                std::cout << "Opcao invalida. Por favor, escolha entre 1 e 5: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

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
            case 5:
                locadora.alterarMetodoPagamento(std::make_unique<PagamentoEscambo>());
                break;
            }

            locadora.processarPagamento(valorEmprestimo, pagamentoRealizado);
        }

        // Simulacao de devolucao
        int diasAtraso;
        std::cout << "\nDevolucao do filme:\n";
        std::cout << "Quantos dias apos o emprestimo o filme foi devolvido? ";
        while (!(std::cin >> diasAtraso) || diasAtraso < 0) {
            std::cout << "Entrada invalida. Por favor, insira um numero inteiro positivo: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

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

                while (!(std::cin >> metodoPagamento) || metodoPagamento < 1 || metodoPagamento > 4) {
                    std::cout << "Opcao invalida. Por favor, escolha entre 1 e 4: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

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
                }

                locadora.processarPagamento(multa, pagamentoRealizado);
            }
        } else {
            std::cout << "Devolucao realizada sem multas.\n";
        }

        int continuar;
        std::cout << "Deseja realizar outro emprestimo? (1. Sim, 2. Nao): ";
        while (!(std::cin >> continuar) || (continuar != 1 && continuar != 2)) {
            std::cout << "Entrada invalida. Por favor, escolha 1 ou 2: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if (continuar != 1) {
            break;
        }
    }

    std::cout << "Obrigado por utilizar a locadora. Ate a proxima!\n";
    return 0;
}