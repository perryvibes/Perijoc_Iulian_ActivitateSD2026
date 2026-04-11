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

Masina initializareMasina(int _id, int _nrUsi, float _pret, char* _model, char* _numeSofer, unsigned char _serie) {
	Masina m;
	if (_id > 0) {
		m.id = _id;
		m.nrUsi = _nrUsi;
		m.pret = _pret;
		m.serie = _serie;
		m.model = malloc(strlen(_model) * sizeof(char) + 1);
		strcpy(m.model, _model);
		m.numeSofer = malloc(strlen(_numeSofer) * sizeof(char) + 1);
		strcpy(m.numeSofer, _numeSofer);
	}
	else {
		m.id = -1;
	}
	return m;
}

void afisareMasina(Masina masina) {
	printf("\nId: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

//STACK
//Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
//putem reprezenta o stiva prin LSI, LDI sau vector
typedef struct NodStack NodStack;
struct NodStack {
	Masina masina;
	NodStack* next;
};

void afisareStiva(NodStack* stack) {
	if (stack == NULL) return;
	while (stack) {
		afisareMasina(stack->masina);
		stack = stack->next;
	}
}

void pushStack(NodStack** stack, Masina masina) {
	
	NodStack* nou = (NodStack*)malloc(sizeof(NodStack));
	nou->masina = masina;
	nou->next = *stack;
	*stack = nou;

}

Masina popStack(NodStack** stack) {
	if ((*stack)) {
		NodStack* aux = (*stack);
		(*stack) = (*stack)->next;
		Masina m = aux->masina; //shallow copy!!
		free(aux);
		return m;
	}
	else {
		return (Masina){ -1,0,0,NULL,NULL,0 };
	}
}

int emptyStack(NodStack* stack) {
	return !stack;
}

NodStack* citireStackMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	NodStack* stack = NULL;
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		pushStack(&stack, citireMasinaDinFisier(fptr));
	}
	fclose(fptr);
	return stack;
}


void dezalocareStivaDeMasini(NodStack** stack) {
	//sunt dezalocate toate masinile si stiva de elemente
	while ((*stack)) {
		NodStack* temp = (*stack);
		(*stack) = (*stack)->next;
		free(temp->masina.model);
		free(temp->masina.numeSofer);
		free(temp);
	}
	stack = NULL;
	printf(" Succes!");
}

int size(NodStack* stack) {
	//returneaza numarul de elemente din stiva
	int count = 0;
	while (stack) {
		count++;
		stack = stack->next;
	}
	return count;
}

//QUEUE
//Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
//putem reprezenta o coada prin LSI, LDI sau vector
void enqueue(/*coada*/ Masina masina) {
	//adauga o masina in coada
}

Masina dequeue(/*coada*/) {
	//extrage o masina din coada
}

void* citireCoadaDeMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
}

void dezalocareCoadaDeMasini(/*coada*/) {
	//sunt dezalocate toate masinile si coada de elemente
}


//metode de procesare
Masina getMasinaByID(/*stiva sau coada de masini*/int id);

float calculeazaPretTotal(/*stiva sau coada de masini*/);

int main() {
	
	NodStack* stiva = citireStackMasiniDinFisier("masini.txt");
	afisareStiva(stiva);
	printf("=======================================");
	
	Masina m1 = popStack(&stiva);
	afisareMasina(m1);

	printf("=======================================");
	
	Masina m2 = initializareMasina(4,4,29410,"M5","Jhon",'M');
	pushStack(&stiva, m2);
	afisareStiva(stiva);

	printf("=======================================");
	
	printf("\nDimensiunea Stivei: %d\n", size(stiva));
		
	printf("=======================================");
	
	NodStack* stivaGoala = NULL;
	printf("\nStiva este goala? %d\n", emptyStack(stivaGoala));
		
	printf("=======================================");

	printf("\nDezalocare: ...");
	dezalocareStivaDeMasini(&stiva);

	return 0;
}