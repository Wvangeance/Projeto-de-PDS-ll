#include "Filmes.hpp"

class Filme {
private:
    std::string titulo;
    std::vector<std::string> generos;
    int classificacaoEtaria;
    int anoLancamento;

public:
    Filme(const std::string& titulo, const std::vector<std::string>& generos, int classificacaoEtaria, int anoLancamento)
        : titulo(titulo), generos(generos), classificacaoEtaria(classificacaoEtaria), anoLancamento(anoLancamento) {}

    std::string getTitulo() const { return titulo; }
    std::vector<std::string> getGeneros() const { return generos; }
    int getClassificacaoEtaria() const { return classificacaoEtaria; }
    int getAnoLancamento() const { return anoLancamento; }

    bool isRecemLancado() const {
        int anoAtual = 2025; // Atualize conforme necessario
        return (anoAtual - anoLancamento) <= 1;
    }

    void exibirInformacoes() const {
        std::cout << "Titulo: " << titulo
                  << "\nGeneros: ";
        for (size_t i = 0; i < generos.size(); ++i) {
            std::cout << generos[i];
            if (i < generos.size() - 1) std::cout << ", ";
        }
        std::cout << "\nClassificacao Etaria: " << classificacaoEtaria
                  << "\nAno de Lancamento: " << anoLancamento
                  << "\nStatus: " << (isRecemLancado() ? "Recem-lancado" : "Fora de cartaz") << "\n";
    }

    void salvarNoArquivo(std::ofstream& arquivo) const {
        arquivo << titulo << "|";
        for (size_t i = 0; i < generos.size(); ++i) {
            arquivo << generos[i];
            if (i < generos.size() - 1) arquivo << ",";
        }
        arquivo << "|" << classificacaoEtaria << "|" << anoLancamento << "\n";
    }

    static Filme lerDoArquivo(const std::string& linha) {
        size_t pos1 = linha.find('|');
        size_t pos2 = linha.find('|', pos1 + 1);
        size_t pos3 = linha.find('|', pos2 + 1);

        std::string titulo = linha.substr(0, pos1);
        std::string generosStr = linha.substr(pos1 + 1, pos2 - pos1 - 1);
        int classificacaoEtaria = std::stoi(linha.substr(pos2 + 1, pos3 - pos2 - 1));
        int anoLancamento = std::stoi(linha.substr(pos3 + 1));

        std::vector<std::string> generos;
        size_t start = 0, end;
        while ((end = generosStr.find(',', start)) != std::string::npos) {
            generos.push_back(generosStr.substr(start, end - start));
            start = end + 1;
        }
        generos.push_back(generosStr.substr(start));

        return Filme(titulo, generos, classificacaoEtaria, anoLancamento);
    }
};

class SistemaFilmes {
private:
    std::vector<Filme> filmes;
    const std::string arquivoFilmes = "filmes.txt";

public:
    SistemaFilmes() {
        carregarFilmes();
    }

    ~SistemaFilmes() {
        salvarFilmes();
    }

