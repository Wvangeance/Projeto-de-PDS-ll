#include "Pagamento.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>

// Função auxiliar para obter a data atual no formato "YYYY-MM-DD"
std::string Multa::getDataAtual() {
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");
    return oss.str();
}

// Implementação da classe PagamentoDinheiro
void PagamentoDinheiro::realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) {
    double valorPago;
    double valor = locacao.getFilme().getPreco(); // Obtém o valor do filme
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
void PagamentoCartaoCredito::realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) {
    double valor = locacao.getFilme().getPreco(); // Obtém o valor do filme
    std::cout << "Pagamento de R$ " << valor << " realizado com cartão de crédito.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoCartaoDebito
void PagamentoCartaoDebito::realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) {
    double valor = locacao.getFilme().getPreco(); // Obtém o valor do filme
    std::cout << "Pagamento de R$ " << valor << " realizado com cartão de débito.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoPix
void PagamentoPix::realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) {
    double valor = locacao.getFilme().getPreco(); // Obtém o valor do filme
    std::cout << "Pagamento de R$ " << valor << " realizado via Pix.\n";
    pagamentoRealizado = true;
}

// Implementação da classe PagamentoEscambo
void PagamentoEscambo::realizarPagamento(const Locacao& locacao, bool& pagamentoRealizado) {
    double valor = locacao.getFilme().getPreco(); // Obtém o valor do filme
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
double Multa::calcularMulta(const Locacao& locacao, int diasPermitidos) {
    std::string dataAtual = getDataAtual(); // Obtém a data atual
    int diasAtraso = locacao.calcularDiasAtraso(dataAtual); // Passa a data atual como argumento
    double valorEmprestimo = locacao.getFilme().getPreco();
    if (diasAtraso <= diasPermitidos) {
        return 0.0; // Sem multa dentro do prazo
    }
    double multaFixa = valorEmprestimo * 0.4; // Multa fixa de 40%
    double juros = valorEmprestimo * 0.01 * (diasAtraso - diasPermitidos); // Juros de 1% por dia após o prazo permitido
    double multaTotal = multaFixa + juros;
    return (multaTotal > valorEmprestimo) ? valorEmprestimo : multaTotal; // Limite da multa
}
