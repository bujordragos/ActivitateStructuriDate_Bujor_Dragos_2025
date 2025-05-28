#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct BiletDeAutobuz { // B si D
    int id;
    int durata;
    float pret;
    char* destinatie;
};

typedef struct BiletDeAutobuz Bilet;

Bilet citesteBilet() { 
    Bilet b;
    char buffer[100];

    printf("Id: ");
    scanf("%d", &b.id);

    printf("Durata: ");
    scanf("%d", &b.durata);

    printf("Pret: ");
    scanf("%f", &b.pret);

    getchar();

    printf("Destinatie: ");
    gets_s(buffer, sizeof(buffer));

    b.destinatie = (char*)malloc(strlen(buffer) + 1);
    strcpy(b.destinatie, buffer);

    return b;
}

Bilet initBilet(int id, int durata, float pret, const char* destinatie) {
    Bilet b;
    b.id = id;
    b.durata = durata;
    b.pret = pret;
    b.destinatie = (char*)malloc(strlen(destinatie) + 1);
    strcpy(b.destinatie, destinatie);
    return b;
}

void pretPerDurata(Bilet b) {
    float pretPerTimp = b.pret / b.durata;
    printf("Pret per km: %.2f\n", pretPerTimp);
}

void updatePret(Bilet* b, float pret) {
    b->pret = pret;
    printf("Pretul a fost actualizat\n");
}

void afisareBilet(Bilet b) {
    printf("\n");
    printf("Id: %d\n", b.id);
    printf("Durata: %d\n", b.durata);
    printf("Pret: %.2f\n", b.pret);
    printf("Destinatie: %s\n", b.destinatie);
    printf("\n");
}

void elibereazaBilet(Bilet* b) {
    if (b->destinatie != NULL) {
        free(b->destinatie);
        b->destinatie = NULL;
    }
}

void afiseazaVectorBilete(Bilet* vector, int dimensiune) {
    printf("\nVector de bilete: \n");
    for (int i = 0; i < dimensiune; i++) {
        printf("Biletul %d:\n", i + 1);
        afisareBilet(vector[i]);
    }
    printf("\n");
}

Bilet* copiazaBiletePretMic(Bilet* vector, int dimensiune, int* dimensiuneNoua) {
    *dimensiuneNoua = 0;
    for (int i = 0; i < dimensiune; i++) {
        if (vector[i].pret < 50) {
            (*dimensiuneNoua)++;
        }
    }

    if (*dimensiuneNoua == 0) {
        return NULL;
    }

    Bilet* rezultat = (Bilet*)malloc(*dimensiuneNoua * sizeof(Bilet));
    if (rezultat == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < dimensiune; i++) {
        if (vector[i].pret < 50) {
            rezultat[index] = initBilet(vector[i].id, vector[i].durata, vector[i].pret, vector[i].destinatie);
            index++;
        }
    }

    return rezultat;
}

Bilet* mutaBileteDurataLunga(Bilet* vector, int* dimensiune) {
    int dimensiuneNoua = 0;

    for (int i = 0; i < *dimensiune; i++) {
        if (vector[i].durata > 60) {
            dimensiuneNoua++;
        }
    }

    if (dimensiuneNoua == 0) {
        return NULL;
    }

    Bilet* rezultat = (Bilet*)malloc(dimensiuneNoua * sizeof(Bilet));
    if (rezultat == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return NULL;
    }

    int indexRezultat = 0;
    int indexOriginal = 0;

    for (int i = 0; i < *dimensiune; i++) {
        if (vector[i].durata > 60) {
            rezultat[indexRezultat] = vector[i];
            indexRezultat++;
        }
        else {
            if (i != indexOriginal) {
                vector[indexOriginal] = vector[i];
            }
            indexOriginal++;
        }
    }

    *dimensiune = indexOriginal;

    return rezultat;
}

Bilet* concateneazaVectori(Bilet* v1, int dim1, Bilet* v2, int dim2, int* dimRezultat) {
    *dimRezultat = dim1 + dim2;

    Bilet* rezultat = (Bilet*)malloc(*dimRezultat * sizeof(Bilet));
    if (rezultat == NULL) {
        printf("Eroare la alocarea memoriei!\n");
        return NULL;
    }

    for (int i = 0; i < dim1; i++) {
        rezultat[i] = initBilet(v1[i].id, v1[i].durata, v1[i].pret, v1[i].destinatie);
    }

    for (int i = 0; i < dim2; i++) {
        rezultat[dim1 + i] = initBilet(v2[i].id, v2[i].durata, v2[i].pret, v2[i].destinatie);
    }

    return rezultat;
}

int main() {

    int dimensiune = 5;
    Bilet* vectorBilete = (Bilet*)malloc(dimensiune * sizeof(Bilet));

    vectorBilete[0] = initBilet(1, 30, 20.5, "Gara");
    vectorBilete[1] = initBilet(2, 45, 35.0, "Aeroport");
    vectorBilete[2] = initBilet(3, 75, 60.5, "Universitate");
    vectorBilete[3] = initBilet(4, 90, 45.0, "Piata Centrala");
    vectorBilete[4] = initBilet(5, 25, 15.0, "Parc");

    printf("Vectorul initial de bilete:\n");
    afiseazaVectorBilete(vectorBilete, dimensiune);

    int dimensiuneCopiate = 0;
    Bilet* vectorCopiat = copiazaBiletePretMic(vectorBilete, dimensiune, &dimensiuneCopiate);
    printf("\nBilete cu pret mai mic de 50:\n");
    afiseazaVectorBilete(vectorCopiat, dimensiuneCopiate);

    int dimensiuneInitiala = dimensiune;
    Bilet* vectorMutat = mutaBileteDurataLunga(vectorBilete, &dimensiune);
    printf("\nBilete cu durata mai mare de 60 (mutate):\n");
    afiseazaVectorBilete(vectorMutat, dimensiuneInitiala - dimensiune);

    printf("\nVectorul ramas dupa mutare:\n");
    afiseazaVectorBilete(vectorBilete, dimensiune);

    int dimensiuneConcatenat = 0;
    Bilet* vectorConcatenat = concateneazaVectori(vectorBilete, dimensiune,
        vectorMutat, dimensiuneInitiala - dimensiune, &dimensiuneConcatenat);
    printf("\nVector rezultat din concatenare:\n");
    afiseazaVectorBilete(vectorConcatenat, dimensiuneConcatenat);

    for (int i = 0; i < dimensiune; i++) {
        elibereazaBilet(&vectorBilete[i]);
    }
    free(vectorBilete);

    for (int i = 0; i < dimensiuneCopiate; i++) {
        elibereazaBilet(&vectorCopiat[i]);
    }
    free(vectorCopiat);

    for (int i = 0; i < dimensiuneInitiala - dimensiune; i++) {
        elibereazaBilet(&vectorMutat[i]);
    }
    free(vectorMutat);

    for (int i = 0; i < dimensiuneConcatenat; i++) {
        elibereazaBilet(&vectorConcatenat[i]);
    }
    free(vectorConcatenat);

    return 0;
}