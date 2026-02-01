#include <iostream>
#include <iomanip>
#include <random>
#include <omp.h>

// Tamaño de array
static constexpr int N = 1000;        
static constexpr int MOSTRAR = 10;    


static constexpr int THREADS = 4;     
static constexpr int CHUNK   = 100;   

void imprimirPrimeros(const float* arr, const char* nombre) {
    std::cout << nombre << ": ";
    for (int i = 0; i < MOSTRAR; ++i) {
        std::cout << std::fixed << std::setprecision(2) << arr[i] << " - ";
    }
    std::cout << "\n";
}

bool validarSuma(const float* a, const float* b, const float* c) {
    const float eps = 1e-5f;
    for (int i = 0; i < N; ++i) {
        float esperado = a[i] + b[i];
        float diff = std::abs(c[i] - esperado);
        if (diff > eps) return false;
    }
    return true;
}

int main() {
    std::cout << "Solucion: Suma de arreglos en paralelo con OpenMP\n";
    std::cout << "Parametros -> N=" << N
              << " | THREADS=" << THREADS
              << " | CHUNK=" << CHUNK << "\n\n";

    // Arrays en stack
    float a[N], b[N], c[N];

    // Generacion de datos 
    std::mt19937 rng(12345); 
    std::uniform_real_distribution<float> dist(0.0f, 100.0f);

    for (int i = 0; i < N; ++i) {
        a[i] = dist(rng);
        b[i] = dist(rng);
    }

    //  Numero de hilos
    omp_set_num_threads(THREADS);

    //For paralelo 
    #pragma omp parallel for default(none) shared(a, b, c) schedule(static, CHUNK)
    for (int i = 0; i < N; ++i) {
        c[i] = a[i] + b[i];
    }

    //Titulo de valores
    std::cout << "Imprimiendo primeros " << MOSTRAR << " valores:\n";
    imprimirPrimeros(a, "Arreglo A");
    imprimirPrimeros(b, "Arreglo B");
    imprimirPrimeros(c, "Arreglo C (A+B)");

    //Validacion
    bool ok = validarSuma(a, b, c);
    std::cout << "\nValidacion: " << (ok ? "correcta" : "fallida") << "\n";

    return 0;
}
