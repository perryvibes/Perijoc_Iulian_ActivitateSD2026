#define _CRT_SECURE_NO_WARNINGS
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

struct Heap {
	int lungime;
	Masina* vector;
	int nrMasini; // numar de masini VIZIBILE
};
typedef struct Heap Heap;

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

Heap initializareHeap(int lungime) {
	Heap heapMasini;
	heapMasini.lungime = lungime;
	heapMasini.vector = (Masina*)malloc(sizeof(Masina) * lungime);
	heapMasini.nrMasini = 0;
	return heapMasini;
}

void filtreazaHeap(Heap heap, int pozNod) {
	// practic metoda de functionare a heap-ului
	int pozMax = pozNod;
	int pozNodStanga = 2 * pozNod + 1;
	int pozNodDreapta = 2 * pozNod + 2;
	if (pozNodStanga < heap.nrMasini //verificam sa fie mai mic decat nr de masini vizibile
		&& heap.vector[pozNodStanga].pret > heap.vector[pozNod].pret)
	{
		pozMax = pozNodStanga;
	}
	if (pozNodDreapta < heap.nrMasini
		&& heap.vector[pozNodDreapta].pret > heap.vector[pozNod].pret)
	{
		pozMax = pozNodDreapta;
	}
	if (pozMax != pozNod) { // avem modificari la nivelul pozitiilor
		Masina aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
	}
	if (pozMax <= (heap.nrMasini - 2) / 2) {
		filtreazaHeap(heap, pozMax);
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {

	// citim prima data masinile din fisier si le adaugam in heap
	Heap heapMasini = initializareHeap(10);
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		heapMasini.vector[heapMasini.nrMasini++] = citireMasinaDinFisier(fptr);
	}
	fclose(fptr);
	// folosim functia heap-ului pentru a filtra elementele. Cum procedam? 
	// Preluam ultimul parinte si apoi decrementam spre radacina.
	// Folosim filtrarea pentru fiecare nod incepand de la nod parinte spre radacina.
	// FORMULA ultimului parinte = (nrMasini-2)/2
	for (int i = (heapMasini.nrMasini - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heapMasini, i);
	}
	return heapMasini;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrMasini; i++) {
		afisareMasina(heap.vector[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	//afiseaza elementele ascunse din heap
}

Masina extrageMasina(void* heap) {
	//extrage si returneaza masina de pe prima pozitie
	//elementul extras nu il stergem...doar il ascundem
}


void dezalocareHeap(Heap* heap) {
	//sterge toate elementele din Heap
}

int main() {


	return 0;
}