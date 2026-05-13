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

typedef struct Nod {
	Masina masina;
	struct Nod* NodSt;
	struct Nod* NodDr;
} Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if ((*radacina) == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->masina = masinaNoua;
		nou->NodSt = NULL;
		nou->NodDr = NULL;
		(*radacina) = nou;
	}
	else {
		if ((*radacina)->masina.id > masinaNoua.id) {
			adaugaMasinaInArbore(&((*radacina)->NodSt), masinaNoua);
		}
		if ((*radacina)->masina.id <= masinaNoua.id) { // in caz ca avem aceeasi valoare preferam sa il punem pe nodurile din dreapta
			adaugaMasinaInArbore(&((*radacina)->NodDr), masinaNoua);
		}
	}
}

Nod* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	Nod* arbore = NULL;
	FILE* fptr = fopen(numeFisier, "r");
	while (!feof(fptr)) {
		adaugaMasinaInArbore(&arbore, citireMasinaDinFisier(fptr));
	}
	fclose(fptr);
	return arbore;
}

// Sunt 3 MODURI de parcurgere.
// parcurgerea poate fi realizata prin: RSD,SRD,SDR

// 1. PARCURGERE RSD
void afisareMasinaArboreRSD(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, RSD - radacina,stanga,dreapta
		afisareMasina(radacina->masina);
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasinaArboreRSD(radacina->NodDr);
	}
}
// 2. PARCURGERE SRD
void afisareMasinaArboreSRD(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, SRD - stanga,radacina,dreapta
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasina(radacina->masina);
		afisareMasinaArboreRSD(radacina->NodDr);
	}
}
// 3. PARCURGERE SDR
void afisareMasinaArboreSDR(Nod* radacina) {
	if (radacina) {
		// se implementeaza in ordinea acronimului, SRD - stanga,dreapta,radacina
		afisareMasinaArboreRSD(radacina->NodSt);
		afisareMasinaArboreRSD(radacina->NodDr);
		afisareMasina(radacina->masina);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina) {
		dezalocareArboreDeMasini(&(*radacina)->NodSt);
		dezalocareArboreDeMasini(&(*radacina)->NodDr);
		free((*radacina)->masina.model);
		free((*radacina)->masina.numeSofer);
		free(*radacina);
		*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m = {0,0,0,NULL,NULL,0};
	if (radacina) {
		if (radacina->masina.id > id) {
			m = getMasinaByID(radacina->NodSt, id);
		}
		else if (radacina->masina.id < id) {
			m = getMasinaByID(radacina->NodDr, id);
		} else {
			m = radacina->masina;
			// vom face un deep copy asa ca exercitiu
			m.model = malloc((strlen(radacina->masina.model) + 1) * sizeof(char));
			strcpy(m.model, radacina->masina.model);
			m.numeSofer = malloc((strlen(radacina->masina.numeSofer) + 1) * sizeof(char));
			strcpy(m.numeSofer, radacina->masina.numeSofer);
		}
	}
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina) {
		int nrNoduriSt = determinaNumarNoduri(radacina->NodSt);
		int nrNoduriDr = determinaNumarNoduri(radacina->NodDr);
		return 1 + nrNoduriSt + nrNoduriDr;
	}
	else {
		return 0;
	}
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina) {
		int maxSt = calculeazaInaltimeArbore(radacina->NodSt);
		int maxDr = calculeazaInaltimeArbore(radacina->NodDr);
		return 1 + max(maxSt,maxDr);
	}
	else {
		return 0;
	}
}

float calculeazaPretTotal(Nod* radacina) {
	if (radacina) {
		float sumStanga = calculeazaPretTotal(radacina->NodSt);
		float sumDreapta = calculeazaPretTotal(radacina->NodDr);
		return radacina->masina.pret + sumStanga + sumDreapta;
	}
	else {
		return 0;
	}
}

float calculeazaPretulMasinilorUnuiSofer(Nod* radacina, const char* numeSofer) {
	if (radacina) {
		float st = calculeazaPretulMasinilorUnuiSofer(radacina->NodSt, numeSofer);
		float dr = calculeazaPretulMasinilorUnuiSofer(radacina->NodDr, numeSofer);
		if (strcmp(radacina->masina.numeSofer, numeSofer) == 0) {
			return radacina->masina.pret + st + dr;
		}
		return st + dr;
	}
}

int main() {
	Nod* arbore = citireArboreDeMasiniDinFisier("masiniArbore.txt");
	afisareMasinaArboreSDR(arbore);
	return 0;
}