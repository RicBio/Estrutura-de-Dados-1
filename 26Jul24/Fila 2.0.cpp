#include <iostream>
#include <queue>
#include <list>
#include <unordered_map>

struct Guiche {
    int id;
    std::queue<int> senhasAtendidas; // Fila para armazenar as senhas atendidas pelo guichê
};

int main() {
    std::queue<int> senhasGeradas; // Fila para armazenar as senhas geradas
    std::unordered_map<int, Guiche> guiches; // Mapa para armazenar os guichês abertos
    int senhaAtual = 0;
    int totalSenhasAtendidas = 0;

    while (true) {
        std::cout << "Selecione uma opcao:\n";
        std::cout << "0. Sair\n";
        std::cout << "1. Gerar senha\n";
        std::cout << "2. Abrir guiche\n";
        std::cout << "3. Realizar atendimento\n";
        std::cout << "4. Listar senhas atendidas\n";
        std::cout << "Senhas aguardando atendimento: " << senhasGeradas.size() << "\n";
        std::cout << "Guiches abertos: " << guiches.size() << "\n";

        int opcao;
        std::cin >> opcao;

        switch (opcao) {
            case 0: // Sair
                if (!senhasGeradas.empty()) {
                    std::cout << "Ainda ha senhas aguardando atendimento. O programa nao pode ser encerrado.\n";
                } else {
                    std::cout << "Total de senhas atendidas: " << totalSenhasAtendidas << "\n";
                    return 0;
                }
                break;
            case 1: // Gerar senha
                senhasGeradas.push(++senhaAtual); // Adiciona uma nova senha à fila de senhas geradas
                std::cout << "Senha gerada: " << senhaAtual << "\n";
                break;
            case 2: { // Abrir guiche
                int idGuiche;
                std::cout << "Digite o ID do guiche: ";
                std::cin >> idGuiche;
                if (guiches.find(idGuiche) == guiches.end()) {
                    Guiche novoGuiche = {idGuiche};
                    guiches[idGuiche] = novoGuiche; // Adiciona um novo guichê ao mapa de guichês
                    std::cout << "Guiche " << idGuiche << " aberto.\n";
                } else {
                    std::cout << "Guiche " << idGuiche << " ja esta aberto.\n";
                }
                break;
            }
            case 3: { // Realizar atendimento
                if (senhasGeradas.empty()) {
                    std::cout << "Nao ha senhas para atendimento.\n";
                    break;
                }
                int idGuiche;
                std::cout << "Digite o ID do guiche: ";
                std::cin >> idGuiche;
                if (guiches.find(idGuiche) != guiches.end()) {
                    int senha = senhasGeradas.front(); // Obtém a senha da frente da fila de senhas geradas
                    senhasGeradas.pop(); // Remove a senha da fila de senhas geradas
                    guiches[idGuiche].senhasAtendidas.push(senha); // Adiciona a senha à fila de senhas atendidas pelo guichê
                    totalSenhasAtendidas++;
                    std::cout << "Guiche " << idGuiche << " atendeu a senha " << senha << ".\n";
                } else {
                    std::cout << "Guiche " << idGuiche << " nao esta aberto.\n";
                }
                break;
            }
            case 4: { // Listar senhas atendidas
                int idGuiche;
                std::cout << "Digite o ID do guiche: ";
                std::cin >> idGuiche;
                if (guiches.find(idGuiche) != guiches.end()) {
                    std::cout << "Senhas atendidas pelo guiche " << idGuiche << ": ";
                    std::queue<int> senhas = guiches[idGuiche].senhasAtendidas; // Obtém a fila de senhas atendidas pelo guichê
                    while (!senhas.empty()) {
                        std::cout << senhas.front() << " "; // Exibe a senha da frente da fila
                        senhas.pop(); // Remove a senha da fila
                    }
                    std::cout << "\n";
                } else {
                    std::cout << "Guiche " << idGuiche << " nao esta aberto.\n";
                }
                break;
            }
            default:
                std::cout << "Opcao invalida.\n";
                break;
        }
    }

    return 0;
}