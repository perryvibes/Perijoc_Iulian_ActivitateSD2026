#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-un arbore binar de cautare
typedef struct Nod {
	Masina masina;
	struct Nod* nodSt;
	struct Nod* nodDr;
} Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

char calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina == NULL) return 0;
	else {
		return 1 + max(calculeazaInaltimeArbore(radacina->nodSt), calculeazaInaltimeArbore(radacina->nodDr));
	}
}

//ALTE FUNCTII NECESARE:
// - aici veti adauga noile functii de care aveti nevoie.

char calculareGE(Nod* radacina) {
	if (radacina == NULL) return 0;
	else {
		return calculeazaInaltimeArbore(radacina->nodSt) - calculeazaInaltimeArbore(radacina->nodDr);
	}
}

void rotireStanga(Nod** radacina) {
	if (*radacina == NULL) return;
	else {
		Nod* aux = (*radacina)->nodDr;
		(*radacina)->nodDr = aux->nodSt;
		aux->nodSt = (*radacina);
		(*radacina) = aux;
	}
}
void rotireDreapta(Nod** radacina) {
	if (*radacina == NULL) return;
	else {
		Nod* aux = (*radacina)->nodSt;
		(*radacina)->nodSt = aux->nodDr;
		aux->nodDr = (*radacina);
		(*radacina) = aux;
	}
}

void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
	//dupa o anumita cheie pe care o decideti - poate fi ID
	Nod* nou = malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->nodSt = NULL;
	nou->nodDr = NULL;
	if (*radacina) {
		if ((*radacina)->masina.id > masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->nodSt), masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->nodDr), masinaNoua);
		}
		int gradEchilibru = calculareGE(*radacina);
		if (gradEchilibru == 2) {
			if (calculareGE	((*radacina)->nodSt) != 1) {
				rotireStanga(&((*radacina)->nodSt));
			}
			rotireDreapta(radacina);
		}
		else if (gradEchilibru == -2) {
			if (calculareGE((*radacina)->nodDr) != -1) {
				rotireDreapta(&((*radacina)->nodDr));
			}
			rotireStanga(radacina);
		}
	}
	else {
		(*radacina) = nou;
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* fptr = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(fptr)) {
		adaugaMasinaInArboreEchilibrat(&radacina, citireMasinaDinFisier(fptr));
	}
	fclose(fptr);
	return radacina;
}

void afisareMasiniDinArbore(/*arbore de masini*/) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void dezalocareArboreDeMasini(/*arbore de masini*/) {
	//sunt dezalocate toate masinile si arborele de elemente
}

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {


	return 0;
}