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
//typedef struct Nod Nod;
//struct Nod {
//	Masina masina;
//	Nod* next;
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
//	m1.pret= atof(strtok(NULL, sep));
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
//void afisareListaMasini(Nod* lista) {
//	if (lista != NULL) {
//		while (lista) {
//			afisareMasina(lista->masina);
//			lista = lista->next;
//		}
//	}
//	else {
//		printf("\nLista nu exista!\n");
//	}
//}
//
//void adaugaMasinaInLista(Nod** lista, Masina masinaNoua) {
//	//adauga la final in lista primita o noua masina pe care o primim ca parametru
//	Nod* aux = (Nod*)malloc(sizeof(Nod));
//	aux->masina = masinaNoua;
//	aux->next = NULL;
//	if ((*lista) != NULL) {
//		Nod* p = (*lista);
//		while (p->next != NULL) {
//			p = p->next;
//		}
//		p->next = aux;
//	}
//	else {
//		(*lista) = aux;
//	}
//}
//
//void adaugaLaInceputInLista(Nod** lista, Masina masinaNoua) {
//	//adauga la inceputul listei o noua masina pe care o primim ca parametru
//	Nod* aux = (Nod*)malloc(sizeof(Nod));
//	aux->masina = masinaNoua;
//	aux->next = (*lista);
//	(*lista) = aux;	
//}
//
//Nod* citireListaMasiniDinFisier(const char* numeFisier) {
//	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
//	//prin apelul repetat al functiei citireMasinaDinFisier()
//	//ATENTIE - la final inchidem fisierul/stream-ul
//	FILE* fptr = fopen(numeFisier, "r");
//	Nod* lista = NULL;
//	while (!feof(fptr)) {
//		adaugaMasinaInLista(&lista, citireMasinaDinFisier(fptr));
//		//adaugaLaInceputInLista(&lista, citireMasinaDinFisier(fptr));
//	}
//	fclose(fptr);
//	return lista;
//}
//
//void dezalocareListaMasini(/*lista de masini*/) {
//	//sunt dezalocate toate masinile si lista de elemente
//}
//
//float calculeazaPretMediu(Nod* lista) {
//	//calculeaza pretul mediu al masinilor din lista.
//	float sum = 0;
//	int count = 0;
//	Nod* p = lista;
//	while (p) {
//		sum += p->masina.pret;
//		count++;
//		p = p->next;
//	}
//	return sum/count;
//}
//
//void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
//
//	// tratare situatie unde exista de la inceput seria cautata
//	while ((*cap) && (*cap)->masina.serie == serieCautata) {
//		Nod* p = (*cap);
//		(*cap) = p->next;
//		if (p->masina.numeSofer) {
//			free(p->masina.numeSofer);
//		}
//		if (p->masina.model) {
//			free(p->masina.model);
//		}
//		free(p);
//	}
//	if (!(*cap)) {
//		Nod* aux = (*cap);
//		while (aux) {
//			while (aux->next != NULL && aux->masina.serie == serieCautata) {
//				aux = aux->next;
//			}
//			if (aux->next) {
//				Nod* temp = aux->next;
//				aux->next = temp->next;
//				if (temp->masina.numeSofer) {
//					free(temp->masina.numeSofer);
//				}
//				if (temp->masina.model) {
//					free(temp->masina.model);
//				}
//				free(temp);
//			}
//			else {
//				aux = NULL;
//			}
//		}
//	}
//}
//
//float calculeazaPretulMasinilorUnuiSofer(Nod* lista, const char* numeSofer) {
//	//calculeaza pretul tuturor masinilor unui sofer.
//	Nod* p = lista;
//	float pretMasini = 0;
//	while (p) {
//		int rez = strcmp(p->masina.numeSofer, numeSofer);
//		if (!rez) {
//			pretMasini += p->masina.pret;
//		}
//		p = p->next;
//	}
//	return pretMasini;
//}
//
//int main() {
//	Nod* lista = citireListaMasiniDinFisier("masini.txt");
//	afisareListaMasini(lista);
//	printf("=============================================");
//
//	float sum = calculeazaPretMediu(lista);
//	printf("\nPret Mediu: %.2f\n", sum);
//	float pretMasini = calculeazaPretulMasinilorUnuiSofer(lista, "Ionescu");
//	printf("\nPretul Masinilor: %.2f\n", pretMasini);
//
//	printf("=============================================");
//	stergeMasiniDinSeria(&lista, 'A');
//	afisareListaMasini(lista);
//
//	return 0;
//}