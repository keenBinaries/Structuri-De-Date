#include <stdio.h>
#include <malloc.h>
#include <string.h>

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

void Filtreaza(Heap heap, int pozitie)
{
	int fiuStanga = 2 * pozitie + 1;
	int fiuDreapta = 2 * pozitie + 2;

	int max = pozitie;

	if (heap.vector[max].id < heap.vector[fiuStanga].id && fiuStanga < heap.dimensiune)
		max = fiuStanga;

	if (heap.vector[max].id < heap.vector[fiuDreapta].id && fiuDreapta < heap.dimensiune)
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

void Insereaza(Heap heap, Student student)
{
	if (heap.dimensiune <= 0) return;

	Student* tempVec = (Student*)malloc(sizeof(Student) * (heap.dimensiune + 1));

	for (int i = 0; i < heap.dimensiune; i++)
		tempVec[i] = heap.vector[i];

	tempVec[heap.dimensiune] = student;

	free(heap.vector);
	heap.vector = tempVec;

	heap.dimensiune++;

	for (int i = (heap.dimensiune - 1) / 2; i >= 0; i--)
	{
		Filtreaza(heap, i);
	}
}

void main()
{

}