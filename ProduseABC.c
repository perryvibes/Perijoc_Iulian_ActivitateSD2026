#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produs {
	int codBare;
	char* denumire;
	float pret;
	char* categorie;
	int stoc; // stocul produsului

} Produs;

// arboreABC
typedef struct Nod {
	Produs produs;
	struct Nod* nodSt;
	struct Nod* nodDr;
}Nod;

void afisareProdus(Produs p) {
	printf("\n CodBare produs: %d", p.codBare);
	printf("\n Denumire produs: %s", p.denumire);
	printf("\n Pret produs: %.2f", p.pret);
	printf("\n Categorie produs: %s", p.categorie);
	printf("\n Stoc produs: %d\n", p.stoc);
}

Produs citireProdusFisier(FILE* fptr) {
	Produs produs;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, fptr);
	char* token = strtok(buffer, sep);
	produs.codBare = atoi(token);
	token = strtok(NULL, sep);
	produs.denumire = malloc(strlen(token) + 1);
	strcpy(produs.denumire, token);
	token = strtok(NULL, sep);
	produs.pret = atof(token);
	token = strtok(NULL, sep);
	produs.categorie = malloc(strlen(token) + 1);
	strcpy(produs.categorie, token);
	token = strtok(NULL, sep);
	produs.stoc = atoi(token);
	return produs;
}

void inserareProdusArbore(Nod** radacina, Produs produsNou) {
	// ne bazam pe codul de bare
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->produs = produsNou;
		nou->nodSt = NULL;
		nou->nodDr = NULL;
		(*radacina) = nou;
	}
	else {
		if ((*radacina)->produs.codBare > produsNou.codBare) {
			inserareProdusArbore(&((*radacina)->nodSt), produsNou);
		}
		else {
			inserareProdusArbore(&((*radacina)->nodDr), produsNou);
		}
	}
}

Nod* citireArboreFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		inserareProdusArbore(&arbore, citireProdusFisier(fptr));
	}
	fclose(fptr);
	return arbore;
}

void afisareArbore(Nod* radacina) //preordine RSD
{
	if (radacina) {
		afisareProdus(radacina->produs);
		afisareArbore(radacina->nodSt);
		afisareArbore(radacina->nodDr);
	}
}

float pretTotalCategorie(Nod* arbore, const char* categorie) {
	if (arbore) {
		// GRIJA cum pozitionezi etapele!!!!!
		// sum, si recursivitate inainte de verificare!!
		float sum = 0;
		float st = pretTotalCategorie(arbore->nodSt, categorie);
		float dr = pretTotalCategorie(arbore->nodDr, categorie);
		if (strcmp(arbore->produs.categorie, categorie) == 0) {
			sum += arbore->produs.pret;
		}
		return sum + st + dr;
	}
	return 0;
}

void dezalocare(Nod** radacina) {
	if (*radacina) {
		dezalocare(&((*radacina)->nodSt));
		dezalocare(&((*radacina)->nodDr));
		free((*radacina)->produs.categorie);
		free((*radacina)->produs.denumire);
		free(*radacina);
	}
}

int main() {

	Nod* arbore = citireArboreFisier("produse.txt");
	afisareArbore(arbore);
	printf("\n========\n");
	printf("Pret total categorie: %.2f", pretTotalCategorie(arbore, "fructe"));
	printf("\n========\n");



	dezalocare(&arbore);
	return 0;
}