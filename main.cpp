#include <stdio.h>
#include <iostream>
#include <queue> 
#include <cstdlib> 
#include <ctime>   
#include <string> 

using namespace std;

//creo una estructura proceso

struct proceso {
    string nombre_proceso;
    int tiempo_de_llegada = 0;
    int rafaga = 0;
};

queue<proceso> Pila_procesos;   //es una cola pero lo usamos pa guardar nomas los procesos
queue<proceso> salida_procesos_RR;
queue<proceso> salida_procesos_FCFS;

void crea_procesos(queue<proceso>&);
void round_robin(proceso&, int&, int, queue<proceso>&, queue<proceso>&);
void algoritmo_FCFS(proceso&, int&, queue<proceso>&);
void muestra_colas(queue<proceso>,queue<proceso>);

int main() {

    cout << "-----------Menu De Opciones ----------------" << endl;
    cout << " 1.- Aplicacion de algoritmos de cpu RR y FCFS " << endl;

    printf("Hello World\n");
    int timer_sistema = 1;
    int quantum = 0;
    cout << "Define el valor del quantum para los procesos: ";
    cin >> quantum;
    
    crea_procesos(Pila_procesos);
    
    while (!Pila_procesos.empty()) {
        proceso entra = Pila_procesos.front();
        round_robin(entra, timer_sistema, quantum, salida_procesos_RR, salida_procesos_FCFS);
        Pila_procesos.pop();
    }
    
    muestra_colas(salida_procesos_RR,salida_procesos_FCFS);
    
    return 0;
}

void crea_procesos(queue<proceso>& Pila) {
    srand(time(nullptr));
    for (int i = 0; i < 10; i++) {
        int llegada_aleatorio = rand() % 5 + 1;
        int rafaga_aleatorio = rand() % 4 + 1;
        proceso nuevo;
        nuevo.nombre_proceso = "Proceso " + to_string(i);
        nuevo.tiempo_de_llegada = llegada_aleatorio;
        nuevo.rafaga = rafaga_aleatorio;
        Pila.push(nuevo);
    }
}

void round_robin(proceso& Actual, int& timer_sistema, int quantum, queue<proceso>& pilarr, queue<proceso>& pilafcfs) {
    if (Actual.rafaga <= quantum) {
        Actual.rafaga = 0;
        cout << "\nEl " << Actual.nombre_proceso << " se terminó en Algoritmo Round Robin" << endl;
        timer_sistema += quantum;
        pilarr.push(Actual);
    } else {
        Actual.rafaga -= quantum;
        timer_sistema += quantum;
        cout << "\nEl " << Actual.nombre_proceso << " fue interrumpido";
        algoritmo_FCFS(Actual, timer_sistema, pilafcfs);
    }
}

void algoritmo_FCFS(proceso& nuevo, int& timer_sistema, queue<proceso>& pilafcfs) {
    timer_sistema += nuevo.rafaga;
    nuevo.rafaga = 0;
    cout << "\nEl " << nuevo.nombre_proceso << " se terminó exitosamente en el FCFS";
    pilafcfs.push(nuevo);
}

void muestra_colas(queue<proceso> rr , queue<proceso> fcfs ){
    
    cout << "\nProcesos que terminaron en round robin: " << endl;
    while(!rr.empty()){
        proceso aux = rr.front();
        cout << " [ " << aux.nombre_proceso << " ] " << endl;
        rr.pop();
    }
    
    cout << "\nProcesos que terminaron en fcfs: " << endl;
        
    while(!fcfs.empty()){
        proceso aux = fcfs.front();
        cout << " [ " << aux.nombre_proceso << " ] " << endl;
        fcfs.pop();
    }
    
}
