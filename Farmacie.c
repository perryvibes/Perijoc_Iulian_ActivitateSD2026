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
};

void initializareListaNull(ListaDubla* lista) {
	lista->head = NULL;
	lista->tail = NULL;
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
	printf("\nNumar angajati: %c", info.nrAngajati);
	printf("\nSuprafata: %.2f", info.suprafata);
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
}

int main() {

	Farmacie f1 = initializareFarmacie("Farmacia Unirii",89.5,5,"Bulevardul Piata Unirii");
	Farmacie f2 = initializareFarmacie("Farmacia Unirii",89.5,5,"Bulevardul Piata Unirii");
	Farmacie f3 = initializareFarmacie("Farmacia Unirii",89.5,5,"Bulevardul Piata Unirii");
	Farmacie f4 = initializareFarmacie("Farmacia Unirii",89.5,5,"Bulevardul Piata Unirii");
	Farmacie f5 = initializareFarmacie("Farmacia Unirii",89.5,5,"Bulevardul Piata Unirii");


	Farmacie v[5] = { f1,f2,f3,f4,f5 };
	ListaDubla lista;
	initializareListaNull(&lista);
	for (int i = 0; i < sizeof(v) / sizeof(v[0]); i++) {
		adaugaFarmacieInLista(&lista, v[i]);
	}
	afisareListaDubla(lista);
	//afisareFarmacie(f1);



	return 0;
}