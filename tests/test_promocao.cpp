#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Promocao.hpp"

using ::testing::Return;

class MockPessoa : public Pessoa {
public:
    MockPessoa(int id, const std::string& nome) : Pessoa(id, nome) {}
    MOCK_METHOD(int, getId, (), (const, override));
    MOCK_METHOD(std::string, getNome, (), (const, override));
};

class MockHistorico : public Historico {
public:
    MOCK_METHOD(void, registrarLocacao, (const Locacao& locacao), ());
};

class PromocaoTest : public ::testing::Test {
protected:
    MockHistorico historico;
    MockPessoa cliente1{1, "Anakin Skywalker"};
    MockPessoa cliente2{2, "Padmé Amidala"};
    Promocao promocao{"Desconto de 10%", "desconto percentual", 10.0, "2025-02-01", "2025-02-28"};

    void SetUp() override {
        historico.clientes[1] = cliente1;
        historico.clientes[2] = cliente2;
        historico.clientesFrequentes[1] = 6; // Cliente com 6 locações (elegível)
        historico.clientesFrequentes[2] = 3; // Cliente com 3 locações (não elegível)
    }
};

TEST_F(PromocaoTest, TestAplicarPromocao) {
    EXPECT_CALL(cliente1, getNome()).WillRepeatedly(Return("Anakin Skywalker"));
    EXPECT_CALL(cliente2, getNome()).WillRepeatedly(Return("Padmé Amidala"));
    
    testing::internal::CaptureStdout();
    promocao.aplicarPromocao(historico);
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Promoção aplicada ao cliente ID: 1 (Anakin Skywalker)") != std::string::npos);
    EXPECT_FALSE(output.find("Promoção aplicada ao cliente ID: 2 (Padmé Amidala)") != std::string::npos);
}

TEST_F(PromocaoTest, TestExibirDetalhes) {
    testing::internal::CaptureStdout();
    promocao.exibirDetalhes();
    std::string output = testing::internal::GetCapturedStdout();
    
    EXPECT_TRUE(output.find("Desconto de 10%") != std::string::npos);
    EXPECT_TRUE(output.find("desconto percentual") != std::string::npos);
    EXPECT_TRUE(output.find("2025-02-01") != std::string::npos);
    EXPECT_TRUE(output.find("2025-02-28") != std::string::npos);
}