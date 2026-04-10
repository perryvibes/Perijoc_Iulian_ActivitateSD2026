//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//typedef struct Farmacie Farmacie;
//struct Farmacie {
//	char* denumire;
//	float suprafata; //m2
//	unsigned char nrAngajati;
//	char* adresa;
//};
//
//typedef struct Nod Nod;
//struct Nod {
//	Farmacie farmacie;
//	Nod* prev;
//	Nod* next;
//};
//
//typedef struct ListaDubla ListaDubla;
//struct ListaDubla {
//	Nod* head;
//	Nod* tail;
//	int nrNoduri;
//};
//
//void initializareListaNull(ListaDubla* lista) {
//	lista->head = NULL;
//	lista->tail = NULL;
//	lista->nrNoduri = 0;
//}
//
//Farmacie initializareFarmacie(const char* _denumire, float _suprafata, unsigned char _nrAngajati, const char* _adresa) {
//	Farmacie init;
//	init.denumire = malloc(strlen(_denumire) * sizeof(char) + 1);
//	strcpy(init.denumire, _denumire);
//	init.adresa = malloc(strlen(_adresa) * sizeof(char) + 1);
//	strcpy(init.adresa, _adresa);
//	init.suprafata = _suprafata;
//	init.nrAngajati = _nrAngajati;
//	return init;
//}
//
//void afisareFarmacie(Farmacie info) {
//	printf("\nDenumire: %s", info.denumire);
//	printf("\nAdresa: %s", info.adresa);
//	printf("\nNumar angajati: %d", info.nrAngajati);
//	printf("\nSuprafata: %.2f", info.suprafata);
//	printf("\n\n");
//}
//
//void afisareListaDubla(ListaDubla lista) {
//	if (lista.head != NULL) {
//		Nod* p = lista.head;
//		while (p) {
//			afisareFarmacie(p->farmacie);
//			p = p->next;
//		}
//	}
//	else {
//		printf("\nLista este goala!\n");
//	}
//}
//
//void adaugaFarmacieInLista(ListaDubla* lista, Farmacie nouaFarmacie) {
//		Nod* nou = (Nod*)malloc(sizeof(Nod));
//		nou->farmacie = nouaFarmacie; // SC
//		nou->next = NULL; //adaugam la sfarsit
//		nou->prev = lista->tail;
//		if (lista->tail != NULL) {
//			lista->tail->next = nou;
//		}
//		else {
//			lista->head = nou;
//		}
//		lista->tail = nou;
//		lista->nrNoduri++;
//}
//
//int DeterminareNrFarmaciiCuOAnumitaSuprafata(ListaDubla lista, float _suprafataCeruta) {
//	int counter = 0;
//	Nod* p = lista.head;
//	while (p) {
//		if (p->farmacie.suprafata < _suprafataCeruta) {
//			counter++;
//		}
//		p = p->next;
//	}
//	return counter;
//}
//
//Farmacie* copiereFarmaciiInVector(ListaDubla* lista, const char* lantComercial, int* dimVector) {
//	*dimVector = 0;
//	int counter = 0;
//	Nod* p = lista->head;
//	while (p) {
//		if (strcmp(p->farmacie.denumire, lantComercial) == 0) {
//			counter++;
//		}
//		p = p->next;
//	}
//	
//	Farmacie* vectorFarmacii = NULL;
//	if (counter > 0) {
//		vectorFarmacii = (Farmacie*)malloc(sizeof(Farmacie) * counter);
//		*dimVector = counter;
//		p = lista->head;
//		int i = 0;
//		while (p) {
//			if (strcmp(p->farmacie.denumire, lantComercial) == 0) {
//				vectorFarmacii[i] = p->farmacie;
//				vectorFarmacii[i].denumire = malloc(sizeof(char) * strlen(p->farmacie.denumire) + 1);
//				strcpy(vectorFarmacii[i].denumire, p->farmacie.denumire);
//				vectorFarmacii[i].adresa = malloc(sizeof(char) * strlen(p->farmacie.adresa) + 1);
//				strcpy(vectorFarmacii[i].adresa, p->farmacie.adresa);
//				i++;
//			}
//			p = p->next;
//		}
//	}
//	return vectorFarmacii;
//}
//
//void stergereFarmacii_First(ListaDubla* lista, unsigned char _angajati) {
//	Nod* p = lista->head;
//	while (p) {
//		Nod* temp = p->next;
//		if (p->farmacie.nrAngajati > _angajati) {
//			if (p->prev == NULL) {
//				lista->head = p->next;
//				p->next->prev = NULL;
//			}
//			else {
//				p->prev->next = p->next;
//			}
//			if (p->next == NULL) {
//				lista->tail = p->prev;
//				p->prev->next = NULL;
//			}
//			else {
//				p->next->prev = p->prev;
//			}
//			if (p->farmacie.adresa != NULL) {
//				free(p->farmacie.adresa);
//			}
//			if (p->farmacie.denumire != NULL) {
//				free(p->farmacie.denumire);
//			}
//			free(p);
//			lista->nrNoduri--;
//		}
//		p = temp;
//	}
//}
//
//void stergereFarmacii_Second(ListaDubla* lista, unsigned char _angajati) {
//	if (lista == NULL) return;
//	Nod** pp = &(lista->head);
//	while ((*pp) != NULL) {
//		Nod* temp = (*pp);
//		if (temp->farmacie.nrAngajati > _angajati) {
//			(*pp) = temp->next;
//			if (temp->prev == NULL) {
//				lista->head = temp->next;
//				temp->next->prev = NULL;
//			}
//			else {
//				temp->prev->next = temp->next;
//			}
//			if (temp->next == NULL) {
//				lista->tail = temp->prev;
//				temp->prev->next = NULL;
//			}
//			else {
//				temp->next->prev = temp->prev;
//			}
//			if (temp->farmacie.denumire != NULL) {
//				free(temp->farmacie.denumire);
//			}
//			if (temp->farmacie.adresa != NULL) {
//				free(temp->farmacie.adresa);
//			}
//			free(temp);
//			lista->nrNoduri--;
//		}
//		else {
//			pp = &(temp->next);
//		}
//	}
//}
//
//void dezalocareLista(ListaDubla* lista) {
//	Nod* p = lista->head;
//	while (p) {
//		Nod* aux = p;
//		p = p->next;
//		if (aux->farmacie.adresa != NULL) {
//			free(aux->farmacie.adresa);
//		}
//		if (aux->farmacie.denumire != NULL) {
//			free(aux->farmacie.denumire);
//		}
//		free(aux);
//	}
//	lista->head = NULL;
//	lista->tail = NULL;
//	lista->nrNoduri = 0;
//}
//
//int main() {
//
//	// ex1
//	Farmacie f1 = initializareFarmacie("Farmacia Unirii",325,15,"Bulevardul Piata Unirii");
//	Farmacie f2 = initializareFarmacie("TEI",35.7,5,"Bulevardul Timisoara");
//	Farmacie f3 = initializareFarmacie("Farmacia Dona",89.5,4,"Strada Margareta");
//	Farmacie f4 = initializareFarmacie("TEI",29.8,9,"Bulevardul Condei");
//	Farmacie f5 = initializareFarmacie("Farmacia Hepytes",100.3,30,"Strada Iuliu Maniu");
//
//
//	Farmacie v[5] = { f1,f2,f3,f4,f5 };
//	ListaDubla lista;
//	initializareListaNull(&lista);
//	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
//		adaugaFarmacieInLista(&lista, v[i]);
//	}
//	afisareListaDubla(lista);
//	//afisareFarmacie(f1);
//
//	printf("\n================================================\n");
//
//	// ex2
//	printf("Numar farmacii cu suprafete mai mici decat cea ceruta: %d", DeterminareNrFarmaciiCuOAnumitaSuprafata(lista, 65.1));
//
//	printf("\n================================================\n");
//	// ex3
//
//	int dimV;
//	Farmacie* FarmaciiCopiate = copiereFarmaciiInVector(&lista, "TEI", &dimV);
//	for (int i = 0; i < dimV; i++) {
//		afisareFarmacie(FarmaciiCopiate[i]);
//	}
//	//dezalocare vector
//	for (int i = 0; i < dimV; i++) {
//		if (FarmaciiCopiate[i].adresa != NULL) {
//			free(FarmaciiCopiate[i].adresa);
//		}
//		if (FarmaciiCopiate[i].denumire != NULL) {
//			free(FarmaciiCopiate[i].denumire);
//		}
//	}
//	free(FarmaciiCopiate);
//
//	printf("\n================================================\n");
//	// ex4
//	//stergereFarmacii_First(&lista, 10);
//	stergereFarmacii_Second(&lista, 10);
//
//	afisareListaDubla(lista);
//
//	// !!! Contine memory leaks!
//	return 0;
//}