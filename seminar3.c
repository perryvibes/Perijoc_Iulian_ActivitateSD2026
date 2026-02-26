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
	printf("\n\nId: %d", masina.id);
	printf("\nNr Usi: %d", masina.nrUsi);
	printf("\nPret: %.2f", masina.pret);
	printf("\nModel: %s", masina.model);
	printf("\nNume Sofer: %s", masina.numeSofer);
	printf("\nSerie: %c", masina.serie);
}

Masina InitializareMasina(int _id, int _nrUsi, float _pret, char* _model, char* _numeSofer, unsigned char _serie) { // testare
	
	Masina m;
	m.id = _id;
	m.nrUsi = _nrUsi;
	m.pret = _pret;
	m.model = malloc((sizeof(char) * strlen(_model)) + 1);
	strcpy_s(m.model, (sizeof(char)*strlen(_model))+1, _model);
	m.numeSofer = malloc((sizeof(char) * strlen(_numeSofer)) + 1);
	strcpy_s(m.numeSofer, (sizeof(char)*strlen(_numeSofer))+1, _numeSofer);
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

	Masina* copie = malloc(sizeof(Masina) * ((*nrMasini) + 1));
	for (int i = 0; i < *nrMasini; i++) {
		copie[i] = (*masini)[i];
	}
	copie[*nrMasini] = masinaNoua;
	(*nrMasini)++;
	if ((*masini) != NULL) {
		free((*masini));
	}
	(*masini) = copie;
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
}

int main() {

	Masina m1 = InitializareMasina(1, 3, 5000, "Astra", "Ionescu", 'A');
	Masina m2 = InitializareMasina(2, 5, 8000, "Mokka", "Vasilescu", 'S');
	Masina m3 = InitializareMasina(3, 4, 9000, "Passat", "Gigel", 'I');
	
	Masina* masini;
	int nrMasini = 2;
	masini = malloc(sizeof(Masina) * nrMasini);
	masini[0] = m1;
	masini[1] = m2;
	afisareMasina(masini[0]);
	afisareMasina(masini[1]);

	printf("\n---------------------------------------------------");

	adaugaMasinaInVector(&masini, &nrMasini, m3);
	afisareMasina(masini[2]);


	return 0;
}