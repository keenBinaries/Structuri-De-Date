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

Produs PopuleazaProdus(int id, const char* denumire, float pret)
{
	Produs produs;

	produs.id = id;
	produs.pret = pret;

	produs.denumire = (char*)malloc(strlen(denumire));
	strcpy((char*)produs.denumire, denumire);

	return produs;
}

// Functii ajutatoare articol
void AfiseazaProdus(Produs produs)
{
	printf("Produsul %s cu id-ul %d costa %5.2f lei.\n", produs.denumire, produs.id, produs.pret);
}

// Functii structura
void Afisare(Nod* cap)
{
	AfiseazaProdus(cap->info);

	Nod* tmp = cap->next;

	while (tmp)
	{
		if (tmp != cap)
		{
			AfiseazaProdus(tmp->info);
			tmp = tmp->next;
		}
		else
			return;
	}
}

Nod* InserareSfarsit(Nod* cap, Produs nou)
{
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = nou;

	nodNou->next = NULL;
	nodNou->prev = NULL;

	if (!cap)
	{
		cap = nodNou;
	}
	else
	{
		if (cap->prev)
		{
			nodNou->next = cap;
			nodNou->prev = cap->prev;

			cap->prev->next = nodNou;
			cap->prev = nodNou;
		}
		else
		{
			cap->prev = nodNou;
			cap->next = nodNou;

			nodNou->next = cap;
			nodNou->prev = cap;
		}
	}

	return cap;
}

Nod* StergerePrimulNod(Nod* cap)
{
	Nod* ult = cap->prev; // Referinta la ultimul element
	Nod* tmp = cap; // Referinta la cap

	cap = cap->next;

	ult->next = cap;
	cap->prev = ult;

	free(tmp);

	return cap;
}

Nod* StergereDupaId(Nod* cap, int id)
{
	if (cap->info.id == id)
	{
		cap = StergerePrimulNod(cap);
		return cap;
	}

	Nod* tmp = cap->next;

	while (tmp)
	{
		if (tmp != cap)
		{
			if (tmp->info.id != id)
				tmp = tmp->next;
			else
			{
				Nod* tmpNext = tmp->next;
				Nod* tmpPrev = tmp->prev;

				tmpNext->prev = tmpPrev;
				tmpPrev->next = tmpNext;

				free(tmp);

				return cap;
			}
		}
		else
		{
			return cap; // Nu facem nimic, lista a fost parcursa si elementul nu a fost gasit
		}
	}
}

void main()
{
	// initializare produse
	Produs p1 = PopuleazaProdus(1, "Pix", 1);
	Produs p2 = PopuleazaProdus(2, "Stilou", 1.50);
	Produs p3 = PopuleazaProdus(3, "Creion", 2);

	Nod* cap = NULL;

	cap = InserareSfarsit(cap, p1);
	cap = InserareSfarsit(cap, p2);
	cap = InserareSfarsit(cap, p3);

	cap = StergereDupaId(cap, 3);

	Afisare(cap);
}