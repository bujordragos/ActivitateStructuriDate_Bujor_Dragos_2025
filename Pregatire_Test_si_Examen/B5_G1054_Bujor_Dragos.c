#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Implementati o aplicatie in limbajul C ce rezolva probleme de gestionare a cheilor unui proprietar

//1. Definiti structuraCheie ce contine: textGravar(char*), esteRezerva(char), greutate(float), definiti structurile necesare pentru lucrucu lista dublu inlantuita
//2. implementati functia de inserare a uneiChei intr-o Lista dublu inlantuita
//3. Creati o lista dubla cu cel putin 5 elemente de tip Cheie, apeland functia de inserare. Informatiile pentru cele 5 obiecte de tipCheie le cititi intr-un fisier text
//4. Implementati functiile de traversare in ambele sensuri a structurii lista dublu inlantuita creata la punctul 2). Vor fi afisate in consola aplicatiei toate datele asociate structurii Cheie
//5. Implementati functia care returneaza textul gravat pe cheia cea mai usoara din lista dublu inlantuita primita ca parametru. rezultatul apelului se valideaza prin apelul functiei si afisarea rezultatului returnat in functia principala
//6. Implementati functia care returneaza numarul de chei de rezerva din lista dublu inlantuita primita ca parametru. Rezultatul apelului se valideaza prin apelul functiei si afisarea rezultatului returnat in functia principala
//7. Implementati functia care cauta si returneaza(deep copy) o Cheie din lista dublu inlantuita, primind textul gravat pe aceasta.Daca sunt mai multe o va returna pe prima. Apelati functia in main()
//8. Trebuie sa eliberati toata memoria alocata in HEAP. sa nu uitati ca ati facut deep-copy la cerinta 6.


struct Cheie {
	char* textGravat;
	char esteRezerva;
	float greutate;
};
typedef struct Cheie Cheie;

struct Nod {
	Cheie cheie;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

Cheie citireCheieDinFisier(FILE* f) {
	char buffer[100];
	char sep[] = ",\n";
	fgets(buffer, 100, f);
	Cheie c;
	char* aux = strtok(buffer, sep);
	c.textGravat = (char*)malloc(strlen(aux) + 1);
	strcpy(c.textGravat, aux);
	c.esteRezerva = strtok(NULL, sep)[0];
	c.greutate = atof(strtok(NULL, sep));

	return c;
}

void afisareCheie(Cheie c) {
	printf("Text: %s\n", c.textGravat);
	printf("Rezerva: %c\n", c.esteRezerva);
	printf("Greutate: %.2f\n\n", c.greutate);
}

void inserareInListaDubla(ListaDubla* lista, Cheie c) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->cheie = c;
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

ListaDubla citireListaDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {
		inserareInListaDubla(&lista, citireCheieDinFisier(f));
	}
	fclose(f);
	return lista;

}

void afisareDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareCheie(p->cheie);
		p = p->next;
	}
}

void afisareDeLaSfarsit(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareCheie(p->cheie);
		p = p->prev;
	}
}

char* getTextCheieUsoara(ListaDubla lista) {
	if (lista.first == NULL) {
		return NULL;
	}
	Nod* aux = lista.first;
	Nod* usoara = aux;
	aux = aux->next;

	while (aux) {
		if (aux->cheie.greutate < usoara->cheie.greutate) {
			usoara = aux;
		}
		aux = aux->next;
	}

	char* text = (char*)malloc(strlen(usoara->cheie.textGravat) + 1);
	strcpy(text, usoara->cheie.textGravat);

	return text;
}

int numaraCheiRezerva(ListaDubla lista) {
	int count = 0;
	Nod* p = lista.first;
	while (p) {
		if (p->cheie.esteRezerva == 'Y' || p->cheie.esteRezerva == 'y') {
			count++;
		}
		p = p->next;
	}
	return count;
}

Cheie cautaCheieDupaText(ListaDubla lista, const char* text) {
	Nod* p = lista.first;
	while (p) {
		if (strcmp(p->cheie.textGravat, text) == 0) {
			Cheie copie;
			copie.textGravat = (char*)malloc(strlen(p->cheie.textGravat) + 1);
			strcpy(copie.textGravat, p->cheie.textGravat);
			copie.esteRezerva = p->cheie.esteRezerva;
			copie.greutate = p->cheie.greutate;
			return copie;
		}
		p = p->next;
	}

	Cheie c;
	c.textGravat = NULL;
	c.esteRezerva = 'N';
	c.greutate = 0;
	return c;
}



void dezalocareLista(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (aux->cheie.textGravat) {
			free(aux->cheie.textGravat);
		}
		free(aux);
	}
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}



int main() {
	ListaDubla lista = citireListaDinFisier("B5_G1054_Bujor_Dragos.txt");

	afisareDeLaInceput(lista);
	afisareDeLaSfarsit(lista);

	char* text = getTextCheieUsoara(lista);
	printf("Textul celei mai usoare chei: %s\n", text);

	if (text) {
		free(text);
	}
	int nrRezerva = numaraCheiRezerva(lista);
	printf("Numarul de chei de rezerva: %d\n", nrRezerva);

	Cheie c = cautaCheieDupaText(lista, "ABC");
	printf("Cheie gasita:\n");
	afisareCheie(c);
	free(c.textGravat);

	dezalocareLista(&lista);

	return 0;

}

































