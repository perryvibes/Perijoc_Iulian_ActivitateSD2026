//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////trebuie sa folositi fisierul masini.txt
////sau va creati un alt fisier cu alte date
//
//struct StructuraMasina {
//	int id;
//	int nrUsi;
//	float pret;
//	char* model;
//	char* numeSofer;
//	unsigned char serie;
//};
//typedef struct StructuraMasina Masina;
//
//Masina citireMasinaDinFisier(FILE* file) {
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* aux;
//	Masina m1;
//	aux = strtok(buffer, sep);
//	m1.id = atoi(aux);
//	m1.nrUsi = atoi(strtok(NULL, sep));
//	m1.pret = atof(strtok(NULL, sep));
//	aux = strtok(NULL, sep);
//	m1.model = malloc(strlen(aux) + 1);
//	strcpy_s(m1.model, strlen(aux) + 1, aux);
//
//	aux = strtok(NULL, sep);
//	m1.numeSofer = malloc(strlen(aux) + 1);
//	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);
//
//	m1.serie = *strtok(NULL, sep);
//	return m1;
//}
//
//Masina initializareMasina(int _id, int _nrUsi, float _pret, char* _model, char* _numeSofer, unsigned char _serie) {
//	Masina m;
//	if (_id > 0) {
//		m.id = _id;
//		m.nrUsi = _nrUsi;
//		m.pret = _pret;
//		m.serie = _serie;
//		m.model = malloc(strlen(_model) * sizeof(char) + 1);
//		strcpy(m.model, _model);
//		m.numeSofer = malloc(strlen(_numeSofer) * sizeof(char) + 1);
//		strcpy(m.numeSofer, _numeSofer);
//	}
//	else {
//		m.id = -1;
//	}
//	return m;
//}
//
//void afisareMasina(Masina masina) {
//	printf("\nId: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
////STACK
////Alegeti prin ce veti reprezenta stiva si creati structura necesara acestei stive
////putem reprezenta o stiva prin LSI, LDI sau vector
//typedef struct NodStack NodStack;
//struct NodStack {
//	Masina masina;
//	NodStack* next;
//};
//
//void afisareStiva(NodStack* stack) {
//	if (stack == NULL) return;
//	while (stack) {
//		afisareMasina(stack->masina);
//		stack = stack->next;
//	}
//}
//
//void pushStack(NodStack** stack, Masina masina) {
//	
//	NodStack* nou = (NodStack*)malloc(sizeof(NodStack));
//	nou->masina = masina;
//	nou->next = *stack;
//	*stack = nou;
//
//}
//
//Masina popStack(NodStack** stack) {
//	if ((*stack)) {
//		NodStack* aux = (*stack);
//		(*stack) = (*stack)->next;
//		Masina m = aux->masina; //shallow copy!!
//		free(aux);
//		return m;
//	}
//	else {
//		return (Masina){ -1,0,0,NULL,NULL,0 };
//	}
//}
//
//int emptyStack(NodStack* stack) {
//	return !stack;
//}
//
//NodStack* citireStackMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	NodStack* stack = NULL;
//	FILE* fptr = fopen(numeFisier, "r");
//	while (!feof(fptr)) {
//		pushStack(&stack, citireMasinaDinFisier(fptr));
//	}
//	fclose(fptr);
//	return stack;
//}
//
//
//void dezalocareStivaDeMasini(NodStack** stack) {
//	//sunt dezalocate toate masinile si stiva de elemente
//	while ((*stack)) {
//		NodStack* temp = (*stack);
//		(*stack) = (*stack)->next;
//		free(temp->masina.model);
//		free(temp->masina.numeSofer);
//		free(temp);
//	}
//	stack = NULL;
//	printf(" Succes!");
//}
//
//int size(NodStack* stack) {
//	//returneaza numarul de elemente din stiva
//	int count = 0;
//	while (stack) {
//		count++;
//		stack = stack->next;
//	}
//	return count;
//}
//
//Masina getMasinaByIDStiva(NodStack** stack, int _id) {
//	NodStack* temp = NULL;
//	Masina rezultat;
//	rezultat.id = -1;
//	while (!emptyStack(*stack)) {
//		Masina m = popStack(stack);
//		if (m.id == _id) {
//			rezultat = m;
//		}
//		pushStack(&temp, m);
//	}
//	while (!emptyStack(temp)) {
//		pushStack(stack, popStack(&temp));
//	}
//	return rezultat;
//}
//
//float calculeazaPretTotalStiva(NodStack** stack) {
//	NodStack* temp = NULL;
//	float sum = 0;
//	while (!emptyStack(*stack)) {
//		Masina m = popStack(stack);
//		sum += m.pret;
//		pushStack(&temp, m);
//	}
//	while (!emptyStack(temp)) {
//		pushStack(stack, popStack(&temp));
//	}
//	return sum;
//}
//
////QUEUE
////Alegeti prin ce veti reprezenta coada si creati structura necesara acestei cozi
////putem reprezenta o coada prin LSI, LDI sau vector
//
//typedef struct {
//	Masina masina;
//	struct NodCoada* next;
//	struct NodCoada* prev;
//} NodCoada;
//
//typedef struct {
//	NodCoada* head;
//	NodCoada* tail;
//} Coada;
//
//
//void enqueue(Coada* queue, Masina masinaNoua) {
//	//adauga o masina in coada
//	
//	NodCoada* nou = (NodCoada*)malloc(sizeof(NodCoada));
//	nou->masina = masinaNoua;
//	nou->prev = NULL;
//	nou->next = NULL;
//
//	if (queue != NULL) {
//		if (queue->head == NULL) {
//			queue->head = nou;
//			queue->tail = nou;
//		}
//		else {
//			// inserare la inceput de coada
//			queue->head->prev = nou;
//			nou->next = queue->head;
//			queue->head = nou;
//		}
//	}
//	else {
//		printf("\nNu exista o lista de tip coada!\n");
//		return;
//	}
//	
//}
//
//Masina dequeue(Coada* queue) {
//	//extrage o masina din coada
//	Masina m;
//	m.id = -1;
//
//	if (queue == NULL) { printf("\nNu exista o lista de tip coada!\n"); return; }
//	else {
//		if (queue->tail == NULL) {
//			queue->head = NULL;
//			printf("\nNu exista nod pe care sa-l stergem\n");
//		}
//		else {
//			m = queue->tail->masina;
//			NodCoada* temp = (NodCoada*)malloc(sizeof(NodCoada));
//			temp = queue->tail;
//			if (queue->tail->prev == NULL) {
//				queue->tail = NULL;
//				queue->head = NULL;
//			}
//			else {
//				queue->tail = queue->tail->prev;
//				queue->tail->next = NULL;
//			}
//			free(temp);
//		}
//	}
//	return m;
//}
//
//Coada citireCoadaDeMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	Coada lista;
//	lista.head = NULL;
//	lista.tail = NULL;
//	FILE* fptr = fopen(numeFisier, "r");
//	while (!feof(fptr)) {
//		enqueue(&lista, citireMasinaDinFisier(fptr));
//	}
//	fclose(fptr);
//	return lista;
//}
//
//void afisareCoada(Coada lista) {
//	NodCoada* p = lista.head;
//	while (p) {
//		afisareMasina(p->masina);
//		p = p->next;
//	}
//}
//
//void dezalocareCoadaDeMasini(Coada* lista) {
//	//sunt dezalocate toate masinile si coada de elemente
//	printf("\nDezalocare masini: \n");
//	while (lista->head) {
//		dequeue(lista);
//		printf("\nSucces!\n");
//	}
//	printf("\nDezalocare efectuata!\n");
//}
//
//
////metode de procesare
//Masina getMasinaByIDCoada(Coada* lista, int _id) {
//	Coada temp;
//	temp.head = NULL;
//	temp.tail = NULL;
//
//	Masina rezultat;
//	rezultat.id = -1;
//
//	while (lista->head) {
//		Masina m = dequeue(lista);
//		if (m.id == _id) {
//			rezultat = m;
//		}
//		enqueue(&temp, m);
//	}
//	while (temp.head) {
//		enqueue(lista, dequeue(&temp));
//	}
//	return rezultat;
//}
//
//
//float calculeazaPretTotalCoada(Coada* lista) {
//	Coada temp;
//	temp.head = NULL;
//	temp.tail = NULL;
//	float sum = 0;
//	while (lista->head) {
//		Masina m = dequeue(lista);
//		sum += m.pret;
//		enqueue(&temp, m);
//	}
//	while (temp.head) {
//		enqueue(lista, dequeue(&temp));
//	}
//	return sum;
//}
//
//int main() {
//	
//	NodStack* stiva = citireStackMasiniDinFisier("masini.txt");
//	afisareStiva(stiva);
//	printf("=======================================");
//	
//	Masina m1 = popStack(&stiva);
//	afisareMasina(m1);
//
//	printf("=======================================");
//	
//	Masina m2 = initializareMasina(4,4,29410,"M5","Jhon",'M');
//	pushStack(&stiva, m2);
//	afisareStiva(stiva);
//
//	printf("=======================================");
//	
//	printf("\nDimensiunea Stivei: %d\n", size(stiva));
//		
//	printf("=======================================");
//	
//	NodStack* stivaGoala = NULL;
//	printf("\nStiva este goala? %d\n", emptyStack(stivaGoala));
//		
//	printf("=======================================");
//
//	afisareMasina(getMasinaByIDStiva(&stiva, 6));
//
//	printf("=======================================");
//
//	printf("\nSuma totala pe STIVA este de %.2f\n", calculeazaPretTotalStiva(&stiva));
//
//	printf("=======================================");
//
//	printf("\nDezalocare: ...");
//	dezalocareStivaDeMasini(&stiva);
//
//	// Coada
//
//	Coada lista = citireCoadaDeMasiniDinFisier("masini.txt");
//	afisareCoada(lista);
//
//	printf("\n=======================================\n");
//	
//	dequeue(&lista);
//	afisareCoada(lista);
//
//	printf("=======================================");
//	
//	Masina m2 = initializareMasina(14, 4, 29410, "M5", "Jhon", 'M');
//	enqueue(&lista, m2);
//	afisareCoada(lista);
//
//	printf("=======================================");
//	
//	Masina m3 = getMasinaByIDCoada(&lista, 6);
//	afisareMasina(m3);
//
//	printf("=======================================");
//
//	printf("\nSuma totala COADA este de %.2f\n", calculeazaPretTotalCoada(&lista));
//	
//	printf("=======================================");
//
//	dezalocareCoadaDeMasini(&lista);
//	
//	printf("=======================================");
//
//	return 0;
//}