#include <windows.h>
#include <vector>
#include <sstream>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

// Estrutura para representar uma poltrona
struct Poltrona {
    bool ocupada;
    int valor;
};

public ref class BilheteriaForm : public Form {
private:
    const int NUM_FILEIRAS = 15;
    const int POLTRONAS_POR_FILEIRA = 40;
    List<Button^>^ botaoPoltronas;
    array<array<Poltrona, 40>^>^ mapaOcupacao;

    int qtdeLugaresOcupados = 0;
    double valorBilheteria = 0.0;
    Label^ labelFaturamento;
    Button^ btnFaturamento;
    Button^ btnReservar;
    Button^ btnMapaOcupacao;

public:
    BilheteriaForm() {
        this->Text = "Controle de Ocupação - Teatro";
        this->Size = System::Drawing::Size(900, 700);
        botaoPoltronas = gcnew List<Button^>();
        mapaOcupacao = gcnew array<array<Poltrona, 40>^>(NUM_FILEIRAS);

        for (int i = 0; i < NUM_FILEIRAS; i++) {
            mapaOcupacao[i] = gcnew array<Poltrona, 40>();
            for (int j = 0; j < POLTRONAS_POR_FILEIRA; j++) {
                mapaOcupacao[i][j] = { false, 0 };

                // Criação dinâmica dos botões
                Button^ poltrona = gcnew Button();
                poltrona->Size = System::Drawing::Size(30, 30);
                poltrona->Location = Point(40 * j + 10, 40 * i + 10);
                poltrona->Text = ".";
                poltrona->BackColor = Color::LightGray;
                poltrona->Click += gcnew EventHandler(this, &BilheteriaForm::onPoltronaClick);

                botaoPoltronas->Add(poltrona);
                this->Controls->Add(poltrona);
            }
        }

        // Botão para exibir faturamento
        btnFaturamento = gcnew Button();
        btnFaturamento->Text = "Faturamento";
        btnFaturamento->Size = System::Drawing::Size(100, 30);
        btnFaturamento->Location = Point(40 * POLTRONAS_POR_FILEIRA + 10, 50);
        btnFaturamento->Click += gcnew EventHandler(this, &BilheteriaForm::mostrarFaturamento);
        this->Controls->Add(btnFaturamento);

        // Label para mostrar resultado do faturamento
        labelFaturamento = gcnew Label();
        labelFaturamento->Size = System::Drawing::Size(150, 30);
        labelFaturamento->Location = Point(40 * POLTRONAS_POR_FILEIRA + 10, 90);
        this->Controls->Add(labelFaturamento);
    }

private:
    // Método chamado ao clicar numa poltrona
    void onPoltronaClick(Object^ sender, EventArgs^ e) {
        Button^ poltrona = dynamic_cast<Button^>(sender);
        int index = botaoPoltronas->IndexOf(poltrona);

        int fileira = index / POLTRONAS_POR_FILEIRA;
        int numeroPoltrona = index % POLTRONAS_POR_FILEIRA;

        if (mapaOcupacao[fileira][numeroPoltrona].ocupada) {
            MessageBox::Show("Poltrona ocupada. Selecione outra.");
        } else {
            int valor = 0;
            if (fileira >= 0 && fileira < 5)
                valor = 50;
            else if (fileira >= 5 && fileira < 10)
                valor = 30;
            else
                valor = 15;

            mapaOcupacao[fileira][numeroPoltrona].ocupada = true;
            mapaOcupacao[fileira][numeroPoltrona].valor = valor;
            poltrona->BackColor = Color::Red;
            poltrona->Text = "#";

            qtdeLugaresOcupados++;
            valorBilheteria += valor;

            MessageBox::Show("Poltrona reservada com sucesso.");
        }
    }

    // Método para exibir o faturamento
    void mostrarFaturamento(Object^ sender, EventArgs^ e) {
        std::stringstream ss;
        ss << "Lugares ocupados: " << qtdeLugaresOcupados << "\n";
        ss << "Faturamento: R$ " << valorBilheteria;
        String^ resultado = gcnew String(ss.str().c_str());
        labelFaturamento->Text = resultado;
    }
};

// Função principal
[STAThread]
void Main(array<String^>^ args) {
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew BilheteriaForm());
}
