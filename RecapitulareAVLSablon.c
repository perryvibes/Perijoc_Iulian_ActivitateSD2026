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

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina == NULL) return 0;
	else {
		return 1 + max(calculeazaInaltimeArbore(radacina->NodSt), calculeazaInaltimeArbore(radacina->NodDr));
	}
}

// calculare grad de echilibru
char calculeazaGE(Nod* radacina) {
	return calculeazaInaltimeArbore(radacina->NodSt) - calculeazaInaltimeArbore(radacina->NodDr);
}

// procedura de rotire la stanga
void rotireStanga(Nod** radacina) {
	Nod* aux = (*radacina)->NodDr;
	(*radacina)->NodDr = aux->NodSt;
	aux->NodSt = (*radacina);
	(*radacina) = aux;
}

// procedura de rotire la dreapta

void rotireDreapta(Nod** radacina) {
	Nod* aux = (*radacina)->NodSt;
	(*radacina)->NodSt = aux->NodDr;
	aux->NodDr = (*radacina);
	(*radacina) = aux;
}


void adaugaMasinaInArboreEchilibrat(Nod** radacina, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte principiile de arbore binar de cautare ECHILIBRAT
	//dupa o anumita cheie pe care o decideti - poate fi ID
	Nod* nou = malloc(sizeof(Nod));
	nou->masina = masinaNoua;
	nou->NodDr = NULL;
	nou->NodSt = NULL;

	if (*radacina == NULL) {
		(*radacina) = nou;
	}
	else {
		if ((*radacina)->masina.id < masinaNoua.id) {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->NodDr), masinaNoua);
		}
		else {
			adaugaMasinaInArboreEchilibrat(&((*radacina)->NodSt), masinaNoua);
		}
		int gradEchilibru = calculeazaGE((*radacina));
		if (gradEchilibru == 2) {
			// avem dezechilibru pe partea dreapta
			if (calculeazaGE((*radacina)->NodSt) == 1) {
				rotireDreapta(radacina);
			}
			else {
				rotireStanga(&((*radacina)->NodSt));
				rotireDreapta(radacina);
			}
		}
		else if (gradEchilibru == -2) {
			if (calculeazaGE((*radacina)->NodDr) != -1) {
				rotireDreapta(&((*radacina)->NodDr));
			}
			rotireStanga(radacina);
		}
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

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
}

void parcurgereRSD(Nod* radacina) {
	afisareMasina(radacina->masina);
	parcurgereRSD(radacina->NodSt);
	parcurgereRSD(radacina->NodDr);
}

void parcurgereSRD(Nod* radacina) {
	parcurgereSRD(radacina->NodSt);
	afisareMasina(radacina->masina);
	parcurgereSRD(radacina->NodDr);
}

void parcurgereSDR(Nod* radacina) {
	parcurgereSDR(radacina->NodSt);
	parcurgereSDR(radacina->NodDr);
	afisareMasina(radacina->masina);
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

//Preluati urmatoarele functii din laboratorul precedent.
//Acestea ar trebuie sa functioneze pe noul arbore echilibrat.

Masina getMasinaByID(/*arborele de masini*/int id);

int determinaNumarNoduri(/*arborele de masini*/);

float calculeazaPretTotal(/*arbore de masini*/);

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer);

int main() {


	return 0;
}