/*Acest fisier inca nu merge*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

struct Aeroport {
	int id;
	char* nume;
	int nrTerminale;

};
struct Aeroport* adaugaAeroport(struct Aeroport* vector, struct Aeroport aeroport,int* dimensiune) {
	struct Aeroport* copie = (struct Aeroport*)malloc(sizeof(struct Aeroport) * ((*dimensiune) + 1));

	copie[(*dimensiune)] = aeroport;

	for (int i = 0; i < (*dimensiune); i++) {
		copie[i] = vector[i];
	}
	if (vector != NULL) {
		free(vector);
	}
	(*dimensiune)++;
	return copie;
}
struct Aeroport* citireFisier(char* numeFisier, int* dim) {
	struct Aeroport* vectorAeroporturi;
	vectorAeroporturi = NULL;
	FILE* f = fopen(numeFisier, "r");

	if (f != NULL) {
		(*dim) = 0;
		char buffer[100];
		while (fgets(buffer, 99, f)!=NULL) {
			struct Aeroport aeroportbuffer;
			char delimitator[] = ",\n";
			char* token=strtok(buffer, ",\n");
			aeroportbuffer.id = atoi(token);
			token = strtok(NULL, delimitator);
			aeroportbuffer.nume = malloc(sizeof(char) * (strlen(token) + 1));
			strcpy(aeroportbuffer.nume, token);
			token = strtok(NULL, delimitator);
			aeroportbuffer.nrTerminale = atoi(token);

			adaugaAeroport(vectorAeroporturi, aeroportbuffer, dim);
		}	
	}
	else {
		printf("NU MERGE");
	}
	fclose(f);
	return vectorAeroporturi;
}

void afisareAeroport(struct Aeroport* aeroport) {
	printf("Aeroportul cu ID: %d cu numele: %s are %d terminale\n", aeroport->id,aeroport->nume,aeroport->nrTerminale);
}

void afisare(struct Aeroport* aeroporturi, int dim) {
	printf("AFISARE VECTOR:\n");
	for (int i = 0; i < dim; i++) {
		afisareAeroport(&aeroporturi[i]);
	}
}
/*void dezalocareVector(struct Aeroport** aeroporturi, int* dim) {
	for (int i = 0; i < (*dim); i++) {
		free(aeroporturi[i]->nume);
		free((*aeroporturi)[i]);
	}
	free(aeroporturi);
	(*aeroporturi) = NULL;
	(*dim) = 0;
}*/
struct Aeroport idCautat(struct Aeroport* aeroporturi, int dim, int id) {

}
void main() {

	int dimensiune = 3;

	struct Aeroport* aeroporturi= NULL;
	aeroporturi =citireFisier("fisier.txt", &dimensiune);
	afisare(aeroporturi, dimensiune);


}
