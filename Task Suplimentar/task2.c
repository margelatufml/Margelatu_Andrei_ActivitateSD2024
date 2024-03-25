#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<malloc.h>

struct MagazinAutomobile {
    int cod;
    char* marca;
    int nrModele;
    float* preturiModele;
};

struct MagazinAutomobile citesteAutomobilMagazin() {
    struct MagazinAutomobile mag;
    printf("Introduceti codul magazinului: ");
    scanf("%d", &mag.cod);

    mag.marca = (char*)malloc(50 * sizeof(char));
    printf("Introduceti marca automobilului: ");
    scanf("%s", mag.marca);

    printf("Introduceti numarul de modele: ");
    scanf("%d", &mag.nrModele);

    mag.preturiModele = (float*)malloc(mag.nrModele * sizeof(float));
    for (int i = 0; i < mag.nrModele; i++) {
        printf("Introduceti pretul modelului %d: ", i + 1);
        scanf("%f", &mag.preturiModele[i]);
    }
    return mag;
}

float calculeazaMediaPreturi(struct MagazinAutomobile mag) {
    float suma = 0;
    for (int i = 0; i < mag.nrModele; i++) {
        suma += mag.preturiModele[i];
    }
    return suma / mag.nrModele;
}

void modificaMarca(struct MagazinAutomobile* mag, char* nouaMarca) {
    free(mag->marca);
    mag->marca = (char*)malloc(strlen(nouaMarca) + 1);
    strcpy(mag->marca, nouaMarca);
}

void afiseazaAutomobilMagazin(struct MagazinAutomobile mag) {
    printf("Cod Magazin: %d\n", mag.cod);
    printf("Marca: %s\n", mag.marca);
    printf("Numar Modele: %d\n", mag.nrModele);
    for (int i = 0; i < mag.nrModele; i++) {
        printf("Pretul Modelului %d: %.2f\n", i + 1, mag.preturiModele[i]);
    }
}

struct MagazinAutomobile* creeazaVector(int n) {
    struct MagazinAutomobile* vector = (struct MagazinAutomobile*)malloc(n * sizeof(struct MagazinAutomobile));
    for (int i = 0; i < n; i++) {
        vector[i] = citesteAutomobilMagazin();
    }
    return vector;
}

struct MagazinAutomobile* filtreazaAutomobile(struct MagazinAutomobile* vector, int n, int* nouaDimensiune, float pragPret) {
    struct MagazinAutomobile* filtrat = (struct MagazinAutomobile*)malloc(n * sizeof(struct MagazinAutomobile));
    int j = 0;
    for (int i = 0; i < n; i++) {
        if (calculeazaMediaPreturi(vector[i]) < pragPret) {
            filtrat[j++] = vector[i];
        }
    }
    *nouaDimensiune = j;
    return filtrat;
}

struct MagazinAutomobile* concateneazaVectori(struct MagazinAutomobile* v1, int n1, struct MagazinAutomobile* v2, int n2) {
    struct MagazinAutomobile* rezultat = (struct MagazinAutomobile*)malloc((n1 + n2) * sizeof(struct MagazinAutomobile));
    for (int i = 0; i < n1; i++) {
        rezultat[i] = v1[i];
    }
    for (int i = 0; i < n2; i++) {
        rezultat[n1 + i] = v2[i];
    }
    return rezultat;
}

void afiseazaVector(struct MagazinAutomobile* vector, int n) {
    for (int i = 0; i < n; i++) {
        afiseazaAutomobilMagazin(vector[i]);
    }
}

int main() {
    int nrAutomobile = 5;
    struct MagazinAutomobile* magazine = creeazaVector(nrAutomobile);

    printf("Informatii initiale ale magazinului:\n");
    afiseazaVector(magazine, nrAutomobile);

    int nouaDimensiune;
    struct MagazinAutomobile* magazineFiltrate = filtreazaAutomobile(magazine, nrAutomobile, &nouaDimensiune, 1000.00);
    printf("Magazine filtrate:\n");
    afiseazaVector(magazineFiltrate, nouaDimensiune);

    // Eliberarea memoriei
    for (int i = 0; i < nrAutomobile; i++) {
        free(magazine[i].marca);
        free(magazine[i].preturiModele);
    }
    free(magazine);

    for (int i = 0; i < nouaDimensiune; i++) {
        free(magazineFiltrate[i].marca);
        free(magazineFiltrate[i].preturiModele);
    }
    free(magazineFiltrate);

    return 0;
}
