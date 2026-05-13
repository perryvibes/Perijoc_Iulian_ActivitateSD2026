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

typedef struct Nod {
	Masina masina;
	struct Nod* NodSt;
	struct Nod* NodDr;
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
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->masina = masinaNoua;
		nou->NodSt = NULL;
		nou->NodDr = NULL;
		(*radacina) = nou;
	}
	if (*radacina) {
		if ((*radacina)->masina.id > masinaNoua.id) {
			adaugaMasinaInArbore((*radacina)->NodSt, masinaNoua);
		}
		if ((*radacina)->masina.id <= masinaNoua.id) { // in caz ca avem aceeasi valoare preferam sa il punem pe nodurile din dreapta
			adaugaMasinaInArbore((*radacina)->NodDr, masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		adaugaMasinaInArbore(&arbore, citireMasinaDinFisier(fptr));
	}
	return arbore;
}

void afisareMasiniDinArbore(Nod* radacina) {
	// Sunt 3 MODURI de parcurgere.
	// parcurgerea poate fi realizata prin: RSD,SRD,SDR

	// vom folosi parcurgerea SRD
	afisareMasinaArboreSRD(radacina);
}

// 1. PARCURGERE RSD
void afisareMasinaArboreRSD(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, RSD - radacina,stanga,dreapta
		afisareMasina(radacina->masina);
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasinaArboreRSD(radacina->NodDr);
	}
}
// 2. PARCURGERE SRD
void afisareMasinaArboreSRD(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, SRD - stanga,radacina,dreapta
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasina(radacina->masina);
		afisareMasinaArboreRSD(radacina->NodDr);
	}
}
// 3. PARCURGERE SDR
void afisareMasinaArboreSDR(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, SRD - stanga,dreapta,radacina
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasinaArboreRSD(radacina->NodDr);
		afisareMasina(radacina->masina);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina) {
		dezalocareArboreDeMasini((*radacina)->NodSt);
		dezalocareArboreDeMasini((*radacina)->NodDr);
		free((*radacina)->masina.model);
		free((*radacina)->masina.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(/*arborele de masini*/int id) {
	Masina m;

	return m;
}

int determinaNumarNoduri(/*arborele de masini*/) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	return 0;
}

int calculeazaInaltimeArbore(/*arbore de masini*/) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor m`asinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {


	return 0;
}