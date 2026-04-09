#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Farmacie Farmacie;
struct Farmacie {
	char* denumire;
	float suprafata; //m2
	unsigned char nrAngajati;
	char* adresa;
};

typedef struct Nod Nod;
struct Nod {
	Farmacie farmacie;
	Nod* prev;
	Nod* next;
};

typedef struct ListaDubla ListaDubla;
struct ListaDubla {
	Nod* head;
	Nod* tail;
	int nrNoduri;
};

void initializareListaNull(ListaDubla* lista) {
	lista->head = NULL;
	lista->tail = NULL;
	lista->nrNoduri = 0;
}

Farmacie initializareFarmacie(const char* _denumire, float _suprafata, unsigned char _nrAngajati, const char* _adresa) {
	Farmacie init;
	init.denumire = malloc(strlen(_denumire) * sizeof(char) + 1);
	strcpy(init.denumire, _denumire);
	init.adresa = malloc(strlen(_adresa) * sizeof(char) + 1);
	strcpy(init.adresa, _adresa);
	init.suprafata = _suprafata;
	init.nrAngajati = _nrAngajati;
	return init;
}

void afisareFarmacie(Farmacie info) {
	printf("\nDenumire: %s", info.denumire);
	printf("\nAdresa: %s", info.adresa);
	printf("\nNumar angajati: %d", info.nrAngajati);
	printf("\nSuprafata: %.2f", info.suprafata);
	printf("\n\n");
}

void afisareListaDubla(ListaDubla lista) {
	if (lista.head != NULL) {
		Nod* p = lista.head;
		while (p) {
			afisareFarmacie(p->farmacie);
			p = p->next;
		}
	}
	else {
		printf("\nLista este goala!\n");
	}
}

void adaugaFarmacieInLista(ListaDubla* lista, Farmacie nouaFarmacie) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->farmacie = nouaFarmacie; // SC
		nou->next = NULL; //adaugam la sfarsit
		nou->prev = lista->tail;
		if (lista->tail != NULL) {
			lista->tail->next = nou;
		}
		else {
			lista->head = nou;
		}
		lista->tail = nou;
		lista->nrNoduri++;
}

int DeterminareNrFarmaciiCuOAnumitaSuprafata(ListaDubla lista, float _suprafataCeruta) {
	int counter = 0;
	Nod* p = lista.head;
	while (p) {
		if (p->farmacie.suprafata < _suprafataCeruta) {
			counter++;
		}
		p = p->next;
	}
	return counter;
}

//void copiereFarmacii(ListaDubla lista, const char* lantComercial, Farmacie* vector) {
//
//	int nrFarmacii = 0;
//	Nod* p = lista.head;
//	while (p) {
//		if (!strcmp(p->farmacie.denumire, lantComercial)) {
//			nrFarmacii++;
//		}
//		p = p->next;
//	}
//	vector = (Farmacie*)malloc(sizeof(Farmacie) * nrFarmacii);
//	for (int i = 0; i < nrFarmacii; i++) {
//		p = lista.head;
//		while (p) {
//			if (!strcmp(p->farmacie.denumire, lantComercial)) {
//				vector[i] = p->farmacie;
//				vector[i].adresa = malloc(strlen(p->farmacie.adresa) + 1);
//				strcpy(vector[i].adresa, p->farmacie.adresa);
//				vector[i].denumire = malloc(strlen(p->farmacie.denumire) + 1);
//				strcpy(vector[i].denumire, p->farmacie.denumire);
//				i++;
//			}
//			p = p->next;
//		}
//	}
//}

void stergereFarmacie(ListaDubla* lista, unsigned char _angajati) {
	if (lista->nrNoduri == 0) return;
	Nod* p = lista->head;
	while (p) {
		if (p->farmacie.nrAngajati > _angajati) {
			printf("\nTRUE");
			if (p->prev == NULL) { // atunci e primul nod
				lista->head = p->next;
				p->next->prev = NULL;
			}
			else {
				p->prev->next = p->next;
			}
			if (p->next == NULL) { // atunci e ultimul nod
				lista->tail = p->prev;
				p->prev->next = NULL;
			}
			else {
				p->next->prev = p->prev;
			}
			if (p->farmacie.adresa != NULL) {
				free(p->farmacie.adresa);
			}
			if (p->farmacie.denumire != NULL) {
				free(p->farmacie.denumire);
			}
			free(p);
			lista->nrNoduri--;
			p=p->next;
		}
		p = p->next;
	}
	//// am ajuns pe nodul pe care vrem sa-l stergem...
	//if (p->prev == NULL) { // atunci e primul nod
	//	lista->head = p->next;
	//	p->next->prev = NULL;
	//}
	//else {
	//	p->prev->next = p->next;
	//}
	//if (p->next == NULL) { // atunci e ultimul nod
	//	lista->tail = p->prev;
	//	p->prev->next = NULL;
	//}
	//else {
	//	p->next->prev = p->prev;
	//}
	//if (p->farmacie.adresa != NULL) {
	//	free(p->farmacie.adresa);
	//}
	//if (p->farmacie.denumire != NULL) {
	//	free(p->farmacie.denumire);
	//}
	//free(p);
	//lista->nrNoduri--;
}

int main() {

	// ex1
	Farmacie f1 = initializareFarmacie("Farmacia Unirii",325,15,"Bulevardul Piata Unirii");
	Farmacie f2 = initializareFarmacie("Farmacia Tei",35.7,5,"Bulevardul Timisoara");
	Farmacie f3 = initializareFarmacie("Farmacia Dona",89.5,4,"Strada Margareta");
	Farmacie f4 = initializareFarmacie("Farmacia Catena",29.8,20,"Bulevardul Condei");
	Farmacie f5 = initializareFarmacie("Farmacia Hepytes",100.3,5,"Strada Iuliu Maniu");


	Farmacie v[5] = { f1,f2,f3,f4,f5 };
	ListaDubla lista;
	initializareListaNull(&lista);
	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
		adaugaFarmacieInLista(&lista, v[i]);
	}
	afisareListaDubla(lista);
	//afisareFarmacie(f1);

	printf("\n================================================\n");

	// ex2
	printf("Numar farmacii cu suprafete mai mici decat cea ceruta: %d", DeterminareNrFarmaciiCuOAnumitaSuprafata(lista, 65.1));

	printf("\n================================================\n");
	// ex3

	//Farmacie v;
	//copiereFarmacii(lista, "Tei", &v);
	//for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
	//	afisareFarmacie(v[i]);
	//}

	printf("\n================================================\n");
	// ex4
	stergereFarmacie(&lista, 10);
	afisareListaDubla(lista);


	return 0;
}