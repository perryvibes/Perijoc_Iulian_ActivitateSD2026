//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//
//struct Pictura {
//	int id;
//	float pret;
//	char* centruExpozitie;
//	char* numeAutor;
//};
//typedef struct Pictura Pictura;
//
//typedef struct Nod {
//	Pictura info;
//	struct Nod* nodSt;
//	struct Nod* nodDr;
//} Nod;
//
//void afiseazaPictura(Pictura p) {
//	printf("Id:%d\n", p.id);
//	printf("Pret:%5.2f\n", p.pret);
//	printf("Centru expozitie:%s\n", p.centruExpozitie);
//	printf("Nume autor:%s\n\n", p.numeAutor);
//}
//
//
//Pictura citestePicturaDinFisier(FILE* file) {
//	Pictura pictura;
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token = strtok(buffer, sep);
//	pictura.id = atoi(token);
//	token = strtok(NULL, sep);
//	pictura.pret = atof(token);
//	token = strtok(NULL, sep);
//	pictura.centruExpozitie = malloc(strlen(token) + 1);
//	strcpy(pictura.centruExpozitie, token);
//	token = strtok(NULL, sep);
//	pictura.numeAutor = malloc(strlen(token) + 1);
//	strcpy(pictura.numeAutor, token);
//	return pictura;
//}
//
//
//int calculInaltime(Nod* radacina) {
//	if (radacina) {
//		return 1 + max(calculInaltime(radacina->nodSt), calculInaltime(radacina->nodDr));
//	}
//}
//
//int GE(Nod* radacina) {
//	if (radacina) {
//		return calculInaltime(radacina->nodSt) - calculInaltime(radacina->nodDr);
//	}
//	else {
//		return 0;
//	}
//
//}
//
//void rotireStanga(Nod** radacina) {
//	if (*radacina) {
//		Nod* aux = (*radacina)->nodDr;
//		(*radacina)->nodDr = aux->nodSt;
//		aux->nodSt = (*radacina);
//		(*radacina) = aux;
//	}
//}
//
//void rotireDreapta(Nod** radacina) {
//	if (*radacina) {
//		Nod* aux = (*radacina)->nodSt;
//		(*radacina)->nodSt = aux->nodDr;
//		aux->nodDr = (*radacina);
//		(*radacina) = aux;
//	}
//}
//
//void adaugaPicturaInArbore(Nod** arbore, Pictura picturaNoua) {
//	if ((*arbore) == NULL) {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->info = picturaNoua;
//		nou->nodSt = NULL;
//		nou->nodDr = NULL;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id > picturaNoua.id) {
//			adaugaPicturaInArbore(&((*arbore)->nodSt), picturaNoua);
//		}
//		else if ((*arbore)->info.id < picturaNoua.id) {
//			adaugaPicturaInArbore(&((*arbore)->nodDr), picturaNoua);
//		}
//		if (GE(*arbore) == 2) {
//			if (GE((*arbore)->nodSt) != 1) {
//				rotireStanga(&((*arbore)->nodSt));
//			}
//			rotireDreapta(arbore);
//		}
//		else if (GE(*arbore) == -2) {
//			if (GE((*arbore)->nodDr) != -1) {
//				rotireDreapta(&((*arbore)->nodDr));
//			}
//			rotireStanga(arbore);
//		}
//	}
//}
//
//
//Nod* citesteArboreDinFisier(const char* numeFisier) {
//	Nod* arbore = NULL;
//	FILE* fptr = fopen(numeFisier, "r");
//	while (!feof(fptr)) {
//		adaugaPicturaInArbore(&arbore, citestePicturaDinFisier(fptr));
//	}
//	fclose(fptr);
//	return arbore;
//}
//
//
//void afisareArboreAVL(Nod* arbore) {  //SRD
//	if (arbore) {
//		afisareArboreAVL(arbore->nodSt);
//		afiseazaPictura(arbore->info);
//		afisareArboreAVL(arbore->nodDr);
//	}
//}
//
//void dezalocaArbore(Nod** arbore) {
//	if (*arbore) {
//		dezalocaArbore(&((*arbore)->nodSt));
//		dezalocaArbore(&((*arbore)->nodDr));
//		free((*arbore)->info.centruExpozitie);
//		free((*arbore)->info.numeAutor);
//		free(*arbore);
//		*arbore = NULL;
//	}
//}
//
//Pictura getPicturaById(Nod* arbore, int id) {
//	
//}
//
//int determinaNrNoduri(Nod* arbore) {
//	
//}
//
//float calculeazaPretTotal(Nod* arbore) {
//	
//}
//
//float calculeazaPretTotalCentru(Nod* arbore, const char* centru) {
//	
//}
//
//int main() {
//	Nod* arbore = citesteArboreDinFisier("picturi.txt");
//	afisareArboreAVL(arbore);
//
//	dezalocaArbore(&arbore);
//	printf("\n==========\n");
//
//
//}