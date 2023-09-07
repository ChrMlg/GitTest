#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estructura de vuelos
struct Vuelo {
    int VueloId;
    string ciudadPartida;
    string ciudadDestino;
    string fechaSalida;
    string fechaLlegada;

    // Constr
    Vuelo(int id, const string& dep, const string& des,
           const string& depD, const string& arrD) : 
        VueloId(id), 
        ciudadPartida(dep), 
        ciudadDestino(des),
        fechaSalida(depD),
        fechaLlegada(arrD){}
};

// Comparacion de numeros de vuelo
bool compareVuelosById(const Vuelo& a, const Vuelo& b) {
    return a.VueloId > b.VueloId; // '>' for min-heap
}

void heapify(vector<Vuelo>& Vuelos, int n, int IDraiz) {
    int min = IDraiz;
    int leftChild = 2 * IDraiz + 1;
    int rightChild = 2 * IDraiz + 2;

    // hijo izquierdo < raiz
    if (leftChild < n && compareVuelosById(Vuelos[leftChild], Vuelos[min]))
        min = leftChild;

    // hijo derecho < raiz
    if (rightChild < n && compareVuelosById(Vuelos[rightChild], Vuelos[min]))
        min = rightChild;

    // min != raiz
    if (min != IDraiz) {
        
        swap(Vuelos[IDraiz], Vuelos[min]);

        heapify(Vuelos, n, min);
    }
}

// heapsort main
void heapSort(vector<Vuelo>& Vuelos) {
    int n = Vuelos.size();

    // min heap --> VueloId
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(Vuelos, n, i);

    // Extraer
    for (int i = n - 1; i > 0; i--) {
        swap(Vuelos[0], Vuelos[i]);
        heapify(Vuelos, i, 0);
    }
}

void load_data(vector<Vuelo>& Vuelos) {
    // Define the file name
    string filename = "Vuelos.txt";

    // Open the file
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Failed to open the file." << endl;
        return;
    }

    while (file) {
        int VueloId;
        string ciudadPartida, ciudadDestino, fechaSalida, fechaLlegada;

        // Read data from the file
        if (file >> VueloId >> ciudadPartida >> ciudadDestino >> fechaSalida >> fechaLlegada) {
            // Create a Vuelo object and add it to the vector
            Vuelo Vuelo(VueloId, ciudadPartida, ciudadDestino, fechaSalida, fechaLlegada);
            Vuelos.push_back(Vuelo);
        }
    }

    // Close the file
    file.close();
}


int main() {
    vector<Vuelo> Vuelos; 
    load_data(Vuelos); //lock and load txt
    heapSort(Vuelos);

    cout << "Sorted Vuelos by Vuelo ID:" << endl;
    for (const Vuelo& Vuelo : Vuelos) {
        cout << "Vuelo ID: " << Vuelo.VueloId 
        << ", Ciudad de embarque: " << Vuelo.ciudadPartida 
        << ", Ciudad de destino: " << Vuelo.ciudadDestino 
        << ", Hora de llegada: " << Vuelo.fechaLlegada 
        << ", Hora de salida: " << Vuelo.fechaSalida<< "\n";
    }

    return 0;
}

