#include <stdio.h>
#include <memory>

// Structura informatiei continuta
// de un nod al arborelui.
struct Student
{
	int id;
	char* nume;
	int varsta;
	float nota;
};

struct Nod
{
	Student info;
	Nod* stanga;
	Nod* dreapta;
};

// Functie pentru initializare student
Student CreazaStudent(int id, const char* nume, int varsta, float nota)
{
	Student student;

	student.id = id;

	student.nota = nota;
	student.varsta = varsta;

	// char ocupa 1 byte asa ca nu mai trebuie inmultit cu dimensiune tipului
	student.nume = (char*)malloc(strlen(nume) + 1);
	strcpy(student.nume, nume);

	return student;
}

Student CopiazaStudent(Student altStudent)
{
	Student student;

	student.id = altStudent.id;

	student.nota = altStudent.nota;
	student.varsta = altStudent.varsta;

	// char ocupa 1 byte asa ca nu mai trebuie inmultit cu dimensiune tipului
	student.nume = (char*)malloc(strlen(altStudent.nume) + 1);
	strcpy(student.nume, altStudent.nume);

	return student;
}

Nod* CreazaNod(Student student)
{
	Nod* nou = (Nod*)malloc(sizeof(Nod));

	nou->info = student;
	nou->stanga = NULL;
	nou->dreapta = NULL;

	return nou;
}

Nod* InsereazaNod(Nod* root, Student student)
{
	if (root)
	{
		if (student.id < root->info.id)
		{
			root->stanga = InsereazaNod(root->stanga, student);
		}
		else if (student.id > root->info.id)
		{
			root->dreapta = InsereazaNod(root->dreapta, student);
		}
		else
		{
			printf("Id-ul Studentului a mai fost introdus");
		}
	}
	else root = CreazaNod(student);

	return root;
}

void AfiseazaStudent(Student student)
{
	printf("Studentul %s cu id-ul %d in varsta de %d are nota %5.2f.\n",
		student.nume, student.id, student.varsta, student.nota);
}

Nod* CautaDupaId(Nod* root, int id)
{
	if (root)
	{
		if (id < root->info.id)
		{
			root->stanga = CautaDupaId(root->stanga, id);
		}
		else if (id > root->info.id)
		{
			root->dreapta = CautaDupaId(root->dreapta, id);
		}
		else // if (id == root->info.id)
		{
			AfiseazaStudent(root->info);

			Nod* nodGasit = CreazaNod(root->info);

			return nodGasit;
		}
	}
	else printf("Arborele nu contine nici un Nod");
}

Nod* GasesteCelMaiMicId(Nod* root)
{
	if (root == NULL) return NULL;

	else if (root->stanga != NULL)
		return GasesteCelMaiMicId(root->stanga);

	return root;
}

Nod* StergeNod(Nod* root, int id)
{
	if (root == NULL) return NULL;

	if (id < root->info.id)
	{
		root->stanga = StergeNod(root->stanga, id);
	}
	else if (id > root->info.id)
	{
		root->dreapta = StergeNod(root->dreapta, id);
	}
	else
	{
		// Nici un copil
		if (root->stanga == NULL && root->dreapta == NULL)
		{
			free(root->info.nume);
			free(root);

			return NULL;
		}

		else if (root->stanga == NULL || root->dreapta == NULL)
		{
			Nod* temp; // Nod temporar al unui copil

			if (root->stanga == NULL)
				temp = root->dreapta;
			else
				temp = root->stanga;

			free(root->info.nume);
			free(root);

			return temp;
		}

		else
		{
			Nod* temp = GasesteCelMaiMicId(root->dreapta);

			root->info = CopiazaStudent(temp->info);
			root->dreapta = StergeNod(root->dreapta, temp->info.id);
		}
	}

	return root;
}

void AfisareInOrdine(Nod* root)
{
	if (root)
	{
		AfisareInOrdine(root->stanga);

		AfiseazaStudent(root->info);

		AfisareInOrdine(root->dreapta);
	}
}

void main()
{
	Student s1 = CreazaStudent(20, "Alyce", 20, 7);
	Student s2 = CreazaStudent(5, "Lacey", 21, 9);
	Student s3 = CreazaStudent(30, "Ceyla", 22, 10);
	Student s4 = CreazaStudent(1, "Yecla", 23, 5);
	Student s5 = CreazaStudent(15, "Ion", 15, 7);
	Student s6 = CreazaStudent(25, "Marcel", 16, 8);
	Student s7 = CreazaStudent(40, "Viorel", 17, 9);
	Student s8 = CreazaStudent(9, "Ionut", 17, 9);

	Nod* arbore = NULL;

	arbore = InsereazaNod(arbore, s1);
	arbore = InsereazaNod(arbore, s2);
	arbore = InsereazaNod(arbore, s3);
	arbore = InsereazaNod(arbore, s4);
	arbore = InsereazaNod(arbore, s5);
	arbore = InsereazaNod(arbore, s6);
	arbore = InsereazaNod(arbore, s7);
	arbore = InsereazaNod(arbore, s8);

	// CautaDupaId(arbore, 1);

	AfisareInOrdine(arbore);
	printf("\n\n");

	// arbore = StergeNod(arbore, 9);
	// arbore = StergeNod(arbore, 15);
	// arbore = StergeNod(arbore, 5);

	arbore = StergeNod(arbore, 30);

	AfisareInOrdine(arbore);
}