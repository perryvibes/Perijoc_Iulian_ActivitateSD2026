//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//
//typedef struct Pilot {
//	int id;
//	float greutate;
//	char* echipa;
//	int castiguri; // numarul de castiguri pe care le-a avut pilotul
//} Pilot;
//
//typedef struct Nod {
//	Pilot info;
//	struct Nod* nodSt;
//	struct Nod* nodDr;
//} Nod;
//
//void afisarePilot(Pilot pilot) {
//	printf("\nId pilot: %d", pilot.id);
//	printf("\nGreutate pilot: %.2f", pilot.greutate);
//	printf("\nEchipa pilot: %s", pilot.echipa);
//	printf("\nCastiguri pilot: %d\n", pilot.castiguri);
//}
//
//Pilot citirePilotFisier(FILE* fptr) {
//	Pilot pilot;
//	char buffer[100];
//	char sep[3] = ",\n";
//	fgets(buffer, 100, fptr);
//	char* token = strtok(buffer, sep);
//	pilot.id = atoi(token);
//	token = strtok(NULL, sep);
//	pilot.greutate = atof(token);
//	token = strtok(NULL, sep);
//	pilot.echipa = malloc(strlen(token) + 1);
//	strcpy(pilot.echipa, token);
//	token = strtok(NULL, sep);
//	pilot.castiguri = atoi(token);
//	return pilot;
//}
//
//void inserarePilotArbore(Nod** radacina, Pilot pilotNou) {
//	//inserare pe criteriul id-ului
//	if (*radacina == NULL) {
//		Nod* nou = malloc(sizeof(Nod));
//		nou->info = pilotNou;
//		nou->nodSt = NULL;
//		nou->nodDr = NULL;
//		*radacina = nou;
//	}
//	else {
//		if ((*radacina)->info.id > pilotNou.id) {
//			inserarePilotArbore(&((*radacina)->nodSt), pilotNou);
//		}
//		else if ((*radacina)->info.id < pilotNou.id) {
//			inserarePilotArbore(&((*radacina)->nodDr), pilotNou);
//		}
//	}
//}
//
//Nod* citireArboreFisier(const char* numeFisier) {
//	Nod* arbore = NULL;
//	FILE* fptr = fopen(numeFisier, "r");
//	while (!feof(fptr)) {
//		inserarePilotArbore(&arbore, citirePilotFisier(fptr));
//	}
//	fclose(fptr);
//	return arbore;
//}
//
//void afisareArboreInordine(Nod* arbore) {
//	if (arbore) {
//		afisareArboreInordine(arbore->nodSt);
//		afisarePilot(arbore->info);
//		afisareArboreInordine(arbore->nodDr);
//	}
//}
//
//int nrTotalPiloti(Nod* arbore, const char* echipa) {
//	if (arbore) {
//		int sum = 0;
//		int st = nrTotalPiloti(arbore->nodSt,echipa);
//		int dr = nrTotalPiloti(arbore->nodDr,echipa);
//		if (strcmp(arbore->info.echipa, echipa) == 0) {
//			sum++;
//		}
//		return sum + st + dr;
//	}
//	return 0;
//}
//
//Pilot cautarePilot(Nod* arbore, int id) {
//	Pilot pilot = { 0,0,NULL,0 }; // dupa id.
//	if (arbore) {
//		if (arbore->info.id > id) {
//			pilot = cautarePilot(arbore->nodSt, id);
//		}
//		else if (arbore->info.id < id) {
//			pilot = cautarePilot(arbore->nodDr, id);
//		}
//		else {
//			pilot = arbore->info;
//			pilot.echipa = malloc(strlen(arbore->info.echipa) + 1);
//			strcpy(pilot.echipa, arbore->info.echipa);
//		}
//	}
//	return pilot;
//}
//
//void dezalocare(Nod** arbore) {
//	if (*arbore) {
//		dezalocare(&((*arbore)->nodSt));
//		dezalocare(&((*arbore)->nodDr));
//		free((*arbore)->info.echipa);
//		free(*arbore);
//	}
//}
//
//int celeMaiMulteCastiguri(Nod* arbore) {
//	if (arbore) {
//		int max = 0;
//		max = celeMaiMulteCastiguri(arbore->nodSt);
//		max = celeMaiMulteCastiguri(arbore->nodDr);
//		if (max < arbore->info.castiguri) {
//			max = arbore->info.castiguri;
//		}
//		return max;
//	}
//	else {
//		return 0;
//	}
//}
//
//int main() {
//
//	Nod* arbore = citireArboreFisier("piloti.txt");
//	afisareArboreInordine(arbore);
//	printf("\n==========\n");
//	
//	printf("Nr total piloti: %d", nrTotalPiloti(arbore, "Red"));
//	printf("\n==========\n");
//	
//	Pilot m = cautarePilot(arbore, 4);
//	afisarePilot(m);
//	free(m.echipa);
//	printf("\n==========\n");
//	
//	printf("Cele mai multe castiguri: %d", celeMaiMulteCastiguri(arbore));
//	
//	dezalocare(&arbore);
//
//	return 0;
//}