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
	printf("\nDenumire: %s (id: %d)",magazin->denumire, magazin->id);
	printf("\nLocatie: %s",magazin->locatie);
	printf("\nNumar de angajati: %d",magazin->numar_angajati);
	printf("\nSuprafata: %.2f",magazin->suprafata);
}

void afisareLista(Nod* lista) {
	Nod* p = lista;
	while (p) {
		afisareMagazin(p->info);
		p = p->next;
	}
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

void dezalocareLista(Nod** lista) {
	if ((*lista) == NULL) return;
	Nod* p = (*lista);
	while (p != NULL); {
		Nod* aux = p;
		p = p->next;
		if (aux->info->denumire != NULL) {
			free(aux->info->denumire);
		}
		if (aux->info->locatie != NULL) {
			free(aux->info->locatie);
		}
		if (aux->info != NULL) {
			free(aux->info);
		}
		free(aux);
	}
}

void modificareDenumireMagazin(Nod* lista, char* _denumire, char* _locatie, char* numeNou) {
	Nod* p = lista;
	while (p) {
		if (strcmp(p->info->denumire, _denumire) == 0 && strcmp(p->info->locatie, _locatie) == 0) {
			free(p->info->denumire);
			p->info->denumire = malloc(strlen(numeNou) * sizeof(char) + 1);
			strcpy(p->info->denumire, numeNou);
		}
		p = p->next;
	}
}

int determinareNrMediuAngajatiLocalitate(Nod* lista, char* _locatie) {
	Nod* p = lista;
	int magazine = 0;
	int angajati = 0;
	while (p) {
		if (strcmp(p->info->locatie, _locatie) == 0) {
			angajati += p->info->numar_angajati;
			magazine++;
		}
		p = p->next;
	}
	return angajati / magazine;
}

int main() {
	
	Magazin* m1 = (Magazin*)malloc(sizeof(Magazin));
	m1->id = 11;
	m1->denumire = malloc(strlen("La Nicusor") * sizeof(char) + 1);
	strcpy(m1->denumire, "La Nicusor");
	m1->locatie = malloc(strlen("Nehoiu") * sizeof(char) + 1);
	strcpy(m1->locatie, "Nehoiu");
	m1->numar_angajati = 2;
	m1->suprafata = 33.89;


	Nod* lista = NULL;
	inserareMagazinInLista(&lista, m1);
	afisareLista(lista);
	printf("\n===============================================\n");
	modificareDenumireMagazin(lista, "La Nicusor", "Nehoiu", "La Micutzu");
	afisareLista(lista);
	printf("\n===============================================\n");
	printf("Numar mediu angajati: %d", determinareNrMediuAngajatiLocalitate(lista, "Nehoiu"));


	//dezalocareLista(&lista);
	return 0;
}