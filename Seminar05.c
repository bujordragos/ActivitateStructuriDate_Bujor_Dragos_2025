#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct StructuraMasina {
    int id;
    int nrUsi;
    float pret;
    char* model;
    char* numeSofer;
    unsigned char serie;
};
typedef struct StructuraMasina Masina;

struct Nod {
    Masina info;
    struct Nod* next;
    struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
    Nod* inceput;
    Nod* final;
};
typedef struct ListaDubla Lista;

Masina citireMasinaDinFisier(FILE* file) {
    char buffer[100];
    char sep[3] = ",\n";
    fgets(buffer, 100, file);
    char* aux;
    Masina m1;
    aux = strtok(buffer, sep);
    m1.id = atoi(aux);
    m1.nrUsi = atoi(strtok(NULL, sep));
    m1.pret = atof(strtok(NULL, sep));
    aux = strtok(NULL, sep);
    m1.model = malloc(strlen(aux) + 1);
    strcpy(m1.model, aux);
    aux = strtok(NULL, sep);
    m1.numeSofer = malloc(strlen(aux) + 1);
    strcpy(m1.numeSofer, aux);
    m1.serie = *strtok(NULL, sep);
    return m1;
}

void afisareMasina(Masina masina) {
    printf("Id: %d\n", masina.id);
    printf("Nr. usi : %d\n", masina.nrUsi);
    printf("Pret: %.2f\n", masina.pret);
    printf("Model: %s\n", masina.model);
    printf("Nume sofer: %s\n", masina.numeSofer);
    printf("Serie: %c\n\n", masina.serie);
}

void afisareListaMasini(Lista lis) {
    Nod* p = lis.inceput;
    while (p)
    {
        afisareMasina(p->info);
        p = p->next;
    }
}

void adaugaMasinaInLista(Lista* lis, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->next = NULL;
    nou->prev = lis->final;
    if (lis->final)
    {
        lis->final->next = nou;
    }
    else
    {
        lis->inceput = nou;
    }
    lis->final = nou;
}

void adaugaLaInceputInLista(Lista* lis, Masina masinaNoua) {
    Nod* nou = (Nod*)malloc(sizeof(Nod));
    nou->info = masinaNoua;
    nou->prev = NULL;
    nou->next = lis->inceput;

    if (lis->inceput) {
        lis->inceput->prev = nou;
    }
    else {
        lis->final = nou;
    }

    lis->inceput = nou;
}

Lista citireLDMasiniDinFisier(const char* numeFisier) {
    FILE* f = fopen(numeFisier, "r");
    Lista lis;
    lis.final = NULL;
    lis.inceput = NULL;

    if (f == NULL) {
        printf("Eroare la deschiderea fisierului!\n");
        return lis;
    }

    while (!feof(f))
    {
        Masina m = citireMasinaDinFisier(f);
        adaugaMasinaInLista(&lis, m);
    }
    fclose(f);
    return lis;
}

void dezalocareLDMasini(Lista* list) {
    while (list->inceput)
    {
        if (list->inceput->info.numeSofer) free(list->inceput->info.numeSofer);
        if (list->inceput->info.model) free(list->inceput->info.model);
        Nod* p = list->inceput;
        list->inceput = p->next;
        free(p);
    }
    list->final = NULL;
}

float calculeazaPretMediu(Lista lista) {
    if (lista.inceput == NULL) return 0;

    float sumaPret = 0;
    int nrMasini = 0;
    Nod* p = lista.inceput;

    while (p) {
        sumaPret += p->info.pret;
        nrMasini++;
        p = p->next;
    }

    return sumaPret / nrMasini;
}

void stergeMasinaDupaID(Lista* lista, int id) {
    Nod* p = lista->inceput;

    while (p) {
        if (p->info.id == id) {
            // Daca este primul nod
            if (p->prev == NULL) {
                lista->inceput = p->next;
                if (lista->inceput) lista->inceput->prev = NULL;
                else lista->final = NULL;
            }
            // Daca este ultimul nod
            else if (p->next == NULL) {
                lista->final = p->prev;
                p->prev->next = NULL;
            }
            // Nod intermediar
            else {
                p->prev->next = p->next;
                p->next->prev = p->prev;
            }

            // Eliberare memorie
            free(p->info.model);
            free(p->info.numeSofer);
            free(p);
            return;
        }
        p = p->next;
    }
}

char* getNumeSoferMasinaScumpa(Lista lista) {

    Nod* p = lista.inceput;
    Nod* masinaScumpa = p;
    float pretMaxim = p->info.pret;
    if (lista.inceput) 
    {
        while (p) {
            if (p->info.pret > pretMaxim) {
                pretMaxim = p->info.pret;
                masinaScumpa = p;
            }
            p = p->next;
        }
        char* nume = malloc(strlen(masinaScumpa->info.numeSofer) + 1);
        strcpy(nume, masinaScumpa->info.numeSofer);
        return nume;
    }
}

void afisareInvers(Lista* list) {
    Nod* p = list->final;
    while (p) {
        afisareMasina(p->info);
        p = p->prev;
    }
}

int main() {
    Lista listaMasini = citireLDMasiniDinFisier("masini.txt");


	stergeMasinaDupaID(&listaMasini, 2);
    printf("Lista initiala de masini:\n");
    afisareListaMasini(listaMasini);

    printf("Pret mediu: %.2f\n", calculeazaPretMediu(listaMasini));

    printf("Soferul masinii cele mai scumpe: %s\n", getNumeSoferMasinaScumpa(listaMasini));

    printf("Afisare inversa:\n");
    afisareInvers(&listaMasini);
	printf("Soferul cu masina cea mai scumpa: %s\n", getNumeSoferMasinaScumpa(listaMasini));

    dezalocareLDMasini(&listaMasini);

    return 0;
}