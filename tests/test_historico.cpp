#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Historico.hpp"

using ::testing::Return;

class MockPessoa : public Pessoa {
public:
    MockPessoa(int id, const std::string& nome) : Pessoa(id, nome) {}
    MOCK_METHOD(int, getId, (), (const, override));
};

class MockFilme : public Filme {
public:
    MockFilme(const std::string& titulo, const std::string& genero) : Filme(titulo, genero) {}
    MOCK_METHOD(std::string, getTitulo, (), (const, override));
};

class MockLocacao : public Locacao {
public:
    MockLocacao(Pessoa& cliente, Filme& filme) : Locacao(cliente, filme) {}
    MOCK_METHOD(Pessoa&, getCliente, (), (const, override));
    MOCK_METHOD(Filme&, getFilme, (), (const, override));
};

class MockPagamento : public Pagamento {
public:
    MockPagamento(Pessoa& cliente, double valor) : Pagamento(cliente, valor) {}
    MOCK_METHOD(Pessoa&, getCliente, (), (const, override));
    MOCK_METHOD(double, getValor, (), (const, override));
};

class HistoricoTest : public ::testing::Test {
protected:
    Historico historico;
    MockPessoa cliente1{1, "Anakin Skywalker"};
    MockPessoa cliente2{2, "Padmé Amidala"};
    MockFilme filme1{"Nosferatu", "Terror"};
    MockFilme filme2{"Star Wars: Episódio II - Ataque dos Clones", "Ação"};

    void SetUp() override {
        historico.adicionarCliente(cliente1);
        historico.adicionarCliente(cliente2);
        historico.adicionarFilme(filme1);
        historico.adicionarFilme(filme2);
    }
};

TEST_F(HistoricoTest, TestRegistrarLocacao) {
    MockLocacao locacao1(cliente1, filme1);
    EXPECT_CALL(locacao1, getCliente()).WillRepeatedly(Return(cliente1));
    EXPECT_CALL(locacao1, getFilme()).WillRepeatedly(Return(filme1));

    historico.registrarLocacao(locacao1);
    EXPECT_EQ(historico.clientesFrequentes[cliente1.getId()], 1);
}

TEST_F(HistoricoTest, TestRegistrarPagamento) {
    MockPagamento pagamento1(cliente1, 50.0);
    EXPECT_CALL(pagamento1, getCliente()).WillRepeatedly(Return(cliente1));
    EXPECT_CALL(pagamento1, getValor()).WillRepeatedly(Return(50.0));

    historico.registrarPagamentoCliente(pagamento1);
}

TEST_F(HistoricoTest, TestGerarRelatorioFilmesMaisAlugados) {
    MockLocacao locacao1(cliente1, filme1);
    MockLocacao locacao2(cliente2, filme1);
    MockLocacao locacao3(cliente1, filme2);
    
    EXPECT_CALL(locacao1, getFilme()).WillRepeatedly(Return(filme1));
    EXPECT_CALL(locacao2, getFilme()).WillRepeatedly(Return(filme1));
    EXPECT_CALL(locacao3, getFilme()).WillRepeatedly(Return(filme2));
    
    historico.registrarLocacao(locacao1);
    historico.registrarLocacao(locacao2);
    historico.registrarLocacao(locacao3);
    
    testing::internal::CaptureStdout();
    historico.gerarRelatorioFilmesMaisAlugados();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Nosferatu: 2 locacoes") != std::string::npos);
    EXPECT_TRUE(output.find("Star Wars: Episódio II - Ataque dos Clones: 1 locacoes") != std::string::npos);
}

TEST_F(HistoricoTest, TestConsultarAtividadeCliente) {
    testing::internal::CaptureStdout();
    historico.consultarAtividade(cliente1.getId());
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_TRUE(output.find("Atividades do cliente") != std::string::npos);
}
