#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// Estructura de ventas
struct Venta {
    string customer_id;
    string product_id;
    string quantity;
    string purchase_date;
    double total_price;

    //constr
    Venta(const string& cid, const string& pid, const string& q,
           const string& pda, double tp) : 
        customer_id(cid), 
        product_id(pid), 
        quantity(q),
        purchase_date(pda),
        total_price(tp){}
};

bool compareSales(const Venta& a, const Venta& b) {
    return a.total_price > b.total_price; // '>' for min-heap
}

void heapify(vector<Venta>& Ventas, int n, int IDraiz) {
    int min = IDraiz;
    int leftChild = 2 * IDraiz + 1;
    int rightChild = 2 * IDraiz + 2;

    // hijo izquierdo < raiz
    if (leftChild < n && compareSales(Ventas[leftChild], Ventas[min]))
        min = leftChild;
   
    if (rightChild < n && compareSales(Ventas[rightChild], Ventas[min]))
        min = rightChild;
        
     // min != raiz
    if (min != IDraiz) {
        
        swap(Ventas[IDraiz], Ventas[min]);

        heapify(Ventas, n, min);
    }
    
}

void heapSort(vector<Venta>& Ventas) {
    int n = Ventas.size();

    // min heap --> VentaId
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(Ventas, n, i);

    // Extraer
    for (int i = n - 1; i > 0; i--) {
        swap(Ventas[0], Ventas[i]);
        heapify(Ventas, i, 0);
    }
}

void load_data(vector<Venta>&Ventas)
{
    // Define the file name
    string filename = "list.txt";

    // Open the file
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Failed to open the file." << endl;
        return;
    }

    while (file) {
        double total_price;
        string customer_id, product_id, quantity, purchase_date;

        // Read data from the file
        if (file >> customer_id >> product_id >> quantity >> purchase_date>> total_price) {
            // Create a Venta object and add it to the vector
            Venta Venta(customer_id,product_id, quantity, purchase_date, total_price);
            Ventas.push_back(Venta);
        }
    }
    // Close the file
    file.close();
}

int main() {
    vector<Venta> Ventas; 
    load_data(Ventas); //lock and load txt
    heapSort(Ventas);

    cout << "Sorted Ventas by Venta total price:" << endl;
    for (const Venta& Venta : Ventas) {
        cout << "Precio total venta: " << Venta.customer_id 
        << ", ID de producto " << Venta.product_id 
        << ", Fecha de compra " << Venta.purchase_date 
        << ", Cantidad: " << Venta.quantity 
        << ", Precio total: " << Venta.total_price<< "\n";
    }

    return 0;
}