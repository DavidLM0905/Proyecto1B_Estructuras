#include <iostream>
#include <stdio.h>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm> 

time_t C_BB, L_BB, B_BB, D_BB;

using namespace std;

struct NodoBB { 

	int Cedula;
	char Codelec[7];
	char FechaVencimientoCedula[9];
	char Junta[6];
	char Nombre[31];
	char PrimerApellido[27];
	char SegundoApellido[27];

	NodoBB* Izquierdo;
	NodoBB* Derecho;

};

bool InsertarBB(NodoBB*& Raiz, int Cedula, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27])  {

	if (Raiz == NULL) { 

		Raiz = new(NodoBB); 

		Raiz->Cedula = Cedula; 

		strcpy_s(Raiz->Codelec, Codelec);
		strcpy_s(Raiz->FechaVencimientoCedula, Fecha);
		strcpy_s(Raiz->Junta, Junta);
		strcpy_s(Raiz->Nombre, Nombre);
		strcpy_s(Raiz->PrimerApellido, PrimerApellido);
		strcpy_s(Raiz->SegundoApellido, SegundoApellido);

		Raiz->Izquierdo = NULL; 
		Raiz->Derecho = NULL;

		return true;
	}

	else {

		if (Cedula == Raiz->Cedula) {
			return false;
		}

		else {

			if (Cedula < Raiz->Cedula) {
				return InsertarBB(Raiz->Izquierdo, Cedula, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
				
			} 

			else{
				return InsertarBB(Raiz->Derecho, Cedula, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
			}		
		} 	
	}
}

void LiberarBB(NodoBB*& Raiz) { 

	if (Raiz != NULL) {

		LiberarBB(Raiz->Izquierdo);
		LiberarBB(Raiz->Derecho);
		delete(Raiz); Raiz = NULL; 
	}

}

NodoBB* BuscarBB(NodoBB* Raiz, int Cedula) { 

	if (Raiz == NULL) {  
		return NULL; 
	}

	else {

		if (Cedula == Raiz->Cedula) {
			return Raiz;
		}

		else {
			if (Cedula < Raiz->Cedula) {
				return BuscarBB(Raiz->Izquierdo, Cedula);
			}
			else {
				return BuscarBB(Raiz->Derecho, Cedula);
			}
		}
	}
}

void EnOrdenBB(NodoBB* Raiz, bool opcion) {

	if (opcion == true) {

		if (Raiz != NULL) {

			EnOrdenBB(Raiz->Izquierdo, opcion);
			cout << "Cedula: " << Raiz->Cedula << " Codelec: " << Raiz->Codelec << " FechaVencimientoCedula: " << Raiz->FechaVencimientoCedula << " Junta: " << Raiz->Junta << " Nombre: " << Raiz->Nombre << " PrimerApellido: " << Raiz->PrimerApellido << " SegundoApellido: " << Raiz->SegundoApellido << endl;
			EnOrdenBB(Raiz->Derecho, opcion);
		}
	}

	else {

		if (Raiz != NULL) {
			EnOrdenBB(Raiz->Izquierdo, opcion);
			EnOrdenBB(Raiz->Derecho, opcion);
		}
	}
}

vector<PtrNodoLista> MezclarLista(PtrNodoLista& Lista) {

	vector<PtrNodoLista> nodos;
	PtrNodoLista Aux = Lista;

	while (Aux != nullptr) {

		nodos.push_back(Aux);
		Aux = Aux->PtrSiguiente;
	}

	srand(time(nullptr));
	random_shuffle(nodos.begin(), nodos.end());

	return nodos;
}

NodoBB CargarBB(NodoBB*& NodoBB, PtrNodoLista& Lista) {

	cout << endl << "=== Cargando el Padron electoral en el ArbolBB... ===" << endl;

	time_t inicio, fin;
	inicio = time(NULL);

	int cont = 0;

	vector<PtrNodoLista> nodos = MezclarLista(Lista);

	for (const auto& nodo : nodos) {
		
		InsertarBB(NodoBB, nodo->Cedula, nodo->Codelec, nodo->FechaVencimientoCedula, nodo->Junta, nodo->Nombre, nodo->PrimerApellido, nodo->SegundoApellido);
		cont++;

	}

	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Padron electoral cargado en el ArbolBB" << endl;
	cout << "Tiempo tardado: " << tiempo << " ms" << endl;
	cout << "Elementos cargados: " << cont << endl;

	C_BB = tiempo;
	system("pause");

	return *NodoBB;
}
