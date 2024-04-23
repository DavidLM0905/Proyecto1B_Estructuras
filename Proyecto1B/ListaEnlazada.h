#include <cctype> 
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

time_t C_Lista, B_Lista, L_Lista, D_Lista;

typedef struct NodoLista { 

	int Cedula;
	char Codelec[7];
	char FechaVencimientoCedula[9];
	char Junta[6];
	char Nombre[31];
	char PrimerApellido[27];
	char SegundoApellido[27];

	NodoLista* PtrSiguiente;

}*PtrNodoLista;

void InsertarVotante(PtrNodoLista& Lista, char linea[119]) {

	PtrNodoLista Aux = new (NodoLista);
	Aux->PtrSiguiente = Lista;
	Lista = Aux;


	Lista->Cedula = stoi(string(linea).substr(0, 9));

	strncpy_s(Lista->Codelec, linea + 10, 6);
	strncpy_s(Lista->FechaVencimientoCedula, linea + 19, 8);
	strncpy_s(Lista->Junta, linea + 28, 5);
	strncpy_s(Lista->Nombre, linea + 34, 30);
	strncpy_s(Lista->PrimerApellido, linea + 65, 26);
	strncpy_s(Lista->SegundoApellido, linea + 92, 26);
	
}

void CargarVotantes(PtrNodoLista& Lista, char* Archivo) {

	cout << "=== Cargando el Padron electoral en la Lista Enlazada... ===" << endl;

	int cont = 1;
	time_t inicio, fin;
	inicio = time(NULL);
	FILE* archivo;

	if (fopen_s(&archivo, Archivo, "r") != 0) {
		cout << "No se pudo abrir el archivo" << endl;
	}

	else {

		char linea[119];

		while (fgets(linea, 119, archivo) != NULL) {
			if (cont % 2 != 0) {
				InsertarVotante(Lista, linea);
				
			}
			cont++;
		}

		fclose(archivo);
	}
	
	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Padron electoral cargado en la Lista Enlazada" << endl;
	cout << "Tiempo tardado: " << tiempo << " s" << endl;
	cout << "Elementos cargados: " << cont/2 << endl;

	C_Lista = tiempo;
	system("pause");
}

void EliminarLista(PtrNodoLista& Lista) {

	PtrNodoLista Aux = Lista;
	time_t inicio, fin;

	inicio = time(NULL);

	while (Aux != NULL) {
		Lista = Lista->PtrSiguiente;
		delete(Aux);
		Aux = Lista;
	}

	fin = time(NULL);

	cout << "----------------------------Padron liberado--------------------------------" << endl;
	printf("La liberacion del padron ha tardado : %f segundos.\n", difftime(fin, inicio));
	cout << "----------------------------Padron liberado--------------------------------" << endl;
	system("pause");
}

void ImprimirLista(PtrNodoLista& Lista, bool opcion) {

	cout << " === Listando elementos en la Lista Enlazada... ===" << endl;

	time_t inicio, fin;
	inicio = time(NULL);

	int index = 1;
	PtrNodoLista Aux;
	Aux = Lista;

	if (opcion == true) {
		_Thrd_sleep_for(200);

		while (Aux != NULL) {
			cout << "Cedula: " << Aux->Cedula << " Codelec: " << Aux->Codelec << " FechaVencimientoCedula: " << Aux->FechaVencimientoCedula << " Junta: " << Aux->Junta << " Nombre: " << Aux->Nombre << " PrimerApellido: " << Aux->PrimerApellido << " SegundoApellido: " << Aux->SegundoApellido << endl;
			Aux = Aux->PtrSiguiente;
			index++;
		}

	}

	else {

		while (Aux != NULL) {

			Aux = Aux->PtrSiguiente;
			index++;

		}
	}


	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Tiempo tardado: " << tiempo << " s" << endl;
	L_Lista = tiempo;

}

PtrNodoLista BuscarElemento(PtrNodoLista& Lista, int Cedula) {

	cout << " === Buscando la cedula en la Lista Enlazada... ===" << endl;

	time_t inicio, fin;
	inicio = time(NULL);

	bool encontro = false;
	PtrNodoLista Aux;
	Aux = Lista;

	while ((!encontro == true) && (Aux != NULL)) {

		if (Aux->Cedula == Cedula) {
			encontro = true;
			cout << "Se ha encontrado la cedula:\n";
			cout << "Cedula : " << Aux->Cedula << " Codelec: " << Aux->Codelec << " FechaVencimientoCedula: " << Aux->FechaVencimientoCedula << " Junta: " << Aux->Junta << " Nombre: " << Aux->Nombre << " PrimerApellido: " << Aux->PrimerApellido << " SegundoApellido: " << Aux->SegundoApellido << endl;
		}
			
		else {
			Aux = Aux->PtrSiguiente;
		}
	}

	if (encontro == false) {
		cout << "No se encontro la persona con la cedula buscada" << endl;
	}

	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Tiempo tardado: " << tiempo << " s" << endl;
	B_Lista = tiempo;

	return Aux;
}

