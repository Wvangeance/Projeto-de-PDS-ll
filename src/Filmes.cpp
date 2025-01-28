#include "Filmes.hpp"

// Implementação da classe Filme
Filme::Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento, double preco)
    : titulo(titulo), generos(generos), classificacaoEtaria(classificacaoEtaria), anoLancamento(anoLancamento), preco(preco) {}

std::string Filme::getTitulo() const {
    return titulo;
}

std::vector<std::string> Filme::getGeneros() const {
    return generos;
}

int Filme::getClassificacaoEtaria() const {
    return classificacaoEtaria;
}

int Filme::getAnoLancamento() const {
    return anoLancamento;
}

double Filme::getPreco() const {
    return preco;
}

void Filme::setPreco(double preco) {
    this->preco = preco;
}

bool Filme::isRecemLancado() const {
    return anoLancamento >= 2023; // Considerando filmes lançados recentemente como os do ano atual
}

void Filme::exibirInformacoes() const {
    std::cout << "Título: " << titulo << "\n";
    std::cout << "Gêneros: ";
    for (const auto& genero : generos) {
        std::cout << genero << " ";
    }
    std::cout << "\n";
    std::cout << "Classificação Etária: " << classificacaoEtaria << "+\n";
    std::cout << "Ano de Lançamento: " << anoLancamento << "\n";
    std::cout << "Preço: R$ " << preco << "\n";
}

void Filme::salvarNoArquivo(std::ofstream& arquivo) const {
    arquivo << titulo << ";";
    for (size_t i = 0; i < generos.size(); ++i) {
        arquivo << generos[i];
        if (i < generos.size() - 1) {
            arquivo << ",";
        }
    }
    arquivo << ";" << classificacaoEtaria << ";" << anoLancamento << ";" << preco << "\n";
}

Filme Filme::lerDoArquivo(const std::string& linha) {
    std::stringstream ss(linha);
    std::string titulo, generoStr, classificacaoStr, anoStr, precoStr;

    std::getline(ss, titulo, ';');
    std::getline(ss, generoStr, ';');
    std::getline(ss, classificacaoStr, ';');
    std::getline(ss, anoStr, ';');
    std::getline(ss, precoStr, ';');

    std::vector<std::string> generos;
    std::stringstream generoStream(generoStr);
    std::string genero;
    while (std::getline(generoStream, genero, ',')) {
        generos.push_back(genero);
    }

    int classificacaoEtaria = std::stoi(classificacaoStr);
    int anoLancamento = std::stoi(anoStr);
    double preco = std::stod(precoStr);

    return Filme(titulo, generos, classificacaoEtaria, anoLancamento, preco);
}

// Implementação da classe SistemaFilmes
SistemaFilmes::SistemaFilmes() : arquivoFilmes("filmes.txt") {
    carregarFilmes();
}

SistemaFilmes::~SistemaFilmes() {
    salvarFilmes();
}

void SistemaFilmes::cadastrarFilme() {
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;
    double preco;

    std::cout << "Digite o título do filme: ";
    std::getline(std::cin, titulo);

    std::cout << "Digite os gêneros do filme separados por vírgula: ";
    std::string generoStr;
    std::getline(std::cin, generoStr);
    std::stringstream ss(generoStr);
    std::string genero;
    while (std::getline(ss, genero, ',')) {
        generos.push_back(genero);
    }

    std::cout << "Digite a classificação etária: ";
    std::cin >> classificacaoEtaria;

    std::cout << "Digite o ano de lançamento: ";
    std::cin >> anoLancamento;

    std::cout << "Digite o preço do filme: R$ ";
    std::cin >> preco;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    filmes.emplace_back(titulo, generos, classificacaoEtaria, anoLancamento, preco);
    std::cout << "Filme cadastrado com sucesso!\n";
}

void SistemaFilmes::listarFilmes() const {
    if (filmes.empty()) {
        std::cout << "Nenhum filme cadastrado.\n";
        return;
    }

    for (const auto& filme : filmes) {
        filme.exibirInformacoes();
        std::cout << "------------------------\n";
    }
}

void SistemaFilmes::buscarPorGenero() const {
    std::cout << "Digite o gênero que deseja buscar: ";
    std::string generoBusca;
    std::getline(std::cin, generoBusca);

    bool encontrado = false;
    for (const auto& filme : filmes) {
        for (const auto& genero : filme.getGeneros()) {
            if (genero == generoBusca) {
                filme.exibirInformacoes();
                std::cout << "------------------------\n";
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        std::cout << "Nenhum filme encontrado para o gênero informado.\n";
    }
}

void SistemaFilmes::alterarOuExcluirFilme() {
    std::cout << "Digite o título do filme que deseja alterar ou excluir: ";
    std::string tituloBusca;
    std::getline(std::cin, tituloBusca);

    for (auto it = filmes.begin(); it != filmes.end(); ++it) {
        if (it->getTitulo() == tituloBusca) {
            std::cout << "Filme encontrado:\n";
            it->exibirInformacoes();

            std::cout << "Deseja alterar (A) ou excluir (E) o filme? ";
            char opcao;
            std::cin >> opcao;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            if (opcao == 'A' || opcao == 'a') {
                std::cout << "Digite o novo preço do filme: R$ ";
                double novoPreco;
                std::cin >> novoPreco;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                it->setPreco(novoPreco);
                std::cout << "Preço atualizado com sucesso!\n";
            } else if (opcao == 'E' || opcao == 'e') {
                filmes.erase(it);
                std::cout << "Filme excluído com sucesso!\n";
            } else {
                std::cout << "Opção inválida.\n";
            }
            return;
        }
    }

    std::cout << "Filme não encontrado.\n";
}

void SistemaFilmes::salvarFilmes() const {
    std::ofstream arquivo(arquivoFilmes);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao salvar os filmes no arquivo.\n";
        return;
    }

    for (const auto& filme : filmes) {
        filme.salvarNoArquivo(arquivo);
    }

    arquivo.close();
}

void SistemaFilmes::carregarFilmes() {
    std::ifstream arquivo(arquivoFilmes);
    if (!arquivo.is_open()) {
        std::cerr << "Erro ao carregar os filmes do arquivo.\n";
        return;
    }

    std::string linha;
    while (std::getline(arquivo, linha)) {
        filmes.push_back(Filme::lerDoArquivo(linha));
    }

    arquivo.close();
}