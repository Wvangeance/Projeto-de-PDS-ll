#ifndef MAIN_HPP
#define MAIN_HPP

#include "Cliente.hpp"
#include "Filmes.hpp"
#include "Locacoes.hpp"
#include "Pagamento.hpp"
#include "Promocao.hpp"
#include "Historico.hpp"

void menuPrincipal();
void realizarLocacao(Historico& historico);
void processarPagamento(const Locacao& locacao, Historico& historico);

#endif // MAIN_HPP
