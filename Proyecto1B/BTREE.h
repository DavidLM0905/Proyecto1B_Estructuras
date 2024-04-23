#include <iostream>
#include <conio.h>

using namespace std;

#define MAX 4
#define MIN 2

time_t C_BTREE, L_BTREE, B_BTREE, D_BTREE;

struct NodoBtree {

	int Cedula[MAX + 1];

	char Codelec[MAX + 1][7];
	char FechaVencimientoCedula[MAX + 1][9];
	char Junta[MAX + 1][6];
	char Nombre[MAX + 1][31];
	char PrimerApellido[MAX + 1][27];
	char SegundoApellido[MAX + 1][27];

	int count;
	NodoBtree* link[MAX + 1];
};

NodoBtree* rootBTREE;
 
NodoBtree* NuevoNodo(int Cedula, NodoBtree* Hijo, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	NodoBtree* NuevoNodo = new NodoBtree;

	NuevoNodo->Cedula[1] = Cedula;

	strcpy_s(NuevoNodo->Codelec[1], Codelec);
	strcpy_s(NuevoNodo->FechaVencimientoCedula[1], Fecha);
	strcpy_s(NuevoNodo->Junta[1], Junta);
	strcpy_s(NuevoNodo->Nombre[1], Nombre);
	strcpy_s(NuevoNodo->PrimerApellido[1], PrimerApellido);
	strcpy_s(NuevoNodo->SegundoApellido[1], SegundoApellido);

	NuevoNodo->count = 1;
	NuevoNodo->link[0] = rootBTREE;
	NuevoNodo->link[1] = Hijo;

	return NuevoNodo;
}

void ColocarNodo(int Cedula, int pos, NodoBtree* Nodo, NodoBtree* Hijo, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	int j = Nodo->count;

	while (j > pos) {

		Nodo->Cedula[j + 1] = Nodo->Cedula[j];

		strcpy_s(Nodo->Codelec[j + 1], Nodo->Codelec[j]);
		strcpy_s(Nodo->FechaVencimientoCedula[j + 1], Nodo->FechaVencimientoCedula[j]);
		strcpy_s(Nodo->Junta[j + 1], Nodo->Junta[j]);
		strcpy_s(Nodo->Nombre[j + 1], Nodo->Nombre[j]);
		strcpy_s(Nodo->PrimerApellido[j + 1], Nodo->PrimerApellido[j]);
		strcpy_s(Nodo->SegundoApellido[j + 1], Nodo->SegundoApellido[j]);

		Nodo->link[j + 1] = Nodo->link[j];

		j--;
	}

	Nodo->Cedula[j + 1] = Cedula;

	strcpy_s(Nodo->Codelec[j + 1], Codelec);
	strcpy_s(Nodo->FechaVencimientoCedula[j + 1], Fecha);
	strcpy_s(Nodo->Junta[j + 1], Junta);
	strcpy_s(Nodo->Nombre[j + 1], Nombre);
	strcpy_s(Nodo->PrimerApellido[j + 1], PrimerApellido);
	strcpy_s(Nodo->SegundoApellido[j + 1], SegundoApellido);

	Nodo->link[j + 1] = Hijo;
	Nodo->count++;
}

