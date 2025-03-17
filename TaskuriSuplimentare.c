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

int main() {
    Bilet b = citesteBilet();
    afisareBilet(b);
    pretPerDurata(b);
    updatePret(&b, 100);
    afisareBilet(b);


    return 0;
}