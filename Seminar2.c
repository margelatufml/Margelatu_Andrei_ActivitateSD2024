#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

struct Calculator {
	char* serie;
	float pret;
	int nrPorturi;
};

struct Calculator initializare(const char* serie, float pret, int nrporturi) {
	struct Calculator c;
	c.serie = (char*)malloc(sizeof(char) * (strlen(serie) + 1));
	c.nrPorturi = nrporturi;
	c.pret = pret;
	return c;
}

void afisareCalculator(struct Calculator c) {
	printf("Calculatorul cu seria %s, costa %5.2f si are %d porturi\n", c.serie, c.pret, c.nrPorturi);
}
void afisareVectorCalculatoare(struct Calculator* vector, int nrCalculatoare) {
	if (nrCalculatoare > 0 && vector != NULL) {
		for (int i = 0; i < nrCalculatoare; i++) {
			afisareCalculator(vector[i]);
		}
	}
}
struct Calculator* copiazaNCalculatoare(struct Calculator* calculatoare, int nrCalculatoare,int nrCalculatoareCopiate) {
	struct Calculator* copiate = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoareCopiate);
	for (int i = 0; i < nrCalculatoareCopiate; i++) {
		copiate[i] = calculatoare[i];
		copiate[i].serie = (char*)malloc(sizeof(char) * (1 + strlen(calculatoare[i].serie)));
		strcpy(copiate[i].serie, calculatoare[i].serie);
	}
}


struct Calculator* copiazaCalculatoareCuMultePortri(struct Calculator* calculatoare,int nrcalculatoare, int nrPragPorturi,int* nrCalculatoarePorturi) {
	*nrCalculatoarePorturi = 0;
	for (int i = 0; i < nrcalculatoare; i++) {
		if (calculatoare[i].nrPorturi >= nrPragPorturi) {
			(*nrCalculatoarePorturi)++;
		}
	}
	struct  Calculator* v = (struct Calculator*)malloc(sizeof(struct Calculator) * (*nrCalculatoarePorturi));
	int k = 0;
	for (int i = 0; i < nrcalculatoare; i++) {
		if (calculatoare[i].nrPorturi > nrPragPorturi) {
			v[k++] = initializare(calculatoare[i].serie, calculatoare[i].pret, calculatoare[i].nrPorturi);
		
		}
	}
	return v;

}

int returnarepretdat(struct Calculator* calculatoare,float pret,int* nrcalculatoare) {
	
	*nrcalculatoare = 0;
	for (int i = 0; i < nrcalculatoare; i++) {
		if (calculatoare[i].pret == pret) {
			return &calculatoare[i];
			break;
		}
		else {
			(*nrcalculatoare)++;
		}
	}
 }

void dezalocare(struct Calculator** vector, int* dim) {
	for (int i = 0; i < dim; i++) {
		free((*vector)[i].serie);
	}
	free(*vector);
	*vector = NULL;
	*dim = 0;
}

void main() {
	int nrCalculatoare = 5;
	struct Calculator* calculatoare = (struct Calculator*)malloc(sizeof(struct Calculator) * nrCalculatoare);
	for (int i = 0; i < nrCalculatoare; i++) {
		calculatoare[i] = initializare("1234567890", i * 20 + 10, i + 1);
	}
	afisareVectorCalculatoare(calculatoare, nrCalculatoare);

	int nrCalculatoarecopiate = 3;

	struct Calculator* calculatoareCopiate  = copiazaNCalculatoare(calculatoare, nrCalculatoare, nrCalculatoarecopiate);

	printf("++++++++++++++++++++++++++++++++++++++++++++");

	afisareVectorCalculatoare(calculatoareCopiate, nrCalculatoarecopiate);
	int calculatoarecumulteporturi = 3;
	
	struct Calculator*
		calculatoarePorturi = copiazaCalculatoareCuMultePortri(calculatoare, nrCalculatoare, 3,&calculatoarecumulteporturi);

	printf("\n");
	afisareVectorCalculatoare(calculatoarePorturi, calculatoarecumulteporturi);


	dezalocare(&calculatoare, &nrCalculatoare);
}
