// aluno Ricardo OLiani CB3025543

#include <iostream>
#include <string>
#include <ctime>
#include <cctype> // Para a função isdigit

using namespace std;

class Data {
public:
    int dia;
    int mes;
    int ano;

    Data(int d, int m, int a) : dia(d), mes(m), ano(a) {}
};

class Contato {
public:
    string email;
    string nome;
    string telefone;
    Data dtnasc;

    Contato() : dtnasc(0, 0, 0) {}

    Contato(string e, string n, string tel, Data data) : email(e), nome(n), telefone(tel), dtnasc(data) {}

    int idade() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        int ano_atual = 1900 + ltm->tm_year;

        int idade = ano_atual - dtnasc.ano;
        return idade;
    }
};

bool validarData(int dia, int mes, int ano) {
    if (mes < 1 || mes > 12)
        return false;
    if (dia < 1 || dia > 31)
        return false;
    if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30)
        return false;
    if (mes == 2) {
        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
            if (dia > 29)
                return false;
        } else {
            if (dia > 28)
                return false;
        }
    }
    return true;
}

Data obterDataNascimento() {
    string data;
    cout << "Digite a data de nascimento (dd/mm/yyyy): ";
    cin >> data;

    int pos1 = data.find('/');
    int pos2 = data.find('/', pos1 + 1);

    int dia = stoi(data.substr(0, pos1));
    int mes = stoi(data.substr(pos1 + 1, pos2 - pos1 - 1));
    int ano = stoi(data.substr(pos2 + 1));

    while (!validarData(dia, mes, ano)) {
        cout << "Data inválida. Digite novamente (dd/mm/yyyy): ";
        cin >> data;
        pos1 = data.find('/');
        pos2 = data.find('/', pos1 + 1);
        dia = stoi(data.substr(0, pos1));
        mes = stoi(data.substr(pos1 + 1, pos2 - pos1 - 1));
        ano = stoi(data.substr(pos2 + 1));
    }

    return Data(dia, mes, ano);
}

string obterTelefone() {
    string telefone;
    cout << "Digite o telefone (apenas números): ";
    cin >> telefone;

    // Verifica se todos os caracteres são dígitos
    for (char c : telefone) {
        if (!isdigit(c)) {
            cout << "Número de telefone inválido. Digite apenas números." << endl;
            return obterTelefone();
        }
    }

    return telefone;
}

string obterEmail() {
    string email;
    cout << "Digite o email: ";
    cin >> email;

    // Verifica se o email contém o caractere "@"
    if (email.find('@') == string::npos) {
        cout << "Email inválido. Deve conter o caractere '@'." << endl;
        return obterEmail();
    }

    return email;
}

int main() {
    Contato contatos[5];

    for (int i = 0; i < 5; ++i) {
        cout << "\nCadastro de Contato " << i + 1 << endl;
        string nome, telefone;

        cout << "Digite o nome: ";
        cin >> nome;

        telefone = obterTelefone();
        string email = obterEmail();
        Data data_nascimento = obterDataNascimento();
        contatos[i] = Contato(email, nome, telefone, data_nascimento);
    }

    cout << "\nLista de Contatos:" << endl;
    for (int i = 0; i < 5; ++i) {
        cout << "\nNome: " << contatos[i].nome << endl;
        cout << "Email: " << contatos[i].email << endl;
        cout << "Telefone: " << contatos[i].telefone << endl;
        cout << "Idade: " << contatos[i].idade() << endl;
    }

    return 0;
}