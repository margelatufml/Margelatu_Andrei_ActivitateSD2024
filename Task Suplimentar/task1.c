#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include<malloc.h>


 struct MagazinAutomobile {
    int cod;
    char* marca;
    int nrModele;
    float* preturiModele;
};

 struct MagazinAutomobile citesteAutomobilMagazin() {
    struct  MagazinAutomobile mag;
     printf("Introduceti codul magazinului: ");
     scanf("%d", &mag.cod);

     mag.marca = malloc(50 * sizeof(char));
     printf("Introduceti marca automobilului: ");
     scanf("%s", mag.marca);

     printf("Introduceti numarul de modele: ");
     scanf("%d", &mag.nrModele);

     mag.preturiModele = malloc(mag.nrModele * sizeof(float));
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
     mag->marca = malloc(strlen(nouaMarca) + 1);
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



 int main() {
     // Citirea datelor magazinului
     struct MagazinAutomobile magazin = citesteAutomobilMagazin();

     // Afișarea datelor citite
     printf("Informatii initiale ale magazinului:\n");
     afiseazaAutomobilMagazin(magazin);

     // Calcularea și afișarea mediei prețurilor
     float mediePreturi = calculeazaMediaPreturi(magazin);
     printf("Media preturilor este: %.2f\n", mediePreturi);

     // Modificarea mărcii și afișarea noilor informații
     modificaMarca(&magazin, "MarcaNoua");
     printf("Informatii magazin dupa modificarea marcii:\n");
     afiseazaAutomobilMagazin(magazin);

     // Eliberarea memoriei alocate
     free(magazin.marca);
     free(magazin.preturiModele);

     return 0;
 }