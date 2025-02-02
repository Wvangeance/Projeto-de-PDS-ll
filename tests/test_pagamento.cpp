#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Pagamento.hpp"
#include "Locacoes.hpp"
#include "Filmes.hpp"
#include "Cliente.hpp"

using ::testing::Return;
using ::testing::AtLeast;

// Mock para a classe Filme
class MockFilme : public Filme {
public:
    MockFilme() : Filme("Mock Movie", {"Ação"}, 12, 2020, 20.0) {}
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
    MOCK_METHOD(double, getPreco, (), (const, override));
};

// Mock para a classe Locacao
class MockLocacao : public Locacao {
public:
    MOCK_METHOD(const Filme&, getFilme, (), (const, override));
    MOCK_METHOD(int, calcularDiasAtraso, (const std::string&), (const, override));
};

// Teste para pagamento em dinheiro com valor exato
TEST(PagamentoDinheiroTest, PagamentoComValorExato) {
    MockLocacao mockLocacao;
    MockFilme mockFilme;

    EXPECT_CALL(mockLocacao, getFilme())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mockFilme));
    
    EXPECT_CALL(mockFilme, getPreco())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(50.0));

    PagamentoDinheiro pagamento;
    bool pagamentoRealizado = false;

    // Redirecionar std::cin para simular entrada do usuário
    std::istringstream input("50\n");
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    pagamento.realizarPagamento(mockLocacao, pagamentoRealizado);

    std::cout.rdbuf(oldCout);  // Restaurar std::cout

    EXPECT_TRUE(pagamentoRealizado);
    EXPECT_NE(buffer.str().find("Pagamento realizado com sucesso."), std::string::npos);
}

// Teste para pagamento com cartão de crédito
TEST(PagamentoCartaoCreditoTest, PagamentoComCartaoCredito) {
    MockLocacao mockLocacao;
    MockFilme mockFilme;

    EXPECT_CALL(mockLocacao, getFilme())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mockFilme));
    
    EXPECT_CALL(mockFilme, getPreco())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(75.0));

    PagamentoCartaoCredito pagamento;
    bool pagamentoRealizado = false;

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    pagamento.realizarPagamento(mockLocacao, pagamentoRealizado);

    std::cout.rdbuf(oldCout);  // Restaurar std::cout

    EXPECT_TRUE(pagamentoRealizado);
    EXPECT_NE(buffer.str().find("Pagamento de R$ 75 realizado com cartão de crédito."), std::string::npos);
}

// Teste para pagamento via Pix
TEST(PagamentoPixTest, PagamentoComPix) {
    MockLocacao mockLocacao;
    MockFilme mockFilme;

    EXPECT_CALL(mockLocacao, getFilme())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mockFilme));
    
    EXPECT_CALL(mockFilme, getPreco())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(30.0));

    PagamentoPix pagamento;
    bool pagamentoRealizado = false;

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    pagamento.realizarPagamento(mockLocacao, pagamentoRealizado);

    std::cout.rdbuf(oldCout);  // Restaurar std::cout

    EXPECT_TRUE(pagamentoRealizado);
    EXPECT_NE(buffer.str().find("Pagamento de R$ 30 realizado via Pix."), std::string::npos);
}

// Teste para pagamento por escambo (objeto aceito)
TEST(PagamentoEscamboTest, PagamentoPorEscamboAceito) {
    MockLocacao mockLocacao;
    MockFilme mockFilme;

    EXPECT_CALL(mockLocacao, getFilme())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(mockFilme));
    
    EXPECT_CALL(mockFilme, getPreco())
        .Times(AtLeast(1))
        .WillRepeatedly(Return(40.0));

    PagamentoEscambo pagamento;
    bool pagamentoRealizado = false;

    // Simular que o objeto foi aceito ('S')
    std::istringstream input("S\n");
    std::cin.rdbuf(input.rdbuf());

    std::ostringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    pagamento.realizarPagamento(mockLocacao, pagamentoRealizado);

    std::cout.rdbuf(oldCout);  // Restaurar std::cout

    EXPECT_TRUE(pagamentoRealizado);
    EXPECT_NE(buffer.str().find("Pagamento realizado por escambo."), std::string::npos);
}

// Teste para cálculo de multa sem atraso
TEST(MultaTest, CalculoMultaSemAtraso) {
    MockLocacao mockLocacao;
    MockFilme mockFilme;

    EXPECT_CALL(mockLocacao, calcularDiasAtraso(::testing::_))
        .WillRepeatedly(Return(0));
    
    EXPECT_CALL(mockLocacao, getFilme())
        .WillRepeatedly(Return(mockFilme));

    EXPECT_CALL(mockFilme, getPreco())
        .WillRepeatedly(Return(100.0));

    double multa = Multa::calcularMulta(mockLocacao, 3); // 3 dias permitidos sem multa

    EXPECT_EQ(multa, 0.0);
}

// Função principal para rodar os testes
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
