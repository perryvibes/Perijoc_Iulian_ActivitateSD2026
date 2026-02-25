#include<stdio.h>
#include<malloc.h>

struct Film {
	int id;
	int durata;
	char* denumire;
	float buget;
	char varstaMinima;

};
struct Film initializare(int _id, int _durata, char* _denumire, float _buget, char _varstaMin) {

	struct Film s;
	s.id = _id;
	s.durata = _durata;
	s.denumire = malloc((sizeof(char) * strlen(_denumire)) + 1);
	strcpy(s.denumire, _denumire);
	s.buget = _buget;
	s.varstaMinima = _varstaMin;

	return s;
}

struct Film copyFilm(struct Film s) {
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}

void afisare(struct Film s) {

	printf("Id: %d\n", s.id);
	printf("Nume: %s\n", s.denumire);
	printf("Durata: %d\n", s.durata);
	printf("Buget: %.2f\n", s.buget);
	printf("Varsta minima: %d\n", s.varstaMinima);

}

void afisareVector(struct Film* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++) {
		afisare(vector[i]);
		printf("\n");
	}
}

struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {
	//copiem intr-un vector nou pe care ii vom returna primele nrElementeCopiate
	struct Film* vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0; i < nrElementeCopiate; i++) {
		vectorNou[i] = copyFilm(vector[i]);
	}
	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; i++) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	//parametrul prag poate fi modificat in functie de 
	// tipul atributului ales pentru a indeplini o conditie
	//este creat un nou vector cu elementele care indeplinesc acea conditie
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget < bugetMaxim) {
			(*dimensiune)++;
		}
	}
	*vectorNou = malloc((*dimensiune) * sizeof(struct Film));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget < bugetMaxim) {
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}
}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* numeCautat) {
	//trebuie cautat elementul care indeplineste o conditie
	//dupa atributul de tip char*. Acesta este returnat.
	struct Film s;
	s.id = -1;
	s.denumire = NULL;

	for (int i = 0; i < nrElemente; i++) {
		if (!strcmp(vector[i].denumire, numeCautat)) return vector[i];
	}
	return s;
}



int main() {

	struct Film f1 = initializare(1, 120, "Don't look up", 60, 16);
	afisare(f1);

	printf("\n----------------------------------------------------\n");

	int nrFilme = 3;

	struct Film* filme = malloc(nrFilme * sizeof(struct Film));

	filme[0] = f1;

	*(filme + 1) = initializare(2, 100, "Interstellar", 30.5, 16);

	filme[2] = initializare(3, 90, "Fight Club", 20, 16);

	afisareVector(filme, nrFilme);

	printf("\n----------------------------------------------------\n");

	int nrFilmeCopiate = 2;
	struct Film* vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);

	printf("\nElemente copiate: \n\n");

	afisareVector(vectorNou, nrFilmeCopiate);

	dezalocare(&vectorNou, &nrFilmeCopiate);

	printf("\n----------------------------------------------------\n");

	struct Film* vectorIeftin;
	float prag = 50;
	int dimIeftin;
	copiazaAnumiteElemente(filme, nrFilme, prag, &vectorIeftin, &dimIeftin);
	afisareVector(vectorIeftin, dimIeftin);

	printf("\n----------------------------------------------------\n");

	afisare(getPrimulElementConditionat(filme, nrFilme, "Interstellar"));

	dezalocare(&filme, &nrFilme);

	printf("\n----------------------------------------------------\n");

	return 0;
}