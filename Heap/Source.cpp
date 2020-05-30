#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define DIMENSIUN 100

struct Student
{
	int id;
	char* nume;
	int varsta;
	float nota;
};

// Structura de Heap (Min / Max)
struct Heap
{
	// Informatia trebuie sa fie un vector (vectorii stau la baza HT-urilor)
	// Pentru a exemplifica si Linear Probingul si Chainigul vom aloca vectorul dinamic 
	// ca vector de pointeri la Nod de lista simpla.
	Student* vector;

	// Dimensiune structura
	int dimensiune;
};

void AfiseazaStudent(Student student)
{
	printf("Studentul %s cu id-ul %d in varsta de %d are nota %5.2f.\n",
		student.nume, student.id, student.varsta, student.nota);
}

Student CreazaStudent(int id, const char* nume, int varsta, float nota)
{
	Student student;

	student.id = id;
	student.nume = (char*)malloc(sizeof(char) * strlen(nume) + 1);

	strcpy(student.nume, nume);

	student.varsta = varsta;
	student.nota = nota;

	return student;
}

Heap CreazaHeap(int dimensiune)
{
	Heap heap;

	heap.dimensiune = dimensiune;
	heap.vector = (Student*)malloc(sizeof(Student) * heap.dimensiune);

	return heap;
}

void Filtreaza(Heap& heap, int pozitie)
{
	int fiuStanga = 2 * pozitie + 1;
	int fiuDreapta = 2 * pozitie + 2;

	int max = pozitie;

	if (heap.vector[max].id < heap.vector[fiuStanga].id && fiuStanga <= heap.dimensiune)
		max = fiuStanga;

	if (heap.vector[max].id < heap.vector[fiuDreapta].id && fiuDreapta <= heap.dimensiune)
		max = fiuDreapta;

	if (max != pozitie)
	{
		Student temp = heap.vector[max];

		heap.vector[max] = heap.vector[pozitie];
		heap.vector[pozitie] = temp;

		if (max > (heap.dimensiune - 1 / 2))
			Filtreaza(heap, max);
	}
}

void Insereaza(Heap& heap, Student student)
{
	if (heap.dimensiune < 0) return;

	Student* tempVec = (Student*)malloc(sizeof(Student) * (heap.dimensiune + 1));

	for (int i = 0; i < heap.dimensiune; i++)
		tempVec[i] = heap.vector[i];

	tempVec[heap.dimensiune] = student;

	free(heap.vector);
	heap.vector = tempVec;

	heap.dimensiune++;

	for (int i = (heap.dimensiune - 2) / 2; i >= 0; i--)
	{
		Filtreaza(heap, i);
	}
}

Student ExtrageRoot(Heap& heap)
{
	if (heap.dimensiune <= 0) return CreazaStudent(NULL, "NULL", NULL, NULL);

	Student root = heap.vector[0];
	Student* vecTemp = (Student*)malloc(sizeof(Student) * (heap.dimensiune - 1));

	for (int i = 1; i < heap.dimensiune; i++)
		vecTemp[i - 1] = heap.vector[i];

	free(heap.vector);
	heap.vector = vecTemp;

	heap.dimensiune--;

	for (int i = heap.dimensiune; i >= 0; i--)
	{
		Filtreaza(heap, i);
	}

	return root;
}

void AfisareConditionata(Heap& heap, int pozitie) 
{
	while (heap.vector[0].id >= pozitie)
	{
		Student student = ExtrageRoot(heap);
		AfiseazaStudent(student);
		free(student.nume);
	}
}

void Afiseaza(Heap heap)
{
	if (heap.vector != NULL)
		for (int i = 0; i < heap.dimensiune; i++)
			AfiseazaStudent(heap.vector[i]);
}

Heap DezalocaHeap(Heap heap)
{
	for (int i = 0; i < heap.dimensiune - 1; i++)
		free(heap.vector[i].nume);

	free(heap.vector);

	heap.dimensiune = 0;

	return heap;
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

	Heap heap = CreazaHeap(0);

	Insereaza(heap, s1);
	Insereaza(heap, s2);
	Insereaza(heap, s3);
	Insereaza(heap, s4);
	Insereaza(heap, s5);
	Insereaza(heap, s6);
	Insereaza(heap, s7);
	Insereaza(heap, s8);
	
	Afiseaza(heap);

	Student extras = ExtrageRoot(heap);
	printf("\n\n");

	Afiseaza(heap);
	printf("\n\n");

	Student extras1 = ExtrageRoot(heap);
	printf("\n\n");

	Afiseaza(heap);
	printf("\n\n");

	// heap = DezalocaHeap(heap);

	Afiseaza(heap);
}