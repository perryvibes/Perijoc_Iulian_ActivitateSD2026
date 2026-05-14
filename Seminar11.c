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

//1. 
// structuri necesare
//dorim stocarea unui graf intr-o lista de liste
//astfel avem nod ListaPrincipala si NodListaSecundara

typedef struct Nod { // GRAFUL       O-O-O-O-O  (Lista principala)
	Masina info;
	struct Nod* next;
	struct NodS* vecini;

} Nod;

typedef struct NodS { // Listele din GRAF       O-O-O-O-O  (Listele secundare)
	struct Nod* info; //						| | | | |
	struct NodS* next; //						v v v v v
} NodS; //										N N	N N	N

void inserareInListaPrincipala(Nod** graf, Masina masinaNoua ) {
	Nod* nou = malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = NULL;
	nou->vecini = NULL;
	if ((*graf) == NULL) {
		(*graf) = nou;
	}
	else {
		Nod* p = *graf;
		while (p->next != NULL) {
			p = p->next;
		}
		p->next = nou;
	}
}

void inserareInListaSecundara(NodS** cap, Nod* vecin) {
	NodS* nou = malloc(sizeof(NodS));
	nou->next = NULL;
	nou->info = vecin;
	if ((*cap) == NULL) {
		(*cap) = nou;
	}
	else {
		NodS* p = (*cap);
		while (p->next) {
			p = p->next;
		}
		p = nou;
	}
}

void* cautaNodDupaID(Nod* graf, int id) {
	while (graf && graf->info.id != id) {
		graf = graf->next;
	}
	return graf;
}

void inserareMuchie(Nod* graf, int idStart, int idStop) {
	Nod* nodStart = cautaNodDupaID(graf,idStart);
	Nod* nodStop = cautaNodDupaID(graf, idStop);
	if (nodStart != NULL && nodStop != NULL) {
		inserareInListaSecundara(&nodStart->vecini, nodStop);
		inserareInListaSecundara(&nodStop->vecini, nodStart);
	}
}


Nod* citireNoduriMasiniDinFisier(const char* numeFisier) {
	FILE* fptr = fopen(numeFisier, "r");
	Nod* graf = NULL;
	while (!feof(fptr)) {
		inserareInListaPrincipala(&graf, citireMasinaDinFisier(fptr));
	}
	fclose(fptr);
	return graf;
}

void citireMuchiiDinFisier(Nod* graf, const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste 
	//toate id-urile de start si stop pentru fiecare muchie
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* fptr = fopen(numeFisier, "r");
	int start, stop;
	while (!feof(fptr)) {
		fscanf(fptr, "%d %d", &start, &stop);
		inserareMuchie(graf, start, stop);
	}
}

void dezalocareNoduriGraf(Nod** graf) {
	//sunt dezalocate toate masinile din graf 
	//si toate nodurile celor doua liste
	if (*graf == NULL) return;
	else {
		Nod* p = *graf;
		while (p) {
			NodS* s = p->vecini;
			while (s) {
				NodS* aux = s;
				s = s->next;
				free(aux);
			}
			free(p->info.model);
			free(p->info.numeSofer);

			Nod* temp = p;
			p = p->next;
			free(temp);
		}
	}
	*graf = NULL;
}

void afiseazaListaSecundara(Nod* graf, int id) { // *vecini
	Nod* nou = cautaNodDupaID(graf, id);
	NodS* aux = nou->vecini;
	while (aux) {
		afisareMasina(aux->info->info);
		aux = aux->next;
	}
}	

int main() {

	Nod* graf = citireNoduriMasiniDinFisier("masini.txt");
	citireMuchiiDinFisier(graf, "muchii.txt");
	afiseazaListaSecundara(graf, 8);
	dezalocareNoduriGraf(&graf);
	return 0;
}