#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Classe Venda
class Venda {
private:
    int qtde;
    double valor;

public:
    Venda(int qtde = 0, double valor = 0.0) : qtde(qtde), valor(valor) {}

    double valorMedio() const {
        return qtde == 0 ? 0.0 : valor / qtde;
    }

    int getQtde() const { return qtde; }
    double getValor() const { return valor; }
};

// Classe Vendedor
class Vendedor {
private:
    int id;
    string nome;
    double percComissao;
    vector<Venda> vendas;

public:
    Vendedor(int id, string nome, double percComissao) 
        : id(id), nome(nome), percComissao(percComissao), vendas(31) {}

    void registrarVenda(int dia, Venda venda) {
        if (dia >= 1 && dia <= 31) {
            vendas[dia - 1] = venda;
        }
    }

    double valorVendas() const {
        double total = 0.0;
        for (const Venda& venda : vendas) {
            total += venda.getValor();
        }
        return total;
    }

    double valorComissao() const {
        return valorVendas() * percComissao / 100;
    }

    double valorMedioVendasDiarias() const {
        double somaMedias = 0.0;
        int diasComVenda = 0;
        for (const Venda& venda : vendas) {
            if (venda.getQtde() > 0) {
                somaMedias += venda.valorMedio();
                diasComVenda++;
            }
        }
        return diasComVenda == 0 ? 0.0 : somaMedias / diasComVenda;
    }

    int getId() const { return id; }
    string getNome() const { return nome; }
    bool possuiVendas() const {
        for (const Venda& venda : vendas) {
            if (venda.getQtde() > 0) {
                return true;
            }
        }
        return false;
    }
};

// Classe Vendedores (Container de vendedores)
class Vendedores {
private:
    vector<Vendedor> osVendedores;
    const int max = 10;

public:
    bool addVendedor(const Vendedor& v) {
        if (osVendedores.size() < max) {
            osVendedores.push_back(v);
            return true;
        }
        return false;
    }

    bool delVendedor(int id) {
        for (size_t i = 0; i < osVendedores.size(); ++i) {
            if (osVendedores[i].getId() == id && !osVendedores[i].possuiVendas()) {
                osVendedores.erase(osVendedores.begin() + i);
                return true;
            }
        }
        return false;
    }

    Vendedor* searchVendedor(int id) {
        for (Vendedor& v : osVendedores) {
            if (v.getId() == id) {
                return &v;
            }
        }
        return nullptr;
    }

    double valorVendasTotal() const {
        double total = 0.0;
        for (const Vendedor& v : osVendedores) {
            total += v.valorVendas();
        }
        return total;
    }

    double valorComissaoTotal() const {
        double total = 0.0;
        for (const Vendedor& v : osVendedores) {
            total += v.valorComissao();
        }
        return total;
    }

    const vector<Vendedor>& getVendedores() const {
        return osVendedores;
    }
};

class View {
public:
    static void mostrarMenu() {
        cout << "0. Sair\n"
             << "1. Cadastrar vendedor\n"
             << "2. Consultar vendedor\n"
             << "3. Excluir vendedor\n"
             << "4. Registrar venda\n"
             << "5. Listar vendedores\n";
    }

    static Vendedor criarVendedor() {
        int id;
        string nome;
        double comissao;
        cout << "ID do vendedor: ";
        cin >> id;
        cout << "Nome do vendedor: ";
        cin.ignore();
        getline(cin, nome);
        cout << "Percentual de comissao: ";
        cin >> comissao;
        return Vendedor(id, nome, comissao);
    }

    static void mostrarVendedor(const Vendedor& v) {
        cout << "ID: " << v.getId() << "\n"
             << "Nome: " << v.getNome() << "\n"
             << "Total de vendas: " << v.valorVendas() << "\n"
             << "Comissao devida: " << v.valorComissao() << "\n"
             << "Media das vendas diarias: " << v.valorMedioVendasDiarias() << "\n";
    }

    static void listarVendedores(const Vendedores& vendedores) {
        double totalVendas = 0.0, totalComissao = 0.0;
        for (const Vendedor& v : vendedores.getVendedores()) {
            mostrarVendedor(v);
            totalVendas += v.valorVendas();
            totalComissao += v.valorComissao();
        }
        cout << "Total de vendas: " << totalVendas << "\n"
             << "Total de comissao: " << totalComissao << "\n";
    }

    static Venda criarVenda() {
        int qtde;
        double valor;
        cout << "Quantidade de vendas: ";
        cin >> qtde;
        cout << "Valor total das vendas: ";
        cin >> valor;
        return Venda(qtde, valor);
    }
};

class Controller {
private:
    Vendedores vendedores;
    View view;

public:
    void executar() {
        int opcao;
        do {
            view.mostrarMenu();
            cin >> opcao;
            switch (opcao) {
                case 1: {  // Cadastrar vendedor
                    Vendedor vendedor = view.criarVendedor();
                    if (!vendedores.addVendedor(vendedor)) {
                        cout << "Limite de vendedores atingido.\n";
                    }
                    break;
                }
                case 2: {  // Consultar vendedor
                    int id;
                    cout << "Informe o ID do vendedor: ";
                    cin >> id;
                    Vendedor* vendedor = vendedores.searchVendedor(id);
                    if (vendedor) {
                        view.mostrarVendedor(*vendedor);
                    } else {
                        cout << "Vendedor nao encontrado.\n";
                    }
                    break;
                }
                case 3: {  // Excluir vendedor
                    int id;
                    cout << "Informe o ID do vendedor: ";
                    cin >> id;
                    if (!vendedores.delVendedor(id)) {
                        cout << "Vendedor nao pode ser excluido (ja possui vendas ou nao encontrado).\n";
                    }
                    break;
                }
                case 4: {  // Registrar venda
                    int id, dia;
                    cout << "Informe o ID do vendedor: ";
                    cin >> id;
                    Vendedor* vendedor = vendedores.searchVendedor(id);
                    if (vendedor) {
                        cout << "Informe o dia da venda (1-31): ";
                        cin >> dia;
                        Venda venda = view.criarVenda();
                        vendedor->registrarVenda(dia, venda);
                    } else {
                        cout << "Vendedor nao encontrado.\n";
                    }
                    break;
                }
                case 5:  // Listar vendedores
                    view.listarVendedores(vendedores);
                    break;
                case 0:
                    cout << "Saindo...\n";
                    break;
                default:
                    cout << "Opcao invalida!\n";
                    break;
            }
        } while (opcao != 0);
    }
};
