#include <stdio.h>
#include <iostream>

// Structura unui nod
struct Nod
{
	// informatia structurii
	int info;
	// pointer catre nodul urmator
	Nod* next;
};

// Afisare prin valoare
void Afisare(Nod* cap)
{
	while (cap != NULL)
	{
		printf("%d\n", cap->info);

		cap = cap->next;
	}
}

// Afisare prin refereinta
void AfisarePrinReferinta(Nod*& cap)
{
	Nod* ptr = cap;

	while (ptr != NULL)
	{
		printf("%d\n", ptr->info);

		ptr = ptr->next;
	}
}

// Afisare prin adresa
void AfisarePrinAdresa(Nod** cap)
{
	Nod* ptr = *cap;

	while (ptr != NULL)
	{
		printf("%d\n", ptr->info);
		// printf("%d\n", (*ptr).info);

		ptr = ptr->next;
		// ptr = (*ptr).next;
	}
}

// Inserare la sfarsit prin referinta
void InserareSfarsit(Nod*& cap, int val)
{
	Nod* nod = new Nod;
	// Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = val;
	nod->next = NULL;

	if (cap == NULL)
		cap = nod;
	else
	{
		Nod* ptr = cap;

		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = nod;
	}
}

// Inserare la sfarsit prin adresa
void InserareSfarsitPrinAdresa(Nod** cap, int val)
{
	Nod* nod = new Nod;
	// Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = val;
	nod->next = NULL;

	if ((*cap) == NULL)
		(*cap) = nod;
	else
	{
		Nod* ptr = (*cap);

		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = nod;
	}
}

// Inserare la inceput prin referinta
void InserareInceput(Nod*& cap, int val)
{
	Nod* nod = new Nod;
	// Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = val;
	nod->next = cap;

	cap = nod;
}

// Inserare la inceput prin adresa
void InserareInceputPrinAdresa(Nod** cap, int val)
{
	Nod* nod = new Nod;
	// Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = val;
	nod->next = (*cap);

	(*cap) = nod;
}

// Inserare pozitie prin referinta
void InserareDupaPozitie(Nod*& cap, int pozitie, int val)
{
	// verificam daca lista este goala
	if (cap == NULL)
		return;

	// daca pozitia este prima 
	if (pozitie == 0)
	{
		Nod* nou = new Nod;

		nou->info = val;
		nou->next = cap;

		cap = cap->next;
		cap = nou;

		return;
	}

	Nod* temp = cap;
	int pozitieCurenta = 0;

	while (temp != NULL && pozitieCurenta < pozitie - 1)
	{
		temp = temp->next;
		pozitieCurenta++;
	}

	if (pozitieCurenta == pozitie - 1)
	{
		Nod* nou = new Nod;

		nou->next = temp->next->next;
		temp->next = nou;

		nou->info = val;
	}
}

// Iserare dupa pozitie prin adresa
void InserareDupaPozitie(Nod** cap, int pozitie, int val)
{
	// verificam daca lista este goala
	if ((*cap) == NULL)
		return;


	// daca pozitia este prima 
	if (pozitie == 0)
	{
		Nod* nou = new Nod;

		nou->info = val;
		nou->next = (*cap);

		(*cap) = (*cap)->next;
		(*cap) = nou;

		return;
	}

	Nod* temp = *cap;
	int pozitieCurenta = 0;

	while (temp != NULL && pozitieCurenta < pozitie - 1)
	{
		temp = temp->next;
		pozitieCurenta++;
	}

	if (pozitieCurenta == pozitie - 1)
	{
		Nod* nou = new Nod;

		nou->next = temp->next->next;
		temp->next = nou;

		nou->info = val;
	}
}

void StergerePozitie(Nod*& cap, int pozitie)
{
	// daca lista e goala
	if (cap == NULL)
		return;

	// daca pozitia este prima
	if (pozitie == 0)
	{
		Nod* deSters = cap;
		cap = cap->next;

		delete deSters;
		// free desters;

		return;
	}

	Nod* predecesor = cap;
	int pozitieCurenta = 0;

	while (predecesor != NULL && pozitieCurenta < pozitie - 1)
	{
		predecesor = predecesor->next;
		pozitieCurenta++;
	}

	if (pozitieCurenta == pozitie - 1)
	{
		// stergem pe urmatorul

		Nod* deSters = predecesor->next;

		predecesor->next = predecesor->next->next;

		delete deSters;
		// free deSters;
	}
}

void StergereValoare(Nod*& cap, int val)
{
	// Daca lista este goala nu facem nimic
	if (cap == NULL)
		return;

	// daca este primul elemenet, atunci
	// il stergem si mutam capul
	if (cap->info == val)
	{
		Nod* deSters = cap;
		cap = cap->next;

		delete deSters;
		// free deSters;

		return;
	}

	// cautam predecesorul
	Nod* predecesor = cap;

	while (predecesor->next != NULL && predecesor->next->info != val)
		predecesor = predecesor->next;

	// daca a fost gasit, atunci il stergem
	if (predecesor->next != NULL)
	{
		Nod* deSters = predecesor->next;

		predecesor->next = predecesor->next->next;

		delete deSters;
		// free deSters;
	}
}

int CautareValoare(Nod* cap, int val)
{
	if (cap == NULL)
		return 0;
	else
	{
		while (cap != NULL)
		{
			if (cap->info == val)
			{
				if (cap->next != NULL)
					return cap->next->info;
			}
			else
			{
				if (cap->next != NULL)
					cap = cap->next;
			}
		}
	}
}

int main()
{
	// Declararea listei se 
	// face prin crearea nodului initial null.
	Nod* cap = NULL;

	InserareSfarsit(cap, 1);
	InserareSfarsit(cap, 2);
	InserareSfarsit(cap, 3);
	InserareSfarsit(cap, 4);

	Afisare(cap);
	printf("\n");

	StergerePozitie(cap, 3);

	Afisare(cap);
	printf("\n");

	StergereValoare(cap, 3);

	Afisare(cap);
	printf("\n");

	// InserareDupaPozitie(cap, )
}