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


void adaugaMasinaInArbore(Nod** arbore, Masina masinaNoua) {
	//adauga o noua masina pe care o primim ca parametru in arbore,
	//astfel incat sa respecte princiippile de arbore binar de cautare
	//dupa o anumita cheie pe care o decideti - poate fi ID

	if ((*arbore) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->masina = masinaNoua;
		nou->nodSt = NULL;
		nou->nodDr = NULL;
		(*arbore) = nou;
	}
	else {
		if ((*arbore)->masina.id > masinaNoua.id) {
			adaugaMasinaInArbore(&((*arbore)->nodSt), masinaNoua);
		}
		else if ((*arbore)->masina.id < masinaNoua.id) {
			adaugaMasinaInArbore(&((*arbore)->nodDr), masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* fptr = fopen(numeFisier, "r");
	Nod* arbore = NULL;
	while (!feof(fptr)) {
		adaugaMasinaInArbore(&arbore, citireMasinaDinFisier(fptr));
	}	
	fclose(fptr);
	return arbore;
}

void afisareMasiniDinArbore(Nod* arbore) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere

}

/*
	Modurile de parcurgere sunt:
	RSD - radacina, nod stanga, nod dreapta
	SRD - nod stanga, radacina, nod dreapta
	SDR - nod stanga, nod dreapta, radacina
*/

void afisareOrdineRSD(Nod* arbore) {
	if (arbore) {
		afisareMasina(arbore->masina);
		afisareOrdineRSD(arbore->nodSt);
		afisareOrdineRSD(arbore->nodDr);
	}
}
void afisareOrdineSRD(Nod* arbore) {
	if (arbore) {
		afisareOrdineSRD(arbore->nodSt);
		afisareMasina(arbore->masina);
		afisareOrdineSRD(arbore->nodDr);
	}
}
void afisareOrdineSDR(Nod* arbore) {
	if (arbore) {
		afisareOrdineSDR(arbore->nodSt);
		afisareOrdineSDR(arbore->nodDr);
		afisareMasina(arbore->masina);
	}
}

void dezalocareArboreDeMasini(Nod** arbore) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*arbore) {
		dezalocareArboreDeMasini((*arbore)->nodSt);
		dezalocareArboreDeMasini((*arbore)->nodDr);
		free((*arbore)->nodSt);
		free((*arbore)->nodDr);
		free((*arbore));
		*arbore = NULL;
	}
}

Masina getMasinaByID(Nod* arbore, int id) {
	
	Masina m = {0,0,0,NULL,NULL,0};

	if (arbore) {
		if (arbore->masina.id > id) {
			getMasinaByID(arbore->nodSt, id);
		}
		else if (arbore->masina.id < id) {
			getMasinaByID(arbore->nodDr, id);
		}
		else {
			m = arbore->masina; //SC
		}
	}
	return m;
}

int determinaNumarNoduri(Nod* arbore) {
	//calculeaza numarul total de noduri din arborele binar de cautare
	if (arbore) {
		int noduriSt = determinaNumarNoduri(arbore->nodSt);
		int noduriDr = determinaNumarNoduri(arbore->nodDr);
		return 1 + noduriSt + noduriDr;
	}
	return 0;
}

int calculeazaInaltimeArbore(Nod* arbore) {
	//calculeaza inaltimea arborelui care este data de 
	//lungimea maxima de la radacina pana la cel mai indepartat nod frunza
	if (arbore) {
		int noduriSt = 1 + calculeazaInaltimeArbore(arbore->nodSt);
		int noduriDr = 1 + calculeazaInaltimeArbore(arbore->nodDr);
		return (1+noduriSt > 1+noduriDr ? noduriSt : noduriDr);
	}
	return 0;
}

float calculeazaPretTotal(/*arbore de masini*/) {
	//calculeaza pretul tuturor masinilor din arbore.
	return 0;
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {


	return 0;
}