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

void afisareMasina(Masina masina) {
	printf("\n\nID: %d", masina.id);
	printf("\nNumar usi: %d", masina.nrUsi);
	printf("\nPret: %.2f", masina.pret);
	printf("\nModel masina: %s", masina.model);
	printf("\nNume sofer: %s", masina.numeSofer);
	printf("\nSeria: %c", masina.serie);
}

Masina InitializareManuala(int _id, int _nrUsi, float _pret, char* _model, char* _numeSofer, unsigned char _serie) { // pentru testing
	Masina m;
	m.id = _id;
	m.nrUsi = _nrUsi;
	m.pret = _pret;
	m.model = malloc((sizeof(char) * strlen(_model)) + 1);
	strcpy_s(m.model, sizeof(char) * strlen(_model)+1, _model);
	m.numeSofer = malloc((sizeof(char) * strlen(_numeSofer)) + 1);
	strcpy_s(m.numeSofer, sizeof(char) * strlen(_numeSofer)+1, _numeSofer);
	m.serie = _serie;
	return m;
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	//afiseaza toate elemente de tip masina din vector
	//prin apelarea functiei afisareMasina()
	for (int i = 0; i < nrMasini; i++) {
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int* nrMasini, Masina masinaNoua) {
	//adauga in vectorul primit o noua masina pe care o primim ca parametru
	//ATENTIE - se modifica numarul de masini din vector;
	Masina** aux = malloc( (sizeof(Masina*) * (*nrMasini)) + 1);
	for (int i = 0; i < *nrMasini; i++) {
		aux[i] = masini[i];
	}
	*aux[(*nrMasini)] = masinaNoua;
	masini = aux; // shallow copy
	*nrMasini++;
}

Masina citireMasinaFisier(FILE* file) {
	//functia citeste o masina dintr-un strceam deja deschis
	//masina citita este returnata;
}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini
	for (int i = 0; i < *nrMasini; i++) {
		free((*vector)[i].model);
		free((*vector)[i].numeSofer);
	}
	free(*vector);
	*vector = NULL;
	*nrMasini = 0;
}

int main() {

	Masina opel = InitializareManuala(1, 3, 5000, "Astra", "Ionescu", 'A');
	Masina dacia = InitializareManuala(5, 3, 11000, "Logan", "Ionescu", 'C');

	int nrMasini = 2;
	Masina* masini = malloc(sizeof(Masina) * nrMasini);
	masini[0] = opel;
	masini[1] = dacia;

	afisareVectorMasini(masini, nrMasini);

	printf("\n----------------------------------------------------\n");

	Masina random = InitializareManuala(6, 5, 4000, "Sportage", "Badescu", 'J');
	adaugaMasinaInVector(&masini, &nrMasini, random);
	afisareVectorMasini(masini, nrMasini);

	return 0;
}