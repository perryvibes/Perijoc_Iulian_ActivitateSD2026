#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Pacient {
	int id;
	char* nume;
	int varsta;
	float gradUrgenta;
	char* problema; // problema cu care s-a prezentat

} Pacient;

typedef struct Heap {
	Pacient* vector;
	int lungime;
	int nrPacienti;
} Heap;

void afisarePacient(Pacient pacient) {
	printf("\n Id pacient: %d", pacient.id);
	printf("\n Nume pacient: %s", pacient.nume);
	printf("\n Varsta pacient: %d", pacient.varsta);
	printf("\n Grad urgenta pacient: %.2f", pacient.gradUrgenta);
	printf("\n Problema pacient: %s\n", pacient.problema);
}

Pacient citirePacientFisier(FILE* fptr) {
	Pacient pacient;
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, fptr);
	char* token = strtok(buffer, sep);
	pacient.id = atoi(token);
	token = strtok(NULL, sep);
	pacient.nume = malloc(strlen(token) + 1);
	strcpy(pacient.nume, token);
	token = strtok(NULL, sep);
	pacient.varsta = atoi(token);
	token = strtok(NULL, sep);
	pacient.gradUrgenta = atof(token);
	token = strtok(NULL, sep);
	pacient.problema = malloc(strlen(token) + 1);
	strcpy(pacient.problema, token);
	return pacient;
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime;
	heap.nrPacienti = 0;
	heap.vector = malloc(sizeof(Pacient) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozNod) {
	// dupa gradul de urgenta
	int pozSt = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;
	int pozMax = pozNod;
	if (pozSt < heap.nrPacienti && heap.vector[pozSt].gradUrgenta > heap.vector[pozMax].gradUrgenta) {
		pozMax = pozSt;
	}
	if (pozDr < heap.nrPacienti && heap.vector[pozDr].gradUrgenta > heap.vector[pozMax].gradUrgenta) {
		pozMax = pozDr;
	}
	if (pozMax != pozNod) {
		Pacient aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
		if (pozMax <= (heap.nrPacienti - 2) / 2) {
			filtreazaHeap(heap, pozMax);
		}
	}
}

Heap citireHeapFisier(const char* numeFisier) {
	Heap heap = initializareHeap(4);
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		heap.vector[heap.nrPacienti++] = citirePacientFisier(fptr);
	}
	fclose(fptr);
	for (int i = (heap.nrPacienti - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}


void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrPacienti; i++) {
		afisarePacient(heap.vector[i]);
	}
}

Pacient extragePacient(Heap* heap) {
	if (heap) {
		Pacient aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrPacienti - 1];
		heap->vector[heap->nrPacienti - 1] = aux;
		heap->nrPacienti--;
		for (int i = (heap->nrPacienti - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
		return aux;
	}
	else {
		return (Pacient) { 0, NULL, 0, 0, NULL };
	}
}

void dezalocare(Heap* heap) {
	if (heap->lungime > 0) {
		for (int i = 0; i < heap->lungime; i++) {
			free(heap->vector[i].nume);
			free(heap->vector[i].problema);
		}
		free(heap->vector);
		heap->lungime = 0;
		heap->nrPacienti = 0;
		heap->vector = NULL;
	}
}

int main() {
	Heap heap = citireHeapFisier("pacienti.txt");
	afisareHeap(heap);
	printf("\n========================================\n");
	Pacient m = extragePacient(&heap);
	afisarePacient(m);
	printf("\n========================================\n");
	extragePacient(&heap);
	extragePacient(&heap);
	afisareHeap(heap);
	printf("\n========================================\n");

	dezalocare(&heap);

	return 0;
}
