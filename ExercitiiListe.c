#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char* denumire;
	char* autor;
	float pret;
} Carte;

typedef struct {
	Carte info;
	struct Nod* prev;
	struct Nod* next;
} Nod;

typedef struct {
	Nod* head;
	Nod* tail;
	int nrNoduri;
} ListaDubla;

void afisareCarte(Carte c) {
	printf("\nId: %d\n", c.id);
	printf("Denumire: %s\n", c.denumire);
	printf("Autor: %s\n", c.autor);
	printf("Pret: %.2f\n", c.pret);
}

Carte initializareCarte(int _id, const char* _den, const char* _autor, float _pret) {
	Carte c;
	c.id = _id;
	c.denumire = malloc(sizeof(char)*sizeof(_den)+1);
	strncpy(c.denumire, _den, sizeof(char)*sizeof(_den)+1);
	c.autor = malloc(sizeof(char)*sizeof(_autor)+1);
	strncpy(c.autor, _autor, sizeof(char)*sizeof(_autor)+1);
	c.pret = _pret;
	return c;
}

Carte citireCarteFisier(FILE* f) {
	Carte c;
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer,100,f);
	char* token;
	token = strtok(buffer,delimitator);
	c.id = atoi(token);
	token = strtok(NULL,delimitator);
	c.denumire = malloc(sizeof(char)*strlen(token)+1);
	strncpy(c.denumire, token, sizeof(char)*strlen(token)+1);
	token = strtok(NULL, delimitator);
	c.autor = malloc(sizeof(char)*strlen(token)+1);
	strncpy(c.autor, token, sizeof(char)*strlen(token)+1);
	token = strtok(NULL,delimitator);
	c.pret = atof(token);
	return c;
}

void dezalocare(Carte x) {
	printf("\nDEZALOCARE\n");
	if (x.autor != NULL) {
		free(x.autor);
	} else if (x.denumire != NULL)
	{
		free(x.denumire);
	} else {
		x.denumire = NULL;
		x.autor = NULL;
	}
}


int main() {

	// Carte c1 = initializareCarte(1,"Shrek","Anonim",29.33);
	// afisareCarte(c1);
	// dezalocare(c1);

	FILE* f = fopen("carti.txt", "r");
	while(!feof(f)) {
		afisareCarte(citireCarteFisier(f));
	}
	// Carte c = citireCarteFisier(f);
	// afisareCarte(c);


    return 0;
}