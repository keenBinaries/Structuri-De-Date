#include <stdio.h>
#include <memory>

// Definire structuri
struct Produs
{
	int id;
	const char* denumire;
	float pret;
};

struct Nod
{
	// Informatia nodului, informatia
	// este tinuta static
	Produs info;

	// Legaturi
	Nod* next;
	Nod* prev;
};

// Functii ajutatoare articol
void AfiseazaProdus(Produs produs)
{
	printf("Produsul %s cu id-ul %d costa %5.2f lei.\n", produs.denumire, produs.id, produs.pret);
}

void CopiazaProdus(Produs sursa, Produs& destinatie)
{
	destinatie.id = sursa.id;
	destinatie.pret = sursa.pret;

	destinatie.denumire = (char*)malloc(strlen(sursa.denumire));
	strcpy((char*)destinatie.denumire, sursa.denumire);
}

void PopuleazaProdus(Produs& produs, int id, const char* denumire, float pret)
{
	produs.id = id;
	produs.pret = pret;

	produs.denumire = (char*)malloc(strlen(denumire));
	strcpy((char*)produs.denumire, denumire);
}

Produs InitializeazaProdus(int id, const char* denumire, float pret)
{
	Produs produs;

	produs.id = id;
	produs.pret = pret;

	produs.denumire = (char*)malloc(strlen(denumire));
	strcpy((char*)produs.denumire, denumire);

	return produs;
}

// Functii structura
void Afisare(Nod* cap)
{
	while (cap)
	{
		AfiseazaProdus(cap->info);
		cap = cap->next;
	}
}

Nod* InsereazaLaSfarsit(Nod* cap, Produs nou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = nou; // assignam produsul nodului

	// Initializam legaturile cu null
	nodNou->next = NULL;
	nodNou->prev = NULL;

	if (cap == NULL)
	{
		cap = nodNou;
	}
	else
	{
		Nod* tmp = cap;

		while (tmp->next)
			tmp = tmp->next;

		// Creem legaturile la introducere
		tmp->next = nodNou;
		nodNou->prev = tmp;
	}

	return cap;
}

// De data trecuta
Nod* InserareDupaPret(Nod* cap, Produs nou, float pret)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = nou;

	nodNou->next = NULL;
	nodNou->prev = NULL;

	Nod* tmp = cap;
	while (tmp->next)
	{
		if (tmp->next->info.pret <= pret)
			tmp = tmp->next;
		else
		{
			// introducem in fata nodului cu pretul mai mare 
			// sau introducem dupa cel cu cel mai mic

			nodNou->next = tmp;
			nodNou->prev = tmp->prev;

			tmp->prev->next = nodNou;
			tmp->prev = nodNou;

			return cap;
		}
	}
}

Nod* InserareLaInceput(Nod* cap, Produs nou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = nou;

	nodNou->prev = NULL;
	nodNou->next = cap;

	cap->prev = nodNou;

	return nodNou;
}

void Sterge(Nod* cap)
{
	while (cap)
	{
		// conditie

		Nod* tmp = cap;
		cap = cap->next;

		free((char*)tmp->info.denumire);
		free(tmp);
	}
}

int main()
{

	// Declarare si asignare produs
	Produs a;

	a.id = 1;
	a.denumire = "Gogoasa";
	a.pret = 2;

	// AfiseazaProdus(a);

	// Declarare si copiere implicita
	// Este posibila dar este recomandat s-o evitam
	Produs b = a;


	// AfiseazaProdus(b);

	Produs c;
	PopuleazaProdus(c, 2, "Carte", 20);
	// AfiseazaProdus(c);

	Produs d = InitializeazaProdus(3, "Aragaz", 30);

	// Initializare lista,
	// primul nod este null.
	Nod* cap = NULL;

	cap = InsereazaLaSfarsit(cap, a);
	cap = InsereazaLaSfarsit(cap, b);
	cap = InsereazaLaSfarsit(cap, c);
	cap = InsereazaLaSfarsit(cap, d);


	Produs e = InitializeazaProdus(4, "Pix", 1);
	cap = InserareLaInceput(cap, e);

	Produs f = InitializeazaProdus(5, "Creion", 10);
	cap = InserareDupaPret(cap, f, 2);

	Afisare(cap);
}