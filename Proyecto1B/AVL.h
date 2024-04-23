#include<stdio.h>
#include<stdlib.h>

time_t C_AVL, L_AVL, B_AVL, D_AVL;

 struct NodoAVL {

	int Cedula;
	char Codelec[7];
	char FechaVencimientoCedula[9];
	char Junta[6];
	char Nombre[31];
	char PrimerApellido[27];
	char SegundoApellido[27];

	NodoAVL* izquierda;
    NodoAVL* derecha;
	int altura;

}PtrNodoAV;

int altura(NodoAVL* N) {
	if (N == NULL) {
		return 0;
	}
	return N->altura;
}

int max(int a, int b) {
	return (a > b) ? a : b;
}

int obtenerbalance(NodoAVL* N) {
	if (N == NULL) {
		return 0;
	}
	
	return altura(N->izquierda) - altura(N->derecha);
}

NodoAVL* RotarDerecha(NodoAVL* y) {

	 NodoAVL* x = y->izquierda;
	 NodoAVL* T2 = x->derecha;

	x->derecha = y;
	y->izquierda = T2;

	y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;
	x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;

	return x;
}

NodoAVL* RotarIzquierda(NodoAVL* x) {

	 NodoAVL* y = x->derecha;
	 NodoAVL* T2 = y->izquierda;

	y->izquierda = x;
	x->derecha = T2;

	x->altura = max(altura(x->izquierda), altura(x->derecha)) + 1;
	y->altura = max(altura(y->izquierda), altura(y->derecha)) + 1;

	return y;
}

NodoAVL* NuevoNodo(int Cedula, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	NodoAVL* NodoAVL = new struct NodoAVL;

	NodoAVL->Cedula = Cedula;
	strcpy_s(NodoAVL->Codelec, Codelec);
	strcpy_s(NodoAVL->FechaVencimientoCedula, Fecha);
	strcpy_s(NodoAVL->Junta, Junta);
	strcpy_s(NodoAVL->Nombre, Nombre);
	strcpy_s(NodoAVL->PrimerApellido, PrimerApellido);
	strcpy_s(NodoAVL->SegundoApellido, SegundoApellido);

	NodoAVL->izquierda = NULL;
	NodoAVL->derecha = NULL;
	NodoAVL->altura = 1; 

	
	return(NodoAVL);
}

NodoAVL* Insertar(NodoAVL* NodoAVL, int Cedula, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	if (NodoAVL == NULL) {
		return(NuevoNodo(Cedula, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido));
	}

	if (Cedula < NodoAVL->Cedula) {
		NodoAVL->izquierda = Insertar(NodoAVL->izquierda, Cedula, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
	}

	else if (Cedula > NodoAVL->Cedula) {
		NodoAVL->derecha = Insertar(NodoAVL->derecha, Cedula, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
	}

	else {
		return NodoAVL;
	}

	NodoAVL->altura = 1 + max(altura(NodoAVL->izquierda), altura(NodoAVL->derecha));
	int balance = obtenerbalance(NodoAVL);

	if (balance > 1 && Cedula < NodoAVL->izquierda->Cedula) {
		return RotarDerecha(NodoAVL);
	}

	if (balance < -1 && Cedula > NodoAVL->derecha->Cedula) {
		return RotarIzquierda(NodoAVL);
	}
		
	if (balance > 1 && Cedula > NodoAVL->izquierda->Cedula) {

		NodoAVL->izquierda = RotarIzquierda(NodoAVL->izquierda);
		return RotarDerecha(NodoAVL);
	}

	if (balance < -1 && Cedula < NodoAVL->derecha->Cedula) {
		NodoAVL->derecha = RotarDerecha(NodoAVL->derecha);
		return RotarIzquierda(NodoAVL);
	}

	return NodoAVL;
}

NodoAVL* BuscarAVL(NodoAVL* NodoAVL, int Cedula) {

	if (NodoAVL == NULL) {
		return NULL;
	}

	else {

		if (Cedula == NodoAVL->Cedula) {
			cout << NodoAVL->Nombre << endl;
			return NodoAVL;
		}

		else {
			if (Cedula < NodoAVL->Cedula) {
				return BuscarAVL(NodoAVL->izquierda, Cedula);
			}
			else {
				return BuscarAVL(NodoAVL->derecha, Cedula);
			}
		}
	}
}

void EnOrdenAVL(NodoAVL* Raiz, bool opcion) {

	if (opcion == true) {

		if (Raiz != NULL) {

			EnOrdenAVL(Raiz->izquierda, opcion);
			cout << "Cedula: " << Raiz->Cedula << " Codelec: " << Raiz->Codelec << " FechaVencimientoCedula: " << Raiz->FechaVencimientoCedula << " Junta: " << Raiz->Junta << " Nombre: " << Raiz->Nombre << " PrimerApellido: " << Raiz->PrimerApellido << " SegundoApellido: " << Raiz->SegundoApellido << endl;
			EnOrdenAVL(Raiz->derecha, opcion);
		}
	}

	else {

		if (Raiz != NULL) {
			EnOrdenAVL(Raiz->izquierda, opcion);
			EnOrdenAVL(Raiz->derecha, opcion);
		}
	}

}

void CargarAVL(NodoAVL*& NodoAVL, PtrNodoLista& Lista) {

	cout << endl << "=== Cargando el Padron electoral en el ArbolAVL... ===" << endl;

	time_t inicio, fin;
	inicio = time(NULL);

	int cont = 0;
	PtrNodoLista Aux;
	Aux = Lista;

	while (Aux != NULL) {

		NodoAVL = Insertar(NodoAVL, Aux->Cedula, Aux->Codelec, Aux->FechaVencimientoCedula, Aux->Junta, Aux->Nombre, Aux->PrimerApellido, Aux->SegundoApellido);
		Aux = Aux->PtrSiguiente;
		cont++;

	}

	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Padron electoral cargado en el ArbolAVL" << endl;
	cout << "Tiempo tardado: " << tiempo << " s" << endl;
	cout << "Elementos cargados: " << cont << endl;
	C_AVL = tiempo;

	system("pause");
}

void LiberarAVL(NodoAVL*& NodoAVL) {

	if (NodoAVL != NULL) {

		LiberarAVL(NodoAVL->izquierda);
		LiberarAVL(NodoAVL->derecha);
		delete(NodoAVL); NodoAVL = NULL;
	}

}