#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Zbor {
	int indicativ;
	char* companie;
	float durataOre;
	char* destinatie;
	int nrScaune; // numar de scaune in avion
} Zbor;

typedef struct Nod {
	Zbor zbor;
	struct Nod* nodSt;
	struct Nod* nodDr;
} Nod;

int calculeazaInaltimeArbore(Nod* arbore) {
	if (arbore) {
		return 1 + max(calculeazaInaltimeArbore(arbore->nodSt), calculeazaInaltimeArbore(arbore->nodDr));
	}
	else {
		return 0;
	}
}

int calculeazaGE(Nod* arbore) {
	if (arbore) {
		return calculeazaInaltimeArbore(arbore->nodSt) - calculeazaInaltimeArbore(arbore->nodDr);
	}
}

void afisareZbor(Zbor zbor) {
	printf("\nIndicativ zbor: %d", zbor.indicativ);
	printf("\nCompanie zbor: %s", zbor.companie);
	printf("\nDurata ore zbor: %.2f", zbor.durataOre);
	printf("\nDestinatie zbor: %s", zbor.destinatie);
	printf("\nNumar de scaune zbor: %d\n", zbor.nrScaune);
}

Zbor citireZborFisier(FILE* fptr) {
	Zbor zbor;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, fptr);
	char* token = strtok(buffer, sep);
	zbor.indicativ = atoi(token);
	token = strtok(NULL, sep);
	zbor.companie = malloc(strlen(token) + 1);
	strcpy(zbor.companie, token);
	token = strtok(NULL, sep);
	zbor.durataOre = atof(token);
	token = strtok(NULL, sep);
	zbor.destinatie = malloc(strlen(token) + 1);
	strcpy(zbor.destinatie, token);
	token = strtok(NULL, sep);
	zbor.nrScaune = atoi(token);
	return zbor;
}

void rotireStanga(Nod** arbore) {
	if (*arbore) {
		Nod* aux = (*arbore)->nodDr;
		(*arbore)->nodDr = aux->nodSt;
		aux->nodSt = (*arbore);
		(*arbore) = aux;
	}
}
void rotireDreapta(Nod** arbore) {
	if (*arbore) {
		Nod* aux = (*arbore)->nodSt;
		(*arbore)->nodSt = aux->nodDr;
		aux->nodDr = (*arbore);
		(*arbore) = aux;
	}
}

void inserareZborArbore(Nod** arbore, Zbor zbor) {
	// indicativ
	if (*arbore == NULL) {
		Nod* aux = malloc(sizeof(Nod));
		aux->zbor = zbor;
		aux->nodSt = NULL;
		aux->nodDr = NULL;
		(*arbore) = aux;
	} else {
		if ((*arbore)->zbor.indicativ > zbor.indicativ) {
			inserareZborArbore(&((*arbore)->nodSt), zbor);
		}
		else if ((*arbore)->zbor.indicativ < zbor.indicativ) {
			inserareZborArbore(&((*arbore)->nodDr), zbor);
		}
		if (calculeazaGE(*arbore) == 2) {
			if (calculeazaGE((*arbore)->nodSt) != 1) {
				rotireStanga(&((*arbore)->nodSt));
			}
			rotireDreapta(arbore);
		} else if (calculeazaGE(*arbore) == -2) {
			if (calculeazaGE((*arbore)->nodDr) != -1) {
				rotireDreapta(&((*arbore)->nodDr));
			}
			rotireStanga(arbore);
		}
	}
}

Nod* citireArboreFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		inserareZborArbore(&arbore, citireZborFisier(fptr));
	}
	fclose(fptr);
	return arbore;
}

void afisareArbore(Nod* arbore) { // INORDINE SRD
	if (arbore) {
		afisareArbore(arbore->nodSt);
		afisareZbor(arbore->zbor);
		afisareArbore(arbore->nodDr);
	}
 }

// TO DO 5,6,7,8

int main() {

	Nod* arbore = citireArboreFisier("zboruri.txt");
	afisareArbore(arbore);


	return 0;
}