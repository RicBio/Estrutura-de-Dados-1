#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct Funcionario {
    int prontuario;
    string nome;
    double salario;
};

// Função para verificar se um funcionário com o mesmo prontuário já está na lista
bool prontuarioJaExistente(const vector<Funcionario>& funcionarios, int prontuario) {
    for (const auto& func : funcionarios) {
        if (func.prontuario == prontuario) {
            return true;
        }
    }
    return false;
}

// Função para incluir um funcionário na lista
void incluirFuncionario(vector<Funcionario>& funcionarios) {
    Funcionario novoFuncionario;
    cout << "Digite o prontuario: ";
    cin >> novoFuncionario.prontuario;

    if (prontuarioJaExistente(funcionarios, novoFuncionario.prontuario)) {
        cout << "Funcionario com esse prontuario ja existe." << endl;
        return;
    }

    cout << "Digite o nome: ";
    cin.ignore(); // Limpar o buffer de entrada
    getline(cin, novoFuncionario.nome);
    cout << "Digite o salario: ";
    cin >> novoFuncionario.salario;

    funcionarios.push_back(novoFuncionario);
    cout << "Funcionario adicionado com sucesso." << endl;
}

// Função para excluir um funcionário da lista
void excluirFuncionario(vector<Funcionario>& funcionarios) {
    int prontuario;
    cout << "Digite o prontuario do funcionario a ser excluido: ";
    cin >> prontuario;

    auto it = find_if(funcionarios.begin(), funcionarios.end(), [prontuario](const Funcionario& func) {
        return func.prontuario == prontuario;
    });

    if (it != funcionarios.end()) {
        funcionarios.erase(it);
        cout << "Funcionario excluido com sucesso." << endl;
    } else {
        cout << "Funcionario nao encontrado." << endl;
    }
}

// Função para pesquisar um funcionário pelo prontuário
void pesquisarFuncionario(const vector<Funcionario>& funcionarios) {
    int prontuario;
    cout << "Digite o prontuario do funcionario a ser pesquisado: ";
    cin >> prontuario;

    auto it = find_if(funcionarios.begin(), funcionarios.end(), [prontuario](const Funcionario& func) {
        return func.prontuario == prontuario;
    });

    if (it != funcionarios.end()) {
        cout << "Funcionario encontrado:" << endl;
        cout << "Prontuario: " << it->prontuario << endl;
        cout << "Nome: " << it->nome << endl;
        cout << "Salario: " << it->salario << endl;
    } else {
        cout << "Funcionario nao encontrado." << endl;
    }
}

// Função para listar todos os funcionários e calcular o total dos salários
void listarFuncionarios(const vector<Funcionario>& funcionarios) {
    if (funcionarios.empty()) {
        cout << "Nenhum funcionario cadastrado." << endl;
        return;
    }

    double totalSalarios = 0.0;
    cout << "Lista de funcionarios:" << endl;
    for (const auto& func : funcionarios) {
        cout << "Prontuario: " << func.prontuario << ", Nome: " << func.nome << ", Salario: " << func.salario << endl;
        totalSalarios += func.salario;
    }
    cout << "Total dos salarios: " << totalSalarios << endl;
}

int main() {
    vector<Funcionario> funcionarios;
    int opcao;

    do {
        cout << "\nMenu:" << endl;
        cout << "0. Sair" << endl;
        cout << "1. Incluir" << endl;
        cout << "2. Excluir" << endl;
        cout << "3. Pesquisar" << endl;
        cout << "4. Listar" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 0:
                cout << "Saindo..." << endl;
                break;
            case 1:
                incluirFuncionario(funcionarios);
                break;
            case 2:
                excluirFuncionario(funcionarios);
                break;
            case 3:
                pesquisarFuncionario(funcionarios);
                break;
            case 4:
                listarFuncionarios(funcionarios);
                break;
            default:
                cout << "Opcao invalida. Tente novamente." << endl;
        }
    } while (opcao != 0);

    return 0;
}
