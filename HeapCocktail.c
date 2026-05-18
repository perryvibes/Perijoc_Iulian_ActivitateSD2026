#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Cocktail {
	int id;
	int nrIngrediente;
	float pret;
	char* denumire;
	char* origine;
};

typedef struct Cocktail Cocktail;

typedef struct Heap {
	Cocktail* vector;
	int lungime;
	int nrCocktails;
} Heap;

void afisareCocktail(Cocktail c) {
	printf("Id:%d\n", c.id);
	printf("Numar ingrediente:%d\n", c.nrIngrediente);
	printf("Pret:%5.2f\n", c.pret);
	printf("Denumire:%s\n", c.denumire);
	printf("Origine:%s\n\n", c.origine);
}

Cocktail citesteCocktailDinFisier(FILE* file) {
	Cocktail cocktail;
	char buffer[100];
	char delimitator[3] = ",\n";
	fgets(buffer, 100, file);
	char* token;
	token = strtok(buffer, delimitator);
	cocktail.id = atoi(token);
	token = strtok(NULL, delimitator);
	cocktail.nrIngrediente = atoi(token);
	token = strtok(NULL, delimitator);
	cocktail.pret = atof(token);
	token = strtok(NULL, delimitator);
	cocktail.denumire = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(cocktail.denumire, token);
	token = strtok(NULL, delimitator);
	cocktail.origine = malloc((strlen(token) + 1) * sizeof(char));
	strcpy(cocktail.origine, token);
	return cocktail;
}

Heap initializareHeap(int lungime) {
	Heap heap;
	heap.lungime = lungime; // total
	heap.nrCocktails = 0; // vizibile
	heap.vector = (Cocktail*)malloc(sizeof(Cocktail) * lungime);
	return heap;
}

void filtreazaHeap(Heap heap, int pozNod) {
	int pozSt = 2 * pozNod + 1;
	int pozDr = 2 * pozNod + 2;
	int pozMax = pozNod;
	if (pozSt < heap.nrCocktails && heap.vector[pozSt].id > heap.vector[pozMax].id) {
		pozMax = pozSt;
	} else if (pozDr < heap.nrCocktails && heap.vector[pozDr].id > heap.vector[pozMax].id) {
		pozMax = pozDr;
	}
	if (pozMax != pozNod) {
		Cocktail aux = heap.vector[pozMax];
		heap.vector[pozMax] = heap.vector[pozNod];
		heap.vector[pozNod] = aux;
		// verificam din nou daca avem situatie dupa aceasta schimbare
		if (pozMax < (heap.nrCocktails - 2) / 2) // formula pentru ultimul parinte din arbore
		{
			filtreazaHeap(heap, pozMax);
		}
	}
}

void afiseazaHeap(Heap heap) { // cocktails vizibile!
	for (int i = 0; i < heap.nrCocktails; i++) {
		afisareCocktail(heap.vector[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrCocktails; i < heap.lungime; i++) {
		afisareCocktail(heap.vector[i]);
	}
}

Heap citesteHeapDinFisier(const char* numeFisier) {
	Heap heap = initializareHeap(4);
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		// nrCocktails e 0!!!
		heap.vector[heap.nrCocktails++] = citesteCocktailDinFisier(fptr);
	}
	fclose(fptr);
	for (int i = (heap.nrCocktails - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

Cocktail extrageCocktail(Heap* heap) {
	Cocktail aux;
	if (heap->lungime > 0) {
		aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrCocktails - 1];
		heap->vector[heap->nrCocktails - 1] = aux;
		heap->nrCocktails--;
		for (int i = (heap->nrCocktails - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
	}
	return aux;
}

void dezalocareHeap(Heap* heap) {
	if (heap) {
		for (int i = 0; i < heap->lungime; i++) {
			free(heap->vector[i].denumire);
			free(heap->vector[i].origine);
		}
		free(heap->vector);
		heap->vector = NULL;
		heap->lungime = 0;
		heap->nrCocktails = 0;
	}
}

int main() {
	Heap h = citesteHeapDinFisier("cocktails.txt");
	afiseazaHeap(h);

	printf("\n=================\n");
	afiseazaHeapAscuns(h);

	printf("\n=================\n");
	Cocktail c1 = extrageCocktail(&h);
	afisareCocktail(c1);

	printf("\n=================\n");
	dezalocareHeap(&h);
	return 0;
}