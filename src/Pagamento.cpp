#include "Pagamento.hpp"

// Implementação da classe PagamentoDinheiro
void PagamentoDinheiro::realizarPagamento(double valor, bool &pagamentoRealizado) {
    double valorPago;
    std::cout << "O valor total é R$ " << valor << ".\nInsira o valor dado pelo cliente: ";
    while (!(std::cin >> valorPago) || valorPago <= 0) {
        std::cout << "Entrada inválida. Por favor, insira um valor numérico positivo: ";
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
        std::cout << "Valor insuficiente! Pagamento não realizado.\n";
        pagamentoRealizado = false;
    }
}

// Implementação da classe PagamentoCartaoCredito
void PagamentoCartaoCredito::realizarPagamento(double valor, bool &pagamentoRealizado) {
    std::cout << "Pagamento de R$ " << valor << " realizado com cartão de crédito.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoCartaoDebito
void PagamentoCartaoDebito::realizarPagamento(double valor, bool &pagamentoRealizado) {
    std::cout << "Pagamento de R$ " << valor << " realizado com cartão de débito.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoPix
void PagamentoPix::realizarPagamento(double valor, bool &pagamentoRealizado) {
    std::cout << "Pagamento de R$ " << valor << " realizado via Pix.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoEscambo
void PagamentoEscambo::realizarPagamento(double valor, bool &pagamentoRealizado) {
    std::cout << "O valor estimado do escambo é R$ " << valor << ".\n";
    char avaliacao;
    std::cout << "O objeto para troca foi avaliado pelo balconista. Objeto aceito? (S/N): ";
    std::cin >> avaliacao;
    avaliacao = toupper(avaliacao);

    if (avaliacao == 'S') {
        std::cout << "Pagamento realizado por escambo.\n";
        pagamentoRealizado = true;
    } else {
        std::cout << "Objeto rejeitado. Pagamento não realizado.\n";
        pagamentoRealizado = false;
    }
}

// Implementação da classe Multa
double Multa::calcularMulta(double valorEmprestimo, int diasAtraso, int diasPermitidos) {
    if (diasAtraso <= diasPermitidos) {
        return 0.0; // Sem multa dentro do prazo
    }
    double multaFixa = valorEmprestimo * 0.4; // Multa fixa de 40%
    double juros = valorEmprestimo * 0.01 * (diasAtraso - diasPermitidos); // Juros de 1% por dia após o prazo permitido
    double multaTotal = multaFixa + juros;
    return (multaTotal > valorEmprestimo) ? valorEmprestimo : multaTotal; // Limite da multa
}

// Implementação da classe Locadora
Locadora::Locadora(std::unique_ptr<Pagamento> metodo)
    : metodoPagamento(std::move(metodo)) {}

void Locadora::processarPagamento(double valor, bool &pagamentoRealizado) {
    metodoPagamento->realizarPagamento(valor, pagamentoRealizado);
}

void Locadora::alterarMetodoPagamento(std::unique_ptr<Pagamento> novoMetodo) {
    metodoPagamento = std::move(novoMetodo);
}
