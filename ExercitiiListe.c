#define _CRT_SECURE_NO_WARNING
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;

//creare structura pentru un nod dintr-o lista dublu inlantuita
typedef struct Nod Nod;

struct Nod {
	Masina masina;
	Nod* next;
	Nod* prev;
};

//creare structura pentru Lista Dubla 
typedef struct ListaDubla ListaDubla;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};

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
	strncpy(m1.model, aux, strlen(aux) + 1);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strncpy(m1.numeSofer, aux, strlen(aux) + 1);

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


int main() {

    FILE* f = fopen("masini.txt","r");
    Masina m1;
    while(!feof(f)) {
        m1 = citireMasinaDinFisier(f);
        afisareMasina(m1);
    }
    return 0;
}