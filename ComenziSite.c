#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Comanda {
	unsigned int id;
	char* data_lansare;
	char* data_livrare_programata;
	char* nume_client;
	float valoare_comanda;
};
typedef struct Comanda Comanda;

struct Nod {
	Comanda info;
	struct Nod* st;
	struct Nod* dr;
};
typedef struct Nod Nod;

void afisareComanda(Comanda c) {
	printf("id comanda %u\n", c.id);
	printf("data lansare %s\n", c.data_lansare);
	printf("data livrare %s\n", c.data_livrare_programata);
	printf("nume client %s\n", c.nume_client);
	printf("valoare %.2f\n\n", c.valoare_comanda);
}

Comanda citireComandaDinFisier(FILE* f) {
	Comanda c;
	char buffer[200];
	char sep[] = ",\n";

	fgets(buffer, 200, f);

	char* token = strtok(buffer, sep);
	c.id = (unsigned int)atoi(token);

	token = strtok(NULL, sep);
	c.data_lansare = (char*)malloc(strlen(token) + 1);
	strcpy(c.data_lansare, token);

	token = strtok(NULL, sep);
	c.data_livrare_programata = (char*)malloc(strlen(token) + 1);
	strcpy(c.data_livrare_programata, token);

	token = strtok(NULL, sep);
	c.nume_client = (char*)malloc(strlen(token) + 1);
	strcpy(c.nume_client, token);

	token = strtok(NULL, sep);
	c.valoare_comanda = atof(token);

	return c;
}

void adaugaInArbore(Nod** radacina, Comanda comanda) {
	if (*radacina == NULL) {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = comanda;
		nou->st = NULL;
		nou->dr = NULL;
		*radacina = nou;
	}
	else {
		if (comanda.id < (*radacina)->info.id) {
			adaugaInArbore(&((*radacina)->st), comanda);
		}
		else if (comanda.id > (*radacina)->info.id) {
			adaugaInArbore(&((*radacina)->dr), comanda);
		}
	}
}

Nod* citireArboreDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	if (f == NULL) {
		return NULL;
	}
	Nod* radacina = NULL;
	while (!feof(f)) {
		Comanda c = citireComandaDinFisier(f);
		adaugaInArbore(&radacina, c);
	}
	fclose(f);
	return radacina;
}

void afisarePostOrdine(Nod* radacina) {
	if (radacina) {
		afisarePostOrdine(radacina->st);
		afisarePostOrdine(radacina->dr);
		afisareComanda(radacina->info);
	}
}


Comanda cautaComandaDupaId(Nod* radacina, unsigned int id) {
	if (radacina == NULL) {
		Comanda c;
		c.id = 0;
		return c;
	}

	if (id < radacina->info.id) {
		return cautaComandaDupaId(radacina->st, id);
	}
	else if (id > radacina->info.id) {
		return cautaComandaDupaId(radacina->dr, id);
	}
	else {
		return radacina->info;
	}
}

float valoareMedie3Comenzi(Nod* radacina, unsigned int id1, unsigned int id2, unsigned int id3) {
	Comanda c1 = cautaComandaDupaId(radacina, id1);
	Comanda c2 = cautaComandaDupaId(radacina, id2);
	Comanda c3 = cautaComandaDupaId(radacina, id3);

	float suma = 0;
	int count = 0;

	if (c1.id != 0) {
		suma += c1.valoare_comanda;
		count++;
	}
	if (c2.id != 0) {
		suma += c2.valoare_comanda;
		count++;
	}
	if (c3.id != 0) {
		suma += c3.valoare_comanda;
		count++;
	}

	if (count > 0) {
		return suma / count;
	}

	return 0;
}


void dezalocareArbore(Nod** radacina) {
	if (*radacina) {
		dezalocareArbore(&((*radacina)->st));
		dezalocareArbore(&((*radacina)->dr));

		free((*radacina)->info.data_lansare);
		free((*radacina)->info.data_livrare_programata);
		free((*radacina)->info.nume_client);
		free(*radacina);

		*radacina = NULL;
	}
}


int main() {
	Nod* arbore = citireArboreDinFisier("comenzi.txt");

	printf("uite arborele afisat in postordine\n\n");
	afisarePostOrdine(arbore);

	printf("\nacum calculam valoarea medie pentru trei comenzi\n");
	unsigned int id1 = 101, id2 = 108, id3 = 110;
	float medie = valoareMedie3Comenzi(arbore, id1, id2, id3);
	printf("valoarea medie pentru comenzile cu id %u %u si %u este %.2f\n", id1, id2, id3, medie);

	dezalocareArbore(&arbore);

	printf("\nam eliberat toata memoria\n");

	return 0;
}