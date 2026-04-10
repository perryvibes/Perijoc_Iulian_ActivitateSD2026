#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Magazin Magazin;
struct Magazin {
	int id;
	char* denumire;
	char* locatie;
	float suprafata;
	int numar_angajati;
};

typedef struct Nod Nod;
struct Nod {
	Magazin* info;
	Nod* next;
};

void afisareMagazin(Magazin* magazin) {
	printf("Denumire: %s (id: %d)",magazin->denumire, magazin->id);
	printf("Locatie: %s",magazin->locatie);
	printf("Numar de angajati: %d",magazin->numar_angajati);
	printf("Suprafata: %.2f",magazin->suprafata);
}

void inserareMagazinInLista(Nod** lista, Magazin* magazin) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = magazin;
	nou->next = NULL;
	if ((*lista) == NULL) {
		(*lista) = nou;
	}
	else {
		Nod* p = (*lista);
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

Magazin* citireMagazinFisier(const char* numeFisier) {
	Magazin* magazin = (Magazin*)malloc(sizeof(Magazin));
	FILE* fptr = fopen(numeFisier, "r");
	char buffer[150];
	char delimitator[3] = ",\n";
	fgets(buffer, 150, fptr);
	char* token = strtok(buffer, delimitator);
	magazin->id = atoi(token);
	magazin->numar_angajati = atoi(strtok(NULL, delimitator));
	magazin->suprafata = atof(strtok(NULL, delimitator));
	token = strtok(NULL, delimitator);
	magazin->denumire = malloc(sizeof(char) * strlen(token) + 1);
	strcpy(magazin->denumire, token);
	token = strtok(NULL, delimitator);
	magazin->locatie = malloc(sizeof(char) * strlen(token) + 1);
	strcpy(magazin->locatie, token);
	token = strtok(NULL, delimitator);
	
	fclose(fptr);
	return magazin;

}


int main() {


	return 0;
}