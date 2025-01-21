## Sistema de Gerenciamento de Locadora de Filmes  

## Descrição do Problema  
O objetivo deste projeto é criar um sistema informatizado que automatize e otimize o gerenciamento de filmes, clientes, locações e pagamentos. Esse sistema será capaz de reduzir erros, aumentar a eficiência operacional e proporcionar uma experiência mais agradável tanto para os clientes quanto para os administradores da locadora.  

## Planejamento do Sistema  

### Objetivo  
Desenvolver um sistema completo para gerenciar todas as operações de uma locadora de filmes, integrando cadastro de filmes e clientes, controle de locações e pagamentos, e funcionalidades adicionais para geração de relatórios e análises de dados.  

### Funcionalidades Principais  
- Cadastro e gerenciamento de filmes.  
- Cadastro e gerenciamento de clientes.  
- Registro e gerenciamento de locações.  
- Controle de pagamentos, incluindo multas por atraso.  
- Geração de relatórios para análise de dados (opcional).  

### Classes Principais  
- **Filme**  
  Representa os filmes disponíveis na locadora, armazenando informações como título, gênero, ano de lançamento, e disponibilidade.  
- **Cliente**  
  Gerencia os dados dos clientes, como nome, endereço, telefone, e histórico de locações.  
- **Locação**  
  Responsável pelo registro das transações de locação, incluindo datas de retirada e devolução, e status de pagamento.  
- **Pagamento**  
  Gerencia os pagamentos realizados pelos clientes, incluindo cálculos de valores, registro de multas e controle de pendências.  
- **Sistema**  
  Centraliza as funcionalidades do sistema, integrando as demais classes e garantindo a operação eficiente do sistema.  
- **Utilitários**  
  Contém ferramentas auxiliares, como validações de dados, operações em banco de dados, e suporte para cálculos específicos.  

O projeto foi planejado para ser modular e escalável, permitindo futuras expansões e adaptações conforme as necessidades da locadora evoluam.  

## Estrutura de diretórios
- **include/**        (Para conter arquivos de cabeçalho - .hpp)
- **src/**            (Para conter arquivos fonte .cpp)