    void cadastrarFilme() {
        std::string titulo;
        std::vector<std::string> generos;
        int classificacaoEtaria, anoLancamento;

        std::cout << "Cadastro de Filme\n";
        std::cout << "Digite o titulo do filme: ";
        std::cin.ignore();
        std::getline(std::cin, titulo);

        std::cout << "Selecione os generos do filme (maximo 3). Digite os numeros correspondentes separados por espaco:\n";
        std::cout << "1. Acao\n2. Aventura\n3. Animacao\n4. Comedia\n5. Crime\n6. Documentario\n7. Drama\n8. Familia\n";
        std::cout << "9. Fantasia\n10. Historia\n11. Horror\n12. Musica\n13. Misterio\n14. Romance\n";
        std::cout << "15. Ficcao cientifica\n16. Suspense\n17. Guerra\n";
        
        std::vector<std::string> opcoesGeneros = {
            "Acao", "Aventura", "Animacao", "Comedia", "Crime", "Documentario", "Drama", "Familia",
            "Fantasia", "Historia", "Horror", "Musica", "Misterio", "Romance", "Ficcao cientifica",
            "Suspense", "Guerra"
        };

        std::string entradaGeneros;
        std::getline(std::cin, entradaGeneros);

        std::istringstream stream(entradaGeneros);
        int genero;
        while (stream >> genero) {
            if (genero >= 1 && genero <= 17) {
                generos.push_back(opcoesGeneros[genero - 1]);
                if (generos.size() == 3) break;
            } else {
                std::cout << "Opcao invalida ignorada." << std::endl;
            }
        }

        std::cout << "Digite a classificacao etaria 0 (Livre), 10, 12, 14, 16, 18: ";
        while (!(std::cin >> classificacaoEtaria) || (classificacaoEtaria != 0 && classificacaoEtaria != 10 && classificacaoEtaria != 12 && classificacaoEtaria != 14 && classificacaoEtaria != 16 && classificacaoEtaria != 18)) {
            std::cout << "Classificacao invalida. Digite novamente 0 (Livre), 10, 12, 14, 16, 18: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        std::cout << "Digite o ano de lancamento: ";
        while (!(std::cin >> anoLancamento) || anoLancamento < 1900 || anoLancamento > 2025) {
            std::cout << "Ano invalido. Digite novamente (1900-2025): ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        filmes.emplace_back(titulo, generos, classificacaoEtaria, anoLancamento);
        std::cout << "Filme cadastrado com sucesso!\n";
    }

    void listarFilmes() const {
        if (filmes.empty()) {
            std::cout << "Nenhum filme cadastrado.\n";
            return;
        }

        std::cout << "\nLista de Filmes Cadastrados:\n";
        for (const auto& filme : filmes) {
            filme.exibirInformacoes();
            std::cout << "--------------------------\n";
        }
    }

    void buscarPorGenero() const {
        if (filmes.empty()) {
            std::cout << "Nenhum filme cadastrado.\n";
            return;
        }

        std::cout << "Digite o genero para buscar: ";
        std::cin.ignore();
        std::string genero;
        std::getline(std::cin, genero);

        std::cout << "\nFilmes encontrados:\n";
        bool encontrou = false;
        for (const auto& filme : filmes) {
            for (const auto& g : filme.getGeneros()) {
                if (g == genero) {
                    filme.exibirInformacoes();
                    std::cout << "--------------------------\n";
                    encontrou = true;
                    break;
                }
            }
        }

        if (!encontrou) {
            std::cout << "Nenhum filme encontrado com o genero especificado.\n";
        }
    }

    void alterarOuExcluirFilme() {
        if (filmes.empty()) {
            std::cout << "Nenhum filme cadastrado.\n";
            return;
        }

        listarFilmes();
        std::cout << "Digite o titulo do filme que deseja alterar ou excluir: ";
        std::cin.ignore();
        std::string titulo;
        std::getline(std::cin, titulo);

        for (auto it = filmes.begin(); it != filmes.end(); ++it) {
            if (it->getTitulo() == titulo) {
                std::cout << "1. Alterar filme\n2. Excluir filme\nEscolha uma opcao: ";
                int opcao;
                std::cin >> opcao;
                if (opcao == 1) {
                    filmes.erase(it);
                    cadastrarFilme();
                    return;
                } else if (opcao == 2) {
                    filmes.erase(it);
                    std::cout << "Filme excluido com sucesso.\n";
                    return;
                } else {
                    std::cout << "Opcao invalida.\n";
                    return;
                }
            }
        }
        std::cout << "Filme nao encontrado.\n";
    }

private:
    void salvarFilmes() const {
        std::ofstream arquivo(arquivoFilmes, std::ios::trunc);
        if (!arquivo) {
            std::cerr << "Erro ao abrir o arquivo para salvar.\n";
            return;
        }

        for (const auto& filme : filmes) {
            filme.salvarNoArquivo(arquivo);
        }
    }

    void carregarFilmes() {
        std::ifstream arquivo(arquivoFilmes);
        if (!arquivo) {
            return; // Sem arquivo, nada para carregar
        }

        std::string linha;
        while (std::getline(arquivo, linha)) {
            filmes.push_back(Filme::lerDoArquivo(linha));
        }
    }
};

int main() {
    SistemaFilmes sistema;
    int opcao;

    while (true) {
        std::cout << "\nMenu Principal\n";
        std::cout << "1. Cadastrar Filme\n";
        std::cout << "2. Listar Filmes\n";
        std::cout << "3. Alterar ou Excluir Filme\n";
        std::cout << "4. Buscar por Genero\n";
        std::cout << "5. Sair\n";
        std::cout << "Escolha uma opcao: ";

        while (!(std::cin >> opcao) || opcao < 1 || opcao > 5) {
            std::cout << "Opcao invalida. Tente novamente: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        switch (opcao) {
        case 1:
            sistema.cadastrarFilme();
            break;
        case 2:
            sistema.listarFilmes();
            break;
        case 3:
            sistema.alterarOuExcluirFilme();
            break;
        case 4:
            sistema.buscarPorGenero();
            break;
        case 5:
            std::cout << "Encerrando o sistema. Ate mais!\n";
            return 0;
        }
    }
}
