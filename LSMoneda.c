#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char* tara;
	int val_nominala;
	float greutate;
	int anEmitere;
} Moneda;

typedef struct Nod {
	Moneda info;
	struct Nod* next;
} Nod;

void adaugareMonedaInLista(Nod** lista, Moneda _moneda) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = _moneda;
	nou->next = NULL;
	if (*lista == NULL) {
		*lista = nou;
	}
	else {
		Nod* p = *lista;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

void afisareMoneda(Moneda _m) {
	printf("\nTara: %s\n", _m.tara);
	printf("Valoare nominala: %d\n", _m.val_nominala);
	printf("Greutate: %.2f\n", _m.greutate);
	printf("An Emitere: %d\n", _m.anEmitere);
}

void afisareLista(Nod* lista) {
	Nod* p = lista;
	while (p) {
		afisareMoneda(p->info);
		printf("=======================\n");
		p = p->next;
	}
}

Moneda greutateMaxima(Nod* lista) {
	float max = 0;
	Moneda m = { NULL,0,0.0,0 };
	Nod* p = lista;
	Nod* nodMax = NULL;
	while (p) {
		if (p->info.greutate > max) {
			max = p->info.greutate;
			nodMax = p;
		}
		p = p->next;
	}
	if (nodMax != NULL) {
		m = nodMax->info;
		m.tara = malloc(sizeof(char) * (strlen(nodMax->info.tara) + 1));
		strcpy(m.tara, nodMax->info.tara);
	}
	return m;
}

void stergereMoneda(Nod** lista, float _greutate) {
	// TO DO!!
	if ((*lista)->info.greutate == _greutate) {
		Nod* temp = (*lista);
		(*lista) = (*lista)->next;
		free(temp);
	}
	Nod* p = *lista;
	while (p->next != NULL && p->next->info.greutate != _greutate) {
		p = p->next;
	}
	if (p->next != NULL) {
		Nod* temp = p->next;
		p->next = temp->next;
		free(temp);
	}
}

void dezalocareHeap(Nod** lista) {
	Nod* p = *lista;
	while (p) {
		Nod* temp = p;
		p = p->next;
		free(temp);
	}
	*lista = NULL;
}

int main() {

	Moneda dolar = { "america",1,25,1978 };
	Moneda ron = { "romania",1,50,1977 };
	Moneda chf = { "elvetia",2,20,1924 };
	Moneda eur = { "spania",1,30,1900 };
	Moneda lira = { "marea britanie",4,45,1999 };
	
	Nod* lista = NULL;
	adaugareMonedaInLista(&lista, dolar);
	adaugareMonedaInLista(&lista, ron);
	adaugareMonedaInLista(&lista, chf);
	adaugareMonedaInLista(&lista, eur);
	adaugareMonedaInLista(&lista, lira);
	afisareLista(lista);

	printf("\n=================\n");
	stergereMoneda(&lista, 30);
	afisareLista(lista);
	
	
	printf("\n=================\n");
	Moneda max = greutateMaxima(lista);
	afisareMoneda(max);
	free(max.tara);

	dezalocareHeap(&lista);
	return 0;
}