void DividirNodo(int Cedula, int* pCedula, int pos, NodoBtree* Nodo, NodoBtree* Hijo, NodoBtree** NuevoNodo, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	int median, j;

	if (pos > MIN) {
		median = MIN + 1;
	}
		
	else {
		median = MIN;
	}

	*NuevoNodo = new NodoBtree;
	j = median + 1;

	while (j <= MAX) {
		(*NuevoNodo)->Cedula[j - median] = Nodo->Cedula[j];
		strcpy_s((*NuevoNodo)->Codelec[j - median], Nodo->Codelec[j]);
		strcpy_s((*NuevoNodo)->FechaVencimientoCedula[j - median], Nodo->FechaVencimientoCedula[j]);
		strcpy_s((*NuevoNodo)->Junta[j - median], Nodo->Junta[j]);
		strcpy_s((*NuevoNodo)->Nombre[j - median], Nodo->Nombre[j]);
		strcpy_s((*NuevoNodo)->PrimerApellido[j - median], Nodo->PrimerApellido[j]);
		strcpy_s((*NuevoNodo)->SegundoApellido[j - median], Nodo->SegundoApellido[j]);
		(*NuevoNodo)->link[j - median] = Nodo->link[j];
		j++;
	}

	Nodo->count = median;
	(*NuevoNodo)->count = MAX - median;

	if (pos <= MIN) {
		ColocarNodo(Cedula, pos, Nodo, Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
	}

	else {
		ColocarNodo(Cedula, pos - median, *NuevoNodo, Hijo, Codelec,  Fecha,  Junta,  Nombre,  PrimerApellido,  SegundoApellido);
	}

	*pCedula = Nodo->Cedula[Nodo->count];
	(*NuevoNodo)->link[0] = Nodo->link[Nodo->count];
	Nodo->count--;
}

int SetCedulaNodo(int Cedula, int* pCedula, NodoBtree* Nodo, NodoBtree** Hijo, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	int pos;

	if (!Nodo) {
		*pCedula = Cedula;
		*Hijo = NULL;
		return 1;
	}

	if (Cedula < Nodo->Cedula[1]) {
		pos = 0;
	}

	else {
		for (pos = Nodo->count; (Cedula < Nodo->Cedula[pos] && pos > 1); pos--); {
			if (Cedula == Nodo->Cedula[pos]) {
				cout << "No está permitido nodos duplicados\n";
				return 0;
			}
		}
		
	}

	if (SetCedulaNodo(Cedula, pCedula, Nodo->link[pos], Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido)) {

		if (Nodo->count < MAX) {
			ColocarNodo(*pCedula, pos, Nodo, *Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
		}

		else {
			DividirNodo(*pCedula, pCedula, pos, Nodo, *Hijo, Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
			return 1;
		}
	}

	return 0;
}

void InsertarBTREE(int Cedula, char Codelec[7], char Fecha[9], char Junta[6], char Nombre[31], char PrimerApellido[27], char SegundoApellido[27]) {

	int flag;
	int i;
	NodoBtree* Hijo;
	flag = SetCedulaNodo(Cedula, &i, rootBTREE, &Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);

	if (flag) {
		rootBTREE = NuevoNodo(i, Hijo, Codelec, Fecha, Junta, Nombre, PrimerApellido, SegundoApellido);
	}
		
}

bool Busqueda(int Cedula, int* pos, NodoBtree* MiNodo) {

	if (!MiNodo) {
		return false;
	}

	if (Cedula < MiNodo->Cedula[1]) {
		*pos = 0;
	}

	else {

		for (*pos = MiNodo->count; (Cedula < MiNodo->Cedula[*pos] && *pos > 1); (*pos)--); {

			if (Cedula == MiNodo->Cedula[*pos]) {
				cout << "Se ha encontrado la cedula:" << endl;
				cout << "Cedula : " << MiNodo->Cedula[*pos] << " Codelec: " << MiNodo->Codelec[*pos] << " FechaVencimientoCedula: " << MiNodo->FechaVencimientoCedula[*pos] << " Junta: " << MiNodo->Junta[*pos] << " Nombre: " << MiNodo->Nombre[*pos] << " PrimerApellido: " << MiNodo->PrimerApellido[*pos] << " SegundoApellido: " << MiNodo->SegundoApellido[*pos] << endl;
				return true;
			}
		}
	}

	Busqueda(Cedula, pos, MiNodo->link[*pos]);
	return false;
}

void CargarBTREE(PtrNodoLista& Lista) {

	cout << endl << "=== Cargando el Padron electoral en el ArbolBTREE... ===" << endl;

	time_t inicio, fin;
	inicio = time(NULL);

	int cont = 0;
	PtrNodoLista Aux;
	Aux = Lista;

	while (Aux != NULL) {

		InsertarBTREE(Aux->Cedula, Aux->Codelec, Aux->FechaVencimientoCedula, Aux->Junta, Aux->Nombre, Aux->PrimerApellido, Aux->SegundoApellido);
		Aux = Aux->PtrSiguiente;
		cont++;

	}

	fin = time(NULL);
	auto tiempo = difftime(fin, inicio);
	cout << "Padron electoral cargado en el ArbolBTREE" << endl;
	cout << "Tiempo tardado: " << tiempo << " s" << endl;
	cout << "Elementos cargados: " << cont << endl;
	C_BTREE = tiempo;
}

void ListarBTree(NodoBtree* MiNodo, bool opcion) {

	int i;

	if (opcion == true) {

		if (MiNodo) {

			for (i = 0; i < MiNodo->count; i++) {
				ListarBTree(MiNodo->link[i], opcion);
				cout << "Cedula: " << MiNodo->Cedula[i + 1] << " Codelec: " << MiNodo->Codelec[i + 1] << " FechaVencimientoCedula: " << MiNodo->FechaVencimientoCedula[i + 1] << " Junta: " << MiNodo->Junta[i + 1] << " Nombre: " << MiNodo->Nombre[i + 1] << " PrimerApellido: " << MiNodo->PrimerApellido[i + 1] << " SegundoApellido: " << MiNodo->SegundoApellido[i + 1] << endl;
			}

			ListarBTree(MiNodo->link[i], opcion);
		}
	}

	else {

		if (MiNodo) {

			for (i = 0; i < MiNodo->count; i++) {
				ListarBTree(MiNodo->link[i], opcion);
			}

			ListarBTree(MiNodo->link[i], opcion);
		}
	}
}

/*
void CopiarSucesor(NodoBtree* MiNodo, int pos) {

	NodoBtree* dummy;
	dummy = MiNodo->link[pos];

	for (; dummy->link[0] != NULL;) {
		dummy = dummy->link[0];
	}

	MiNodo->Cedula[pos] = dummy->Cedula[1];

}

void RemoveCedula(NodoBtree* MiNodo, int pos) {

	int i = pos + 1;

	while (i <= MiNodo->count) {

		MiNodo->Cedula[i - 1] = MiNodo->Cedula[i];
		MiNodo->link[i - 1] = MiNodo->link[i];
		i++;
	}

	MiNodo->count--;
}

void RotacionDerecha(NodoBtree* MiNodo, int pos) {

	NodoBtree* x = MiNodo->link[pos];
	int j = x->count;

	while (j > 0) {
		x->Cedula[j + 1] = x->Cedula[j];
		x->link[j + 1] = x->link[j];
	}

	x->Cedula[1] = MiNodo->Cedula[pos];
	x->link[1] = x->link[0];
	x->count++;

	x = MiNodo->link[pos - 1];
	MiNodo->Cedula[pos] = x->Cedula[x->count];
	MiNodo->link[pos] = x->link[x->count];
	x->count--;
	return;
}

void RotacionIzquierda(NodoBtree* MiNodo, int pos) {

	int j = 1;
	NodoBtree* x = MiNodo->link[pos - 1];

	x->count++;
	x->Cedula[x->count] = MiNodo->Cedula[pos];
	x->link[x->count] = MiNodo->link[pos]->link[0];

	x = MiNodo->link[pos];
	MiNodo->Cedula[pos] = x->Cedula[1];
	x->link[0] = x->link[1];
	x->count--;

	while (j <= x->count) {
		x->Cedula[j] = x->Cedula[j + 1];
		x->link[j] = x->link[j + 1];
		j++;
	}
	return;
}

void UnirNodos(NodoBtree* MiNodo, int pos) {

	int j = 1;
	NodoBtree* x1 = MiNodo->link[pos], * x2 = MiNodo->link[pos - 1];

	x2->count++;
	x2->Cedula[x2->count] = MiNodo->Cedula[pos];
	x2->link[x2->count] = MiNodo->link[0];

	while (j <= x1->count) {
		x2->count++;
		x2->Cedula[x2->count] = x1->Cedula[j];
		x2->link[x2->count] = x1->link[j];
		j++;
	}

	j = pos;

	while (j < MiNodo->count) {
		MiNodo->Cedula[j] = MiNodo->Cedula[j + 1];
		MiNodo->link[j] = MiNodo->link[j + 1];
		j++;
	}

	MiNodo->count--;
	free(x1);
}

void AjustarNodo(NodoBtree* MiNodo, int pos) {

	if (!pos) {

		if (MiNodo->link[1]->count > MIN) {
			RotacionIzquierda(MiNodo, 1);
		}

		else {
			UnirNodos(MiNodo, 1);
		}
	}

	else {

		if (MiNodo->count != pos) {

			if (MiNodo->link[pos - 1]->count > MIN) {
				RotacionDerecha(MiNodo, pos);
			}

			else {

				if (MiNodo->link[pos + 1]->count > MIN) {
					RotacionIzquierda(MiNodo, pos + 1);
				}

				else {
					UnirNodos(MiNodo, pos);
				}
			}
		}

		else {

			if (MiNodo->link[pos - 1]->count > MIN)
				RotacionDerecha(MiNodo, pos);

			else
				UnirNodos(MiNodo, pos);
		}
	}
}

int BorrarDeNodo(int Cedula, NodoBtree* MiNodo) {

	int pos, flag = 0;

	if (MiNodo) {

		if (Cedula < MiNodo->Cedula[1]) {
			pos = 0;
			flag = 0;
		}

		else {

			for (pos = MiNodo->count; (Cedula < MiNodo->Cedula[pos] && pos > 1); pos--); {
				if (Cedula == MiNodo->Cedula[pos]) {
					flag = 1;
				}
				else {
					flag = 0;
				}
			}
		}

		if (flag) {

			if (MiNodo->link[pos - 1]) {
				CopiarSucesor(MiNodo, pos);
				flag = BorrarDeNodo(MiNodo->Cedula[pos], MiNodo->link[pos]);
				if (flag == 0) {
					cout << "No existe en el B-Tree\n";
				}
			}

			else {
				RemoveCedula(MiNodo, pos);
			}
		}

		else {
			flag = BorrarDeNodo(Cedula, MiNodo->link[pos]);
		}

		if (MiNodo->link[pos]) {
			if (MiNodo->link[pos]->count < MIN)
				AjustarNodo(MiNodo, pos);
		}
	}
	return flag;
}

void Borrado(int Cedula, NodoBtree* MiNodo) {

	NodoBtree* tmp;

	if (!BorrarDeNodo(Cedula, MiNodo)) {
		cout << "No existe ese Cedulaor en el B-Tree\n";
		system("pause");
		return;
	}

	else {
		if (MiNodo->count == 0) {
			tmp = MiNodo;
			MiNodo = MiNodo->link[0];
			free(tmp);
		}
	}

	rootBTREE = MiNodo;
	cout << "Borrado" << endl;
	system("pause");
	return;
}

*/