//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//
//typedef struct BiletAvion {
//	int id;
//	float pret;
//	char* destinatie;
//	char* poartaImbarcare;
//} BiletAvion;
//
//typedef struct Nod {
//	BiletAvion info;
//	struct Nod* nodSt;
//	struct Nod* nodDr;
//} Nod;
//
//BiletAvion citireBiletDinFisier(FILE* file) {
//	// atentie! Este citire BILET din fisier si nu citire ARBORE din fisier!
//	BiletAvion bilet;
//	char buffer[100];
//	char separator[3] = ",\n";
//	fgets(buffer, 100, file);
//	char* token = strtok(buffer, separator);
//	bilet.id = atoi(token);
//	token = strtok(NULL, separator);
//	bilet.pret = atof(token);
//	token = strtok(NULL, separator);
//	bilet.destinatie = malloc(sizeof(char) * (1 + strlen(token)));
//	strcpy(bilet.destinatie, token);
//	token = strtok(NULL, separator);
//	bilet.poartaImbarcare = malloc(sizeof(char) * (1 + strlen(token)));
//	strcpy(bilet.poartaImbarcare, token);
//	token = strtok(NULL, separator);
//	return bilet;
//}
//
//void afisareBilet(BiletAvion b) {
//	printf("Id:%d\n", b.id);
//	printf("Pret:%5.2f\n", b.pret);
//	printf("Destinatie:%s\n", b.destinatie);
//	printf("Poarta imbarcare:%s\n\n", b.poartaImbarcare);
//}
//
//void adaugaBiletInArbore(Nod** arbore, BiletAvion biletNou) {
//	// trebuie sa ne luam un criteriu pentru adaugare, vom lua pretul.
//	if ((*arbore) == NULL) {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->info = biletNou;
//		nou->nodSt = NULL;
//		nou->nodDr = NULL;
//		(*arbore) = nou;
//	}
//	else {
//		if ((*arbore)->info.id > biletNou.id) {
//			adaugaBiletInArbore(&((*arbore)->nodSt), biletNou);
//		}
//		else if ((*arbore)->info.id < biletNou.id) {
//			adaugaBiletInArbore(&((*arbore)->nodDr), biletNou);
//		}
//	}
//}
//
//Nod* citireArboreDinFisier(const char* numeFisier) {
//	Nod* arbore = NULL;
//	FILE* fptr = fopen(numeFisier, "r");
//	while (!feof(fptr)) {
//		adaugaBiletInArbore(&arbore, citireBiletDinFisier(fptr));
//	}
//	fclose(fptr);
//	return arbore;
//}
//
//void afisareInOrdineSRD(Nod* arbore) {
//	if (arbore) {
//		afisareInOrdineSRD(arbore->nodSt);
//		afisareBilet(arbore->info);
//		afisareInOrdineSRD(arbore->nodDr);
//	}
//}
//
//void afisarePreordineRSD(Nod* arbore) {
//	if (arbore) {
//		afisareBilet(arbore->info);
//		afisarePreordineRSD(arbore->nodSt);
//		afisarePreordineRSD(arbore->nodDr);
//	}
//}
//
//void afisarePostordineSDR(Nod* arbore) {
//	if (arbore) {
//		afisarePostordineSDR(arbore->nodSt);
//		afisarePostordineSDR(arbore->nodDr);
//		afisareBilet(arbore->info);
//	}
//}
//
//
//void dezalocareArbore(Nod** arbore) {
//	if ((*arbore)) {
//		dezalocareArbore(&((*arbore)->nodSt));
//		dezalocareArbore(&((*arbore)->nodDr));
//		free((*arbore)->info.destinatie);
//		free((*arbore)->info.poartaImbarcare);
//		free((*arbore));
//		(*arbore) = NULL;
//	}
//}
//
//BiletAvion getBiletById(Nod* arbore, int id) {
//	BiletAvion bilet = {0,0,NULL,NULL};
//	if (arbore) {
//		if (arbore->info.id > id) {
//			bilet = getBiletById(arbore->nodSt, id);
//		}
//		else if (arbore->info.id < id) {
//			bilet = getBiletById(arbore->nodDr, id);
//		}
//		else {
//			return arbore->info;
//		}
//	}
//	return bilet;
//}
//
//int determinaNrNoduri(Nod* arbore) {
//	if (arbore) {
//		int nodSt = determinaNrNoduri(arbore->nodSt);
//		int nodDr = determinaNrNoduri(arbore->nodDr);
//		return 1 + nodSt + nodDr;
//	}
//	else {
//		return 0;
//	}
//}
//
//float calculeazaPretTotal(Nod* arbore) {
//	if (arbore) {
//		float st = calculeazaPretTotal(arbore->nodSt);
//		float dr = calculeazaPretTotal(arbore->nodDr);
//		return arbore->info.pret + st + dr;
//	}
//	else {
//		return 0;
//	}
//}
//
//float calculeazaPretTotalDestinatie(Nod* arbore, const char* destinatie) {
//	if (arbore) {
//		float st = calculeazaPretTotalDestinatie(arbore->nodSt, destinatie);
//		float dr = calculeazaPretTotalDestinatie(arbore->nodDr, destinatie);
//		float sum = 0;
//		if (strcmp(arbore->info.destinatie, destinatie) == 0) {
//			sum += arbore->info.pret;
//		}
//		return sum + st + dr;
//	}
//	else {
//		return 0;
//	}
//}
//
//int main() {
//
//	Nod* arbore = citireArboreDinFisier("bilete.txt");
//	afisarePostordineSDR(arbore);
//	printf("\n=====================\n");
//	
//	BiletAvion b = getBiletById(arbore, 3);
//	afisareBilet(b);
//
//	printf("\n=====================\n");
//
//	printf("\nNr noduri: %d", determinaNrNoduri(arbore));
//
//	printf("\n=====================\n");
//
//	float total = calculeazaPretTotal(arbore);
//	printf("\n Pret total: %.2f", total);
//
//	printf("\n=====================\n");
//
//	printf("Pret total Roma: %.2f", calculeazaPretTotalDestinatie(arbore, "Roma"));
//
//	printf("\n=====================\n");
//
//	dezalocareArbore(&arbore);
//
//	return 0;
//}