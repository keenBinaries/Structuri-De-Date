#include <stdio.h>
#include <iostream>

// Structura informatii din interiorul nodului
struct Student
{
	char* nume;
	int varsta;
	float nota;
};

// Structura unui nod
struct Nod
{
	// informatia structurii
	Student* info;
	// pointer catre nodul urmator
	Nod* next;
};

// Creare student pe stack
Student* CreazaStudent(const char* nume, int varsta, float nota)
{
	Student* student = new Student;
	// Student* student = (Student*)malloc(sizeof(Student));

	// Alocare si initializare student.nume (char*)
	student->nume = (char*)malloc(sizeof(char) * strlen(nume));
	strcpy(student->nume, nume);

	student->varsta = varsta;
	student->nota = nota;

	return student;
}

// Initializare student prin refereinta
void InitializareStudent(Student& student, const char* nume, int varsta, float nota)
{
	// Alocare si initializare student.nume (char*)
	student.nume = (char*)malloc(sizeof(char) * strlen(nume));
	strcpy(student.nume, nume);

	student.varsta = varsta;
	student.nota = nota;
}

// Afisare prin valoare
void Afisare(Nod* cap)
{
	while (cap != NULL)
	{
		printf("Numele studentului este: %s\n", cap->info->nume);
		printf("Varsta studentului este: %d\n", cap->info->varsta);
		printf("Nota studentului este: %5.2f\n", cap->info->nota);

		printf("\n");

		cap = cap->next;
	}
}

// Afisare prin refereinta
void AfisarePrinReferinta(Nod*& cap)
{
	Nod* ptr = cap;

	while (ptr != NULL)
	{
		printf("Numele studentului este: %s\n", ptr->info->nume);
		printf("Varsta studentului este: %d\n", ptr->info->varsta);
		printf("Nota studentului este: %5.2f\n", ptr->info->nota);

		printf("\n");

		ptr = ptr->next;
	}
}

// Afisare prin adresa
void AfisarePrinAdresa(Nod** cap)
{
	Nod* ptr = *cap;

	while (ptr != NULL)
	{
		printf("Numele studentului este: %s\n", ptr->info->nume);
		printf("Varsta studentului este: %d\n", ptr->info->varsta);
		printf("Nota studentului este: %5.2f\n", ptr->info->nota);

		/*printf("Numele studentului este: %s\n", (*ptr).info.nume);
		printf("Varsta studentului este: %d\n", (*ptr).info.varsta);
		printf("Nota studentului este: %5.2f\n", (*ptr).info.nota);*/

		printf("\n");

		ptr = ptr->next;
		// ptr = (*ptr).next;
	}
}

// Inserare la sfarsit prin referinta
// si element nou prin referinta
void InserareSfarsitPrinReferintaSiReferinta(Nod*& cap, Student*& studentNou)
{
	Nod* nodNou = new Nod;
	// Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = studentNou;
	nodNou->next = NULL;

	if (cap == NULL)
		cap = nodNou;
	else
	{
		Nod* ptr = cap;

		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = nodNou;
	}
}

// Inserare la sfarsit prin referinta
// si element nou prin adresa
void InserareSfarsitPrinReferintaSiPointer(Nod*& cap, Student** studentNou)
{
	Nod* nodNou = new Nod;
	// Nod* nodNou = (Nod*)malloc(sizeof(Nod));

	nodNou->info = (*studentNou);
	nodNou->next = NULL;

	if (cap == NULL)
		cap = nodNou;
	else
	{
		Nod* ptr = cap;

		while (ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = nodNou;
	}
}

// Inserare la inceput prin 
// referinta si referinta
void InserareInceputPrinReferintaSiReferinta(Nod*& cap, Student*& studentNou)
{
	Nod* nod = new Nod;
	// Nod* nod =(Nod*)malloc(sizeof(Nod));

	nod->info = studentNou;
	nod->next = cap;

	cap = nod;
}

// Inserare la inceput prin 
// pointer si pointer
void InserareInceputPrinPointerSiPointer(Nod** cap, Student** studentNou)
{
	Nod* nod = new Nod;
	// Nod* nod =(Nod*)malloc(sizeof(Nod));

	nod->info = (*studentNou);
	nod->next = (*cap);

	(*cap) = nod;
}

// Inserare dupa valoare, transmitere prin
// referinte pentru parametri dinamici
void InserareDupaVarsta(Nod*& cap, Student* studentNou, int varsta)
{
	Nod* nod = new Nod;
	// Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = studentNou;

	Nod* tmp = cap;

	if (tmp != NULL)
	{
		while (tmp->next != NULL && tmp->info->varsta != varsta)
		{
			tmp = tmp->next;
		}

		if (tmp->info->varsta == varsta)
		{
			nod->next = tmp->next;
			tmp->next = nod;

			return;
		}

		printf("Varsta nu a fost gasita");
	}
	else
	{
		printf("Lista este goala!");

		return;
	}
}

//Cautare nota dupa nume
float CautareValoare(Nod* cap, const char* nume)
{
	if (cap == NULL)
		return -1;
	else
	{
		while (cap != NULL)
		{
			if (strcmp(cap->info->nume, nume))
			{
				return cap->info->nota;
			}
			else
			{
				if (cap->next != NULL)
					cap = cap->next;
			}
		}
	}
}

void Sortare(Nod*& lista)
{
	bool stare = true;
	Nod* auxSort = NULL;

	while (stare == true)
	{
		stare = false;
		auxSort = lista;

		while (auxSort->next)
		{
			if (auxSort->info->varsta >= auxSort->next->info->varsta)
			{
				Student* tempS = auxSort->info;

				auxSort->info = auxSort->next->info;
				auxSort->next->info = tempS;

				stare = true;
			}

			auxSort = auxSort->next;
		}
	}
}

Nod* StergereLista(Nod* lista)
{
	while (lista)
	{
		free(lista->info);
		Nod* p = lista;
		lista = lista->next;
		free(p);
	}

	return NULL;
}

/* Golire lista, parametru
   transmis prin referinta */
void GolesteLista(Nod*& lista)
{
	Nod* aux = lista;

	while (aux)
	{
		free(aux->info);
		Nod* p = aux;
		aux = aux->next;
		free(p);
	}

	lista = NULL;
}

void StergereValoare(Nod*& cap, int varsta)
{
	// Daca lista este goala nu facem nimic
	if (cap == NULL)
		return;

	// daca este primul elemenet, atunci
	// il stergem si mutam capul
	if (cap->info->varsta == varsta)
	{
		Nod* deSters = cap;
		cap = cap->next;

		delete deSters;
		// free deSters;

		return;
	}

	// cautam predecesorul
	Nod* predecesor = cap;

	while (predecesor->next != NULL && predecesor->next->info->varsta != varsta)
		predecesor = predecesor->next;

	// daca a fost gasit, atunci il stergem
	if (predecesor->next != NULL)
	{
		Nod* deSters = predecesor->next;

		predecesor->next = predecesor->next->next;

		delete deSters;
		// free(deSters);
	}
}


int main()
{
	// Initializare lista,
	// primul nod este null.
	Nod* cap = NULL;

	Student* s1 = CreazaStudent("Marcel", 20, 5);
	Student* s2 = CreazaStudent("Vasilica", 21, 6);
	Student* s3 = CreazaStudent("Gica", 45, 5);

	InserareSfarsitPrinReferintaSiPointer(cap, &s1);
	// Afisare(cap);

	InserareSfarsitPrinReferintaSiReferinta(cap, s2);
	// Afisare(cap);

	InserareInceputPrinReferintaSiReferinta(cap, s3);
	// Afisare(cap);

	Student* s4 = CreazaStudent("Ionica", 19, 9);
	InserareDupaVarsta(cap, s4, 21);

	Afisare(cap);

	printf("-----------------------\n");
	Sortare(cap);

	Afisare(cap);
}