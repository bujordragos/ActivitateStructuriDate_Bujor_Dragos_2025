#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraCursaAeriana {
    char* cod;
    char* destinatie;
    char* dataPlecare;
    char* oraPlecare;
    char* statusCursa;
};
typedef struct StructuraCursaAeriana CursaAeriana;

struct Nod {
    CursaAeriana info;
    struct Nod* next;
};
typedef struct Nod Nod;

CursaAeriana initializareCursa(const char* cod, const char* destinatie, const char* dataPlecare, const char* oraPlecare, const char* statusCursa) {
    CursaAeriana ca;
    ca.cod = (char*)malloc(strlen(cod) + 1);
    strcpy(ca.cod, cod);
    ca.destinatie = (char*)malloc(strlen(destinatie) + 1);
    strcpy(ca.destinatie, destinatie);
    ca.dataPlecare = (char*)malloc(strlen(dataPlecare) + 1);
    strcpy(ca.dataPlecare, dataPlecare);
    ca.oraPlecare = (char*)malloc(strlen(oraPlecare) + 1);
    strcpy(ca.oraPlecare, oraPlecare);
    ca.statusCursa = (char*)malloc(strlen(statusCursa) + 1);
    strcpy(ca.statusCursa, statusCursa);
    return ca;
}

void afisareCursa(CursaAeriana ca) {
    printf("Cod: %s\n", ca.cod);
    printf("Destinatie: %s\n", ca.destinatie);
    printf("Data Plecare: %s\n", ca.dataPlecare);
    printf("Ora Plecare: %s\n", ca.oraPlecare);
    printf("Status Cursa: %s\n", ca.statusCursa);
}

void afisareListaCurse(Nod* cap) {
    while (cap) {
        afisareCursa(cap->info);
        printf("\n");
        cap = cap->next;
    }
}

void adaugaCursaInLista(Nod** cap, CursaAeriana ca) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = ca;
    nou->next = NULL;

    if (*cap == NULL) {
        *cap = nou;
    }
    else {
        Nod* temp = *cap;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nou;
    }
}

CursaAeriana citireCursaDinFisier(FILE* file) {
    CursaAeriana ca;
    char buffer[256];
    char separator[] = ",\n";

    fgets(buffer, 256, file);

    char* token = strtok(buffer, separator);
    ca.cod = (char*)malloc(strlen(token) + 1);
    strcpy(ca.cod, token);

    token = strtok(NULL, separator);
    ca.destinatie = (char*)malloc(strlen(token) + 1);
    strcpy(ca.destinatie, token);

    token = strtok(NULL, separator);
    ca.dataPlecare = (char*)malloc(strlen(token) + 1);
    strcpy(ca.dataPlecare, token);

    token = strtok(NULL, separator);
    ca.oraPlecare = (char*)malloc(strlen(token) + 1);
    strcpy(ca.oraPlecare, token);

    token = strtok(NULL, separator);
    ca.statusCursa = (char*)malloc(strlen(token) + 1);
    strcpy(ca.statusCursa, token);

    return ca;
}

Nod* citireListaCurseDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    Nod* cap = NULL;
    if (f == NULL) {
        printf("Eroare la deschiderea fisierului %s\n", numeFisier);
        return NULL;
    }
    while (!feof(f)) {
        CursaAeriana ca = citireCursaDinFisier(f);
        if (ca.cod != NULL) {
            adaugaCursaInLista(&cap, ca);
        }
        else {
            free(ca.cod);
            free(ca.destinatie);
            free(ca.dataPlecare);
            free(ca.oraPlecare);
            free(ca.statusCursa);
        }
    }
    fclose(f);
    return cap;
}

void dezalocareCursa(CursaAeriana* ca) {
    free(ca->cod);
    ca->cod = NULL;
    free(ca->destinatie);
    ca->destinatie = NULL;
    free(ca->dataPlecare);
    ca->dataPlecare = NULL;
    free(ca->oraPlecare);
    ca->oraPlecare = NULL;
    free(ca->statusCursa);
    ca->statusCursa = NULL;
}

void dezalocareLista(Nod** cap) {
    while (*cap) {
        Nod* temp = *cap;
        *cap = (*cap)->next;
        dezalocareCursa(&(temp->info));
        free(temp);
    }
    *cap = NULL;
}

void eliminaCurseCuStatus(Nod** cap, const char* status) {
    Nod* curent = *cap;
    Nod* precedent = NULL;

    while (curent != NULL) {
        if (strcmp(curent->info.statusCursa, status) == 0) {
            Nod* temp = curent;
            if (precedent == NULL) {
                *cap = curent->next;
                curent = *cap;
            }
            else {
                precedent->next = curent->next;
                curent = curent->next;
            }
            dezalocareCursa(&(temp->info));
            free(temp);
        }
        else {
            precedent = curent;
            curent = curent->next;
        }
    }
}

void sorteazaListaDupaCod(Nod** cap) {
    if (*cap == NULL || (*cap)->next == NULL) {
        return;
    }

    int sortat;
    Nod* ptr1;
    Nod* lptr = NULL;

    do {
        sortat = 0;
        ptr1 = *cap;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->info.cod, ptr1->next->info.cod) > 0) {
                CursaAeriana temp = ptr1->info;
                ptr1->info = ptr1->next->info;
                ptr1->next->info = temp;
                sortat = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (sortat);
}


int main() {
    Nod* listaCurse = NULL;

    listaCurse = citireListaCurseDinFisier("Pregatire_Test_si_Examen\\curse.txt");

    printf("Lista initiala:\n");
    afisareListaCurse(listaCurse);
    printf("--------------------\n");

    char statusDeEliminat[] = "Anulat";
    eliminaCurseCuStatus(&listaCurse, statusDeEliminat);
    printf("Lista dupa eliminarea curselor cu status '%s':\n", statusDeEliminat);
    afisareListaCurse(listaCurse);
    printf("--------------------\n");

    sorteazaListaDupaCod(&listaCurse);
    printf("Lista sortata dupa cod:\n");
    afisareListaCurse(listaCurse);
    printf("--------------------\n");

    dezalocareLista(&listaCurse);
    printf("Lista a fost dezalocata.\n");
    if (listaCurse == NULL) {
        printf("Dezalocare reusita.\n");
    }
    else {
        printf("Dezalocare esuata.\n");
    }


    return 0;
}