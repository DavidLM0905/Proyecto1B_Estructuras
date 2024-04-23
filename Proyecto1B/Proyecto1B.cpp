#include "ListaEnlazada.h"
#include "AVL.h"
#include "ArbolBB.h"
#include "BTREE.h"
#include <iostream>

#define MAX 4
char Archivo[] = "PADRON_COMPLETO.txt";

int main() {

	time_t inicio, fin, tiempo;
	bool cargado = false;
	bool imprimir = 1;
	int opcion, cedula;

	NodoBB* BuscadoBB;
	NodoAVL* BuscadoAVL;

	PtrNodoLista ListaMaestra = NULL;
	NodoAVL* AVL = NULL;
	NodoBB* BB = NULL;
	rootBTREE = NULL;

	while (true) {

		cout << "================================================" << endl;
		cout << "Bienvenido al comparador de Estructuras de Datos" << endl;
		cout << "================================================" << endl;
		cout << endl << "Opciones a comparar: " << endl;
		cout << "1. Cargar datos " << endl;
		cout << "2. Listar datos" << endl;
		cout << "3. Busqueda de datos" << endl;
		cout << "4. Liberar de datos" << endl;
		cout << "5. Salir / Reporte de tiempo" << endl;
		cout << endl << "Porfavor digite el numero de opcion que desea ejecutar: ";

		cin >> opcion;
		switch (opcion) {

		case 1:

			system("cls");
			cout << "========== Ha selecionado: 1.Carga de Datos ==========" << endl;

			CargarVotantes(ListaMaestra, Archivo);
			CargarBB(BB, ListaMaestra);
			CargarAVL(AVL, ListaMaestra);
			CargarBTREE(ListaMaestra);

			cargado = true;

			system("pause");
			system("cls");

			break;

		case 2:

			if (cargado == false) {
				cout << "====================== ERORR =====================" << endl;
				cout << "Aun no se han cargado datos, porfavor cargar datos" << endl;
				cout << "====================== ERORR =====================" << endl;
				system("pause");
				system("cls");
				break;
			}
			
			system("cls");
			cout << "=========== Ha selecionado: 2.Listar Datos ===========" << endl;

			cout << endl << "Si desea unicamente recorrer las estructuras sin impresion digite 0: ";
			cin >> imprimir;

			ImprimirLista(ListaMaestra, imprimir);
			system("pause");

			cout << endl << " === Listando elementos en el ArbolBB... ===" << endl;
			inicio = time(NULL);

			EnOrdenBB(BB, imprimir);

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			L_BB = tiempo;
			system("pause");

			cout << endl << " === Listando elementos en el ArbolAVL... ===" << endl;
			inicio = time(NULL);

			EnOrdenAVL(AVL, imprimir);

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			L_AVL = tiempo;
			system("pause");

			cout << endl << " === Listando elementos en el ArbolBTREE... ===" << endl;
			inicio = time(NULL);

			ListarBTree(rootBTREE, imprimir);

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			L_BTREE = tiempo;

			system("pause");
			system("cls");

			break;

		case 3:

			if (cargado == false) {
				cout << "====================== ERORR =====================" << endl;
				cout << "Aun no se han cargado datos, porfavor cargar datos" << endl;
				cout << "====================== ERORR =====================" << endl;
				system("pause");
				system("cls");
				break;
			}
		
			system("cls");
			cout << "========= Ha selecionado: 3.Busqueda de Datos =========" << endl;

			cout << endl << "Porfavor ingrese el numero de cedula que desea buscar: ";
			cin >> cedula;

			BuscarElemento(ListaMaestra,cedula);
			system("pause");

			cout << endl << " === Buscando la cedula en el ArbolBB... ===" << endl;

			inicio = time(NULL);
			BuscadoBB = BuscarBB(BB, cedula);

			if (BuscadoBB != NULL) {
				cout << "Se ha encontrado la cedula:\n";
				cout << "Cedula : " << BuscadoBB->Cedula << " Codelec: " << BuscadoBB->Codelec << " FechaVencimientoCedula: " << BuscadoBB->FechaVencimientoCedula << " Junta: " << BuscadoBB->Junta << " Nombre: " << BuscadoBB->Nombre << " PrimerApellido: " << BuscadoBB->PrimerApellido << " SegundoApellido: " << BuscadoBB->SegundoApellido << endl;
			}
			else {
				cout << "No se encontro la persona con la cedula buscada" << endl;
			}

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			B_BB = tiempo;
			system("pause");

			cout << endl << " === Buscando la cedula en el ArbolALV... ===" << endl;

			inicio = time(NULL);
			BuscadoAVL = BuscarAVL(AVL, cedula);

			if (BuscadoBB != NULL) {
				cout << "Se ha encontrado la cedula:\n";
				cout << "Cedula : " << BuscadoAVL->Cedula << " Codelec: " << BuscadoAVL->Codelec << " FechaVencimientoCedula: " << BuscadoAVL->FechaVencimientoCedula << " Junta: " << BuscadoAVL->Junta << " Nombre: " << BuscadoAVL->Nombre << " PrimerApellido: " << BuscadoAVL->PrimerApellido << " SegundoApellido: " << BuscadoAVL->SegundoApellido << endl;
			}
			else {
				cout << "No se encontro la persona con la cedula buscada" << endl;
			}

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			B_AVL = tiempo;
			system("pause");

			cout << endl << " === Buscando la cedula en el ArbolBTREE... ===" << endl;

			inicio = time(NULL);

			int posicion;
			Busqueda(cedula, &posicion, rootBTREE);

			fin = time(NULL);
			tiempo = difftime(fin, inicio);
			cout << "Tiempo tardado: " << tiempo << " s" << endl;
			B_BTREE = tiempo;	

			system("pause");
			system("cls");

			break;

		case 4:

			if (cargado == false) {
				cout << "====================== ERORR =====================" << endl;
				cout << "Aun no se han cargado datos, porfavor cargar datos" << endl;
				cout << "====================== ERORR =====================" << endl;
				system("pause");
				system("cls");
				break;
			}

			system("cls");
			cout << "=========== Ha selecionado: 4.Liberar datos ===========" << endl;

			system("pause");
			return 0;

		case 5:

			system("cls");
			cout << "======== Ha selecionado: 5.Reportes de tiempo ========" << endl;

			system("pause");
			return 0;

		default:
			system("cls");
			cout << endl << "Porfavor digite el una de opcion valida" << endl;
			break;
		}
	}

	return 0;
   

}