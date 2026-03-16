#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Carte {
	int id;
	char* denumire;
	char* autor;
	float pret;
};
typedef struct Carte Carte;

struct Nod {
	Carte info;
	struct Nod* prev;
	struct Nod* next;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* head;
	Nod* tail;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

void afisareCarte(Carte c) {
	printf("\nId: %d\n", c.id);
	printf("Denumire: %s\n", c.denumire);
	printf("Autor: %s\n", c.autor);
	printf("Pret: %.2f\n", c.pret);
}

Carte initializareCarte(int _id, const char* _den, const char* _autor, float _pret) {
	Carte c;
	c.id = _id;
	c.denumire = malloc(sizeof(char) * sizeof(_den) + 1);
	strcpy_s(c.denumire, sizeof(char) * sizeof(_den) + 1, _den);
	c.autor = malloc(sizeof(char) * sizeof(_autor) + 1);
	strcpy_s(c.autor, sizeof(char) * sizeof(_autor) + 1, _autor);
	c.pret = _pret;
	return c;
}

Carte citireCarteFisier(FILE* f) {
	Carte c;
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, f);
	char* token;
	token = strtok(buffer, delimitator); // de verif flow lin 45-49 deeper
	c.id = atoi(token);
	token = strtok(NULL, delimitator);
	c.denumire = malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(c.denumire, sizeof(char) * strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	c.autor = malloc(sizeof(char) * strlen(token) + 1);
	strcpy_s(c.autor, sizeof(char) * strlen(token) + 1, token);
	token = strtok(NULL, delimitator);
	c.pret = atof(token);
	return c;
}

void adaugareCartiInListaSfarsit(ListaDubla* lista, Carte carte) {
	Nod* aux = (Nod*)malloc(sizeof(Nod));
	aux->info = carte;
	aux->next = NULL;
	aux->prev = lista->tail;
	if (lista->tail != NULL) {
		lista->tail->next = aux;
	}
	else {
		lista->head = aux;
	}
	lista->tail = aux;
	lista->nrNoduri++;
}

void adaugareCartiInListaInceput(ListaDubla* lista, Carte carte) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = carte;
	nou->prev = NULL;
	nou->next = lista->head;
	if (lista->head != NULL) {
		lista->head->prev = nou;
	}
	else {
		lista->tail = nou;
	}
	lista->head = nou;
	lista->nrNoduri++;
}

void afisareListaCartiFirst(ListaDubla* lista) {
	Nod* p = lista->head;
	while (p) {
		afisareCarte(p->info);
		p = p->next;
	}
}

void afisareListaCartiEnd(ListaDubla* lista) {
	Nod* p = lista->tail;
	while (p) {
		afisareCarte(p->info);
		p = p->prev;
	}
}

void dezalocare1(Carte x) {
	printf("\nDEZALOCARE\n");
	if (x.autor != NULL) {
		free(x.autor);
	}
	else if (x.denumire != NULL)
	{
		free(x.denumire);
	}
	else {
		x.denumire = NULL;
		x.autor = NULL;
	}
}


int main() {

	// Carte c1 = initializareCarte(1,"Shrek","Anonim",29.33);
	// afisareCarte(c1);
	// dezalocare1(c1);


	ListaDubla listaCarti;
	FILE* f = fopen("carti.txt", "r");
	while (!feof(f)) {
		adaugareCartiInListaInceput(&listaCarti, citireCarteFisier(f));
	}
	afisareListaCartiFirst(&listaCarti);
	// Carte c = citireCarteFisier(f);
	// afisareCarte(c);

	fclose(f);

	return 0;
}