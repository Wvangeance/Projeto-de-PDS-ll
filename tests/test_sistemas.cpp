#include <iostream>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "Sistema.hpp"


class MockFilme : public Filme {
public:
    MockFilme(std::string titulo, int ano) : Filme(titulo, ano) {}

    MOCK_METHOD(void, alugar, (), (override));  
    MOCK_METHOD(void, devolver, (), (override));  
};


class MockPessoa : public Pessoa {
public:
    MockPessoa(std::string nome) : Pessoa(nome) {}

    MOCK_METHOD(void, receberNotificacao, (), (override));  
};


TEST(SistemaTest, AlugarFilme) {
    
    MockFilme mockFilme("Matrix", 1999);
    MockPessoa mockPessoa("João");

    
    EXPECT_CALL(mockFilme, alugar()).Times(1);  
    EXPECT_CALL(mockPessoa, receberNotificacao()).Times(1);  

    
    SistemaLocadora sistema;
    sistema.adicionarFilme("Matrix", 1999);
    sistema.adicionarCliente("João");

    
    Locacao::alugarFilme(mockPessoa, mockFilme, sistema.historico);

    
    
}

TEST(SistemaTest, DevolverFilme) {
    
    MockFilme mockFilme("Matrix", 1999);
    MockPessoa mockPessoa("João");

    
    EXPECT_CALL(mockFilme, devolver()).Times(1);  
    EXPECT_CALL(mockPessoa, receberNotificacao()).Times(1);  

    
    SistemaLocadora sistema;
    sistema.adicionarFilme("Matrix", 1999);
    sistema.adicionarCliente("João");

    
    Locacao::devolverFilme(mockPessoa, mockFilme, sistema.historico);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
