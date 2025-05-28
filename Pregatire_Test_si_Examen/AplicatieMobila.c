#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
Grupa: 10XX / (60 min)                                       Aprilie 2025

Implementati o aplicatie in limbajul C ce gestioneaza o lista de aplicatii
mobile disponibile intr-un magazin virtual.

1. Definiti structura AplicatieMobila ce contine: denumire (char*),
   marimeMB (float), nrDescarcari (int), anLansare (int).
   Implementati functiile necesare pentru a citi datele dintr-un fisier text
   (`aplicatii.txt`) si a initializa o lista simplu inlantuita cu cel putin
   5 aplicatii mobile (datele vor fi citite din fisier). Formatul fisierului
   este la alegerea voastra (ex: campuri separate prin virgula). Apelati
   aceasta initializare in `main` si afisati lista creata pentru validare. (2 p)

2. Implementati functia C care sterge din lista simpla nodul corespunzator
   unei aplicatii mobile avand o anumita denumire (denumirea va fi data ca
   parametru functiei). Functia se apeleaza in functia `main` pentru o
   denumire la alegere, existenta in fisierul de date. Se valideaza executia
   functiei prin afisarea listei ramase dupa stergere. (2 p)

3. Implementati functia C care identifica si returneaza (printr-o copie
   deep copy - alocand memorie noua inclusiv pentru sirul de caractere)
   aplicatia mobila cu cea mai mica marime in MB din lista. Functia se
   apeleaza in `main`, rezultatul (copia) se stocheaza intr-o variabila
   separata de tip AplicatieMobila si se afiseaza la consola pentru
   validare. (3 p)

4. Implementati si apelati functia C care dezaloca integral memoria ocupata
   de lista simplu inlantuita (inclusiv memoria alocata pentru campurile
   `char*` din fiecare nod). Asigurati-va ca se elibereaza si memoria ocupata
   de copia (deep copy) creata la punctul 3. Verificati la final ca
   pointerul la capul listei este NULL dupa dezalocare. (2 p)

*/

struct AplicatieMobila
{
	char* denumire;
	float marimeMB;
	int nrDescarcari;
	int anLansare;

};

typedef struct AplicatieMobila aplicatie;

struct Nod
{
	aplicatie aplicatie;
	Nod* next;
};
typedef struct Nod Nod;

aplicatie initializareAplicatie(const char* denumire, float marime, int descarcari, int anLansare)
{
	aplicatie a;
	a.denumire = (char*)malloc(strlen(denumire) + 1);
	strcpy(a.denumire, denumire);
	a.marimeMB = marime;
	a.nrDescarcari = descarcari;
	a.anLansare = anLansare;
	return a;
}

void afisareAplicatie(aplicatie a)
{
	printf("Denumirea aplicatiei este: %s\n", a.denumire);
	printf("Marimea: %f\n", a.marimeMB);
	printf("Nr descarcari: %d\n", a.nrDescarcari);
	printf("An lansare: %d\n", a.anLansare);
}

void afisareListaAplicatii(Nod* nod)
{
	while (nod)
	{
		afisareAplicatie(nod->aplicatie);
		print("\n");
		nod = nod->next;
	}
}

void adaugareAplicatieInLista(Nod** nod, aplicatie a)
{
	Nod* nou = (Nod*)malloc(sizeof(nod));
	nou->aplicatie = a;
	nou->next = NULL;

	if (*nod == NULL)
		*nod = nou;
	else
	{

	}
}