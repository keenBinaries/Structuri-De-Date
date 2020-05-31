#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct Student
{
	int id;
	char* nume;
	int varsta;
	float nota;
};

struct NodListaNoduri;

struct NodListaLegaturi
{
	NodListaNoduri* info;
	NodListaLegaturi* next;
};

struct NodListaNoduri
{
	Student info;
	NodListaNoduri* next;

	// cap lista adiacenti
	NodListaLegaturi* adiacenti;
};

struct NodStiva
{
	int id;
	NodStiva* next;
};

Student CreazaStudent(int id, const char* nume, int varsta, float nota)
{
	Student student;

	student.id = id;

	// Alocare si initializare student.nume (char*)
	student.nume = (char*)malloc(sizeof(char) * strlen(nume));
	strcpy(student.nume, nume);

	student.varsta = varsta;
	student.nota = nota;

	return student;
}

NodListaLegaturi* AdaugaLegatura(NodListaLegaturi* capLegaturi, NodListaNoduri* nodDeLegat)
{
	NodListaLegaturi* legaturaNoua = (NodListaLegaturi*)malloc(sizeof(NodListaLegaturi));

	legaturaNoua->info = nodDeLegat;
	legaturaNoua->next = NULL;

	if (capLegaturi)
	{
		NodListaLegaturi* temp = capLegaturi;

		while (temp->next)
			temp = temp->next;

		temp->next = legaturaNoua;
	}
	else
		capLegaturi = legaturaNoua;

	return capLegaturi;
}

NodListaNoduri* AdaugaNod(NodListaNoduri* cap, Student student)
{
	NodListaNoduri* nodNou = (NodListaNoduri*)malloc(sizeof(NodListaNoduri));

	nodNou->info = student;
	nodNou->next = NULL;

	nodNou->adiacenti = NULL;

	if (cap)
	{
		NodListaNoduri* temp = cap;

		while (temp->next)
			temp = temp->next;

		temp->next = nodNou;
	}
	else
		cap = nodNou;

	return cap;
}

NodStiva* AdaugaNodStiva(NodStiva* cap, int id)
{
	NodStiva* nodNouStiva = (NodStiva*)malloc(sizeof(NodStiva));

	nodNouStiva->id = id;
	nodNouStiva->next = NULL;

	if (cap)
	{
		NodStiva* temp = cap;

		while (temp->next)
			temp = temp->next;

		temp->next = nodNouStiva;
	}
	else
		cap = nodNouStiva;

	return cap;
}

int ExtrageDinStiva(NodStiva*& cap)
{
	if (cap)
	{
		NodStiva* temp = cap;

		while (temp->next && temp->next->next)
			temp = temp->next;

		if (temp->next)
		{
			int rezultat = temp->next->id;

			free(temp->next);
			temp->next = NULL;

			return rezultat;
		}
		else if (temp)
		{
			int rezultat = temp->id;

			free(temp);
			cap = NULL;

			return rezultat;
		}
	}
	else return -1;
}

int CalculeazaNumarNoduri(NodListaNoduri* cap)
{
	int numar = 0;

	while (cap)
	{
		numar++;
		cap = cap->next;
	}

	return numar;
}

NodListaNoduri* CautaDupaId(NodListaNoduri* cap, int id)
{
	while (cap && cap->info.id != id)
		cap = cap->next;

	return cap;
}

void ParcurgeInAdancime(NodListaNoduri* cap, int nodRadacina)
{
	NodStiva* stiva = NULL;

	stiva = AdaugaNodStiva(stiva, nodRadacina);

	int nrNoduri = CalculeazaNumarNoduri(cap);
	int* vizitate = (int*)malloc(sizeof(int) * nrNoduri);

	for (int i = 0; i < nrNoduri; i++)
		vizitate[i] = 0;

	vizitate[nodRadacina] = 1;

	while (stiva)
	{
		int nodCurent = ExtrageDinStiva(stiva);
		NodListaNoduri* nodGasit = CautaDupaId(cap, nodCurent);

		printf("Nod: %d %s %d %5.2f\n", nodGasit->info.id,
			nodGasit->info.nume, nodGasit->info.varsta, nodGasit->info.nota);

		NodListaLegaturi* tempLegaturi = nodGasit->adiacenti;

		while (tempLegaturi)
		{
			if (vizitate[tempLegaturi->info->info.id] == 0)
			{
				stiva = AdaugaNodStiva(stiva, tempLegaturi->info->info.id);
				vizitate[tempLegaturi->info->info.id] = 1;
			}
			tempLegaturi = tempLegaturi->next;
		}
	}
}

void AfiseazaLegaturi(NodListaLegaturi* cap)
{
	while (cap != NULL)
	{
		printf("Nod: %d %s %d %5.2f", cap->info->info.id, cap->info->info.nume, cap->info->info.varsta, cap->info->info.nota);
		printf("\n");

		cap = cap->next;
	}
}

void AfiseazaNoduri(NodListaNoduri* cap)
{
	while (cap != NULL)
	{
		printf("Nod: %d %s %d %5.2f", cap->info.id, cap->info.nume, cap->info.varsta, cap->info.nota);
		printf("\n");

		cap = cap->next;
	}
}

void StergeListaLegaturi(NodListaLegaturi*& cap)
{
	while (cap)
	{
		NodListaLegaturi* temp = cap;

		cap = cap->next;

		free(temp->info->info.nume);
		free(temp);
	}
}

void StergeListaNoduri(NodListaNoduri*& cap)
{
	while (cap)
	{
		NodListaNoduri* temp = cap;

		cap = cap->next;

		// free(temp->adiacenti);
		free(temp->info.nume);
		free(temp);
	}
}

void main()
{
	NodListaNoduri* graf = NULL;

	graf = AdaugaNod(graf, CreazaStudent(0, "Ion", 20, 9));
	graf = AdaugaNod(graf, CreazaStudent(1, "Gica", 23, 7));

	// La apel era problema
	NodListaNoduri* nod = CautaDupaId(graf, 0);
	NodListaNoduri* nod2 = CautaDupaId(graf, 1);

	nod->adiacenti = AdaugaLegatura(nod->adiacenti, nod2);

	ParcurgeInAdancime(graf, 0);
}