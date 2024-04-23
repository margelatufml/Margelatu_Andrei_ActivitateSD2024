#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct Elev Elev;
typedef struct Nod Nod;
struct Elev {
	int id;
	int nrMedii;
	float* medii;
};
struct Nod {
	Elev info;
	Nod* st;
	Nod* dr;
};
Elev citireElev(FILE* f) {
	Elev e;
	fscanf(f, "%d", &e.id);
	fscanf(f, "%d", &e.nrMedii);
	e.medii = (float*)malloc(sizeof(float)* e.nrMedii);
	for (int i = 1; i < e.medii;i++) {
		fscanf(f, "%f", &e.medii[i]);
	}
	return e;
}
void inserareArbore(Nod** radacina, Elev e) {

	if ((*radacina) != NULL) {
		if ((*radacina)->info.id > e.id) {
			inserareArbore(&((*radacina)->st), e);
		}
		else {
			inserareArbore(&((*radacina)->dr), e);

		}
	}
	else
	{
		Nod* nod = (Nod*)malloc(sizeof(Nod));
		nod->info = e;
		nod->st = NULL;
		nod->dr = NULL;


		*radacina = nod;
	}

}
Nod* citireFisier(char* numefisier) {
	Nod* nod = NULL;
	if (numefisier != NULL) {
		FILE* f = fopen(numefisier, "r");
		int nrElevi;;
		fscanf(f, "%d", &nrElevi);
		for (int i = 0; i < 6; i++) {
			Elev e = citireElev(f);
			inserareArbore(&nod, e);
		}
		fclose(f);
	
	}
	return nod;
}
void afisareElev(Elev e) {
	printf("Elevul cu numarul %d", e.id);
	for (int i = 0; i < e.nrMedii; i++) {
		printf("5.2f", e.medii[i]);
	}
	printf("\n");
}
void afisareInordine(Nod* arbore) {
	if (arbore != NULL) {
		afisareInordine(arbore->st);
		afisareElev(arbore->info);
		afisareInordine(arbore->dr);
	}
}

float calculeazaMedieElev(Elev e) {
	if (e.nrMedii) {
		float suma;
		for (int i = 0; i < e.nrMedii; i++) {
			suma += e.medii[i];
		}
		return suma / e.nrMedii;
	}
	return 0;
}

float calculareSumaNote(Nod* arbore,int* nrNote) {
	if (arbore != NULL) {
		float suma = 0;
		for (int i = 0; i < arbore->info.nrMedii; i++) {
			suma += arbore->info.medii[i];
		}
		float sumaStanga=calculareSumaNote(arbore->st, nrNote + arbore->info.nrMedii);
		float sumaDreapta = calculareSumaNote(arbore->st, nrNote + arbore->info.nrMedii);

		return sumaStanga + sumaDreapta;
	}
}
float calculareMedieGenerala(Nod* arbore) {
	int nrNote = 0;
	int suma=calculeazaSumaNote(arbore, &nrNote);
	return suma / nrNote;
}

void main() {
	Nod* radacina = NULL;
	radacina = citireFisier("Elevi.txt");
	afisareInordine(radacina);
	printf("Media este %5.2f", calculareMedieGenerala(radacina));

}
