#include <iostream>
#include <algorithm> // Para std::swap

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {
    int universo[] = {0, 2, 6, 5, 8, 1, 3, 9, 7, 4};
    int tamanhoArray = sizeof(universo) / sizeof(universo[0]);

    std::cout << "Tamanho do array: " << tamanhoArray << std::endl;

    std::cout << "Array antes da ordenação: ";
    for (int i = 0; i < tamanhoArray; i++) {
        std::cout << universo[i] << " ";
    }
    std::cout << std::endl;

    quickSort(universo, 0, tamanhoArray - 1);

    std::cout << "Array após a ordenação: ";
    for (int i = 0; i < tamanhoArray; i++) {
        std::cout << universo[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}