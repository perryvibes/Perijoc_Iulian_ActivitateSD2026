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
////creare structura pentru un nod dintr-o lista dublu inlantuita
//typedef struct Nod Nod;
//
//struct Nod {
//	Masina masina;
//	Nod* next;
//	Nod* prev;
//};
//
////creare structura pentru Lista Dubla 
//typedef struct ListaDubla ListaDubla;
//
//struct ListaDubla {
//	Nod* first;
//	Nod* last;
//	int nrNoduri;
//};
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
//void afisareMasina(Masina masina) {
//	printf("Id: %d\n", masina.id);
//	printf("Nr. usi : %d\n", masina.nrUsi);
//	printf("Pret: %.2f\n", masina.pret);
//	printf("Model: %s\n", masina.model);
//	printf("Nume sofer: %s\n", masina.numeSofer);
//	printf("Serie: %c\n\n", masina.serie);
//}
//
//void afisareListaMasiniInceput(ListaDubla lista) {
//	//afiseaza toate elemente de tip masina din lista dublu inlantuita
//	//prin apelarea functiei afisareMasina()
//	Nod* p = lista.first;
//	while (p) {
//		afisareMasina(p->masina);
//		p = p->next;
//	}
//}
//void afisareListaMasiniSfarsit(ListaDubla lista) {
//	//afiseaza toate elemente de tip masina din lista dublu inlantuita
//	//prin apelarea functiei afisareMasina()
//	Nod* p = lista.last;
//	while (p) {
//		afisareMasina(p->masina);
//		p = p->prev;
//	}
//}
//
//void adaugaMasinaInListaSfarsit(ListaDubla* lista, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->masina = masinaNoua; //shallow copy
//	nou->next = NULL;
//	nou->prev = lista->last;
//	if (lista->last != NULL) {
//		lista->last->next = nou;
//	}
//	else {
//		lista->first = nou;
//	}
//	lista->last = nou;
//	lista->nrNoduri++;
//}
//
//void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
//	//adauga la inceputul listei dublu inlantuite o noua masina pe care o primim ca parametru
//	Nod* nou = (Nod*)malloc(sizeof(Nod));
//	nou->masina = masinaNoua;
//	nou->prev = NULL;
//	nou->next = lista->first;
//	if (lista->first != NULL) {
//		lista->first->prev = nou;
//	}
//	else {
//		lista->last = nou;
//	}
//	lista->first = nou;
//	lista->nrNoduri++;
//}
//
//void initializareListaNull(ListaDubla* lista) {
//	lista->first = NULL;
//	lista->last = NULL;
//	lista->nrNoduri = 0;
//};
//
//ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* fptr = fopen("masini.txt", "r");
//	ListaDubla lista;
//	initializareListaNull(&lista);
//	while (!feof(fptr)) {
//		adaugaMasinaInListaSfarsit(&lista, citireMasinaDinFisier(fptr));
//	}
//	fclose(fptr);
//	return lista;
//}
//
//void dezalocareLDMasini(ListaDubla* lista) {
//	Nod* p = lista->first;
//	while (p) {
//		Nod* aux = p;
//		p = p->next;
//		if (aux->masina.model != NULL) {
//			free(aux->masina.model);
//		}
//		if (aux->masina.numeSofer != NULL) {
//			free(aux->masina.numeSofer);
//		}
//		free(aux);
//	}
//	initializareListaNull(lista);
//}
//
//float calculeazaPretMediu(ListaDubla* lista) {
//	//calculeaza pretul mediu al masinilor din lista.
//	if (lista->nrNoduri > 0) {
//		Nod* p = lista->first;
//		float sum = 0.0;
//		while (p) {
//			sum += p->masina.pret;
//			p = p->next;
//		}
//		return sum/lista->nrNoduri;
//	}
//	return 0;
//}
//
//void stergeMasinaDupaID(ListaDubla* lista, int id) {
//	
//	//sterge masina cu id-ul primit.
//	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
//	
//	if (lista->nrNoduri == 0) return;
//	Nod* p = lista->first;
//	while (p && p->masina.id != id){
//		p = p->next;
//	}
//	// am iesit din while si suntem pe nodul pe care vrem sa-l stergem
//	if (p == NULL) return;
//	
//	// tratam cazul pentru primul nod din lista
//	if (p->prev == NULL) {
//		lista->first = p->next;
//		if (lista->first) {
//			lista->first->prev = NULL;
//		}
//	}
//	else {
//		p->prev->next = p->next;
//	}
//
//	// tratam cazul pentru ultimul nod din lista
//	if (p->next == NULL) {
//		lista->last = p->prev;
//	}
//	else {
//		p->next->prev = p->prev;
//	}
//	if (p->masina.model != NULL) {
//		free(p->masina.model);
//	}
//	if (p->masina.numeSofer != NULL) {
//		free(p->masina.numeSofer);
//	}
//	free(p);
//	lista->nrNoduri--;
//}
//
//char* getNumeSoferMasinaScumpa(ListaDubla* lista) {
//	//cauta masina cea mai scumpa si 
//	//returneaza numele soferului acestei maasini.
//	if (lista->first) {
//		Nod* max = lista->first;
//		Nod* p = lista->first;
//		while (p) {
//			if (p->masina.pret > max->masina.pret) {
//				max = p;
//			}
//			p = p->next;
//		}
//		char* nume = (char*)malloc(sizeof(max->masina.numeSofer) + 1);
//		strcpy_s(nume, sizeof(max->masina.numeSofer)+1, max->masina.numeSofer);
//		return nume;
//	}
//	else {
//		return NULL;
//	}
//}
//int main() {
//
//	ListaDubla list1 = citireLDMasiniDinFisier("masini.txt");
//	afisareListaMasiniInceput(list1);
//	printf("------------------------\n");
//
//	// Stergere
//	stergeMasinaDupaID(&list1, 6);
//
//	afisareListaMasiniSfarsit(list1);
//	
//
//	printf("------------------------\n");
//	printf("Pretul mediu al masinilor este: %.2f\n",calculeazaPretMediu(&list1));
//
//	printf("------------------------\n");
//	
//	char* numeSofer = getNumeSoferMasinaScumpa(&list1);
//	printf("Soferul cu cea mai scumpa masina este: %s\n", numeSofer);
//
//	if (numeSofer != NULL) {
//		free(numeSofer);
//	}
//
//	dezalocareLDMasini(&list1);
//	return 0;
//}