//#include<stdio.h>
//#include<stdlib.h>
//#include <string.h>
//#include <malloc.h>
//
//struct Haina {
//	int sku;
//	int stoc;
//	char* denumire;
//	float pret;
//	char marime;
//};
//
//struct Haina initializare(int _sku, int _stoc, char* _denumire, float _pret, char _marime) {
//	struct Haina h;
//	h.sku = _sku;
//	h.stoc = _stoc;
//	h.denumire = malloc((sizeof(char)*strlen(_denumire))+1);
//	strcpy_s(h.denumire, (sizeof(char) * strlen(_denumire)) + 1, _denumire);
//	h.pret = _pret;
//	h.marime = _marime;
//	return h;
//}
//
//void afisare(struct Haina h) {
//	printf("\nHaina (%d): %s", h.sku, h.denumire);
//	printf("\nStoc: %d", h.stoc);
//	printf("\nPret: %.2f", h.pret);
//	printf("\nMarime: %c", h.marime);
//}
//
//void modifica_Atribut(struct Haina* h) {
//	if (h->stoc < 20) {
//		h->pret *= 1.25;
//	}
//}
//
//void dezalocare(struct Haina* h) {
//	free(h->denumire);
//}
//
//int main() {
//
//	struct Haina h1 = initializare(2423, 24, "Jacheta Piele", 139.98, 'M');
//	afisare(h1);
//
//	printf("\n----------------------------------------------------\n");
//
//	struct Haina h2 = initializare(2141, 13, "Vesta TNF", 500.0, 'XL');
//	modifica_Atribut(&h2);
//	afisare(h2);
//
//	printf("\n----------------------------------------------------\n");
//
//	dezalocare(&h1);
//	dezalocare(&h2);
//
//	return 0;
//}