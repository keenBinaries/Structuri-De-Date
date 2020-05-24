#include <stdio.h>
#include <memory>

#define DIMENSIUNE_TABEL 10
#define LINESIZE 100

// -- Hash Functions --
// hash = hashFunc(key)
// index = hash % array_size

// Exemplu functie Hash folosind ca cheie un string
int HashFn(const char* cheie, int dimensiune)
{
	int suma = 0;

	for (int i = 0; i < strlen(cheie); i++)
		suma += cheie[i];

	return suma % dimensiune;
}

// Exemplu functie Hash folosind ca cheie un numar
int HashFn2(int cheie, int dimensiune)
{
	int suma = 0;
	suma += cheie;

	return suma % dimensiune;
}

// -- Hash Tabels --
// Colectie de perechi cheie - valoare

// Structura informatii din interiorul tabelului
struct Student
{
	char* nume;
	int varsta;
	float nota;
};

struct Nod
{
	Student info;
	Nod* next;
};

// Structura de HashTabel
struct HashTabel
{
	// Informatia trebuie sa fie un vector (vectorii stau la baza HT-urilor)
	// Pentru a exemplifica si Linear Probingul si Chainigul vom aloca vectorul dinamic 
	// ca vector de pointeri la Nod de lista simpla.
	Nod** vector;

	// Dimensiune structura
	int dimensiune;
};

HashTabel CreazaHashTabel(int dim)
{
	HashTabel tabel;

	tabel.dimensiune = dim;
	tabel.vector = (Nod**)malloc(sizeof(Nod*) * dim);

	for (int i = 0; i < tabel.dimensiune; i++)
		tabel.vector[i] = NULL;

	return tabel;
}

// O pereche cheie - valoare va fi <Student.nume, Student>

// -- Coliziuni -- 
// 1. Linear Probing
// 2. Separate Chaining

// Vom crea functiile specifice HashTabelului tinand cont de metoda
// de evitare a coliziunilor pe care o folosim.

// Functie pentru initializare student
Student CreazaStudent(const char* nume, int varsta, float nota)
{
	Student student;

	student.nota = nota;
	student.varsta = varsta;

	student.nume = (char*)malloc(strlen(nume) + 1); // char ocupa 1 byte asa ca nu mai trebuie inmultit cu dimensiune tipului
	strcpy(student.nume, nume);

	return student;
}

// Functie pentru creare nod de lista simplu inlantuita pentru eitarea
// coliziunilor via Chaining.
Nod* CreazaNod(Student student)
{
	Nod* nod = (Nod*)malloc(sizeof(Nod));

	nod->info = student;
	nod->next = NULL;

	return nod;
}

// Functie pentru adaugare in lista (la sfarsit)
Nod* InsereazaInLista(Nod* cap, Student student)
{
	if (cap)
	{
		Nod* tmp = cap;

		while (tmp->next)
			tmp = tmp->next;

		tmp->next = CreazaNod(student);
	}
	else
		cap = CreazaNod(student);

	return cap;
}

// Functie de inserarea in HT folosint Chaining
HashTabel InserareazaPrinChaining(HashTabel tabel, Student student)
{
	if (tabel.vector) // verificare daca vectorul a fost initializat
	{
		int cheie = HashFn(student.nume, tabel.dimensiune);
		tabel.vector[cheie] = InsereazaInLista(tabel.vector[cheie], student);
	}

	return tabel;
}

// Functie de inserarea in HT folosint Linear Probing
HashTabel InsereazaPrinProbing(HashTabel tabel, Student student)
{
	if (tabel.vector) // verificare daca vectorul a fost initializat
	{
		int index = HashFn(student.nume, tabel.dimensiune);

		while (tabel.vector[index] != NULL) // Cautam un spatiu ne populat
		{
			index++;   // Incrementam cheia pentru a merge pe urmatoarea pozitie
			index = index % tabel.dimensiune; // Calculam % dimensiune din noua cheie ca sa dispersam cautarea.
		}

		tabel.vector[index] = CreazaNod(student);
	}

	return tabel;
}

Student CautaInLista(Nod* cap, const char* cheie)
{
	Student studentGasit;

	Nod* tmp = cap;

	while (tmp)
	{
		if (strcmp(tmp->info.nume, cheie) == 0)
		{
			studentGasit = tmp->info;
			return studentGasit;
		}
		else
		{
			tmp = tmp->next;
		}
	}

	if (!tmp)  // Cand tmp e NULL
	{
		Student studentNull;
		studentNull.nume = NULL;

		return studentNull;
	}

	return studentGasit;
}

Student CautaInHashChaining(HashTabel tabel, const char* cheie)
{
	Student studentGasit;

	if (tabel.vector)
	{
		int index = HashFn(cheie, tabel.dimensiune);
		studentGasit = CautaInLista(tabel.vector[index], cheie);
	}

	return studentGasit;
}

Student CautaInHashProbing(HashTabel tabel, const char* cheie)
{
	Student studentGasit;

	if (tabel.vector)
	{
		int index = HashFn(cheie, tabel.dimensiune);

		// Conditie care sa opreasca executia daca la indexul
		// pe care HashFn la returnat prima data nu este nimic
		while (tabel.vector[index] != NULL && !strcmp(tabel.vector[index]->info.nume, cheie) == 0)
		{
			index++;
			index = index % tabel.dimensiune;
		}

		if (tabel.vector[index] != NULL)
			studentGasit = tabel.vector[index]->info;
		else
		{
			Student studentNull;
			studentNull.nume = NULL;

			return studentNull;
		}
	}

	return studentGasit;
}

void ScrieStudentInFisier(FILE* fisier, Student student)
{
	fprintf(fisier, "Numele studentului este: %s\n", student.nume);
	fprintf(fisier, "Varsta studentului este: %d\n", student.varsta);
	fprintf(fisier, "Nota studentului este: %5.2f\n", student.nota);
	fprintf(fisier, "\n");
}

void ScrieInFiser(const char* fisierCale, HashTabel tabel)
{
	FILE* fisier = fopen(fisierCale, "w+");

	if (fisier)
	{
		// Logica de parcurs tabelul

		for (int i = 0; i < tabel.dimensiune; i++)
		{
			Nod* tmp = tabel.vector[i];

			while (tmp)
			{
				// ScrieStudentInFisier(fisier, tmp->info);
				// fprintf(fisier, "Indexul: %d -> %s - %d - %5.2f\n", i, tmp->info.nume, tmp->info.varsta, tmp->info.nota);

				fprintf(fisier, "%s %d %5.2f\n", tmp->info.nume, tmp->info.varsta, tmp->info.nota);
				tmp = tmp->next;
			}
		}
	}
	else printf("Fisierul nu poate fi deschis");

	fclose(fisier);
}

HashTabel CitesteDinFisier(const char* fisierCale, HashTabel tabel)
{
	FILE* fisier = fopen(fisierCale, "r");

	if (fisier)
	{
		// O linie din fisier
		char* strLine = (char*)malloc(sizeof(LINESIZE) + 1);

		while (fgets(strLine, LINESIZE, fisier))
		{
			Student student;

			char* numeStr = strtok(strLine, " ");

			student.nume = (char*)malloc(sizeof(strlen(numeStr) + 1));
			strcpy(student.nume, numeStr);

			char* varstaStr = strtok(NULL, " ");
			student.varsta = atoi(varstaStr);

			char* notaStr = strtok(NULL, " ");
			student.nota = atof(notaStr);

			// tabel = InsereazaPrinProbing(tabel, student);
			tabel = InserareazaPrinChaining(tabel, student);
		}
	}
	else printf("Fisierul nu poate fi deschis");

	fclose(fisier);

	return tabel;
}

void AfiseazaLista(Nod* cap)
{
	while (cap)
	{
		printf("%s - %d - %5.2f \n", cap->info.nume, cap->info.varsta, cap->info.nota);
		cap = cap->next;
	}
}

void AfiseazaHash(HashTabel tabel)
{
	if (tabel.vector)
	{
		for (int i = 0; i < tabel.dimensiune; i++)
			AfiseazaLista(tabel.vector[i]);
	}
}

void main()
{
	int hashRezultat = HashFn("Cuvant", DIMENSIUNE_TABEL); // Exemplu

	// Creare hash tabel
	HashTabel hashTabel = CreazaHashTabel(DIMENSIUNE_TABEL);

	// Probam metodele de inserare pentru
	// articole care provoaca coliziuni
	// Ex: cheile Alyce si Lacey

	// Au acelasi hash deci vor fi trimise pe aceeasi pozotie
	printf("Hashul lui Alyce este %d \n", HashFn("Alyce", DIMENSIUNE_TABEL));
	printf("Hashul lui Lacey este %d \n", HashFn("Lacey", DIMENSIUNE_TABEL));
	printf("Hashul lui Ceyla este %d \n", HashFn("Ceyla", DIMENSIUNE_TABEL));
	printf("Hashul lui Yecla este %d \n", HashFn("Yecla", DIMENSIUNE_TABEL));

	printf("\n");

	Student s1 = CreazaStudent("Alyce", 20, 7);
	Student s2 = CreazaStudent("Lacey", 21, 9);
	Student s3 = CreazaStudent("Ceyla", 22, 10);
	Student s4 = CreazaStudent("Yecla", 23, 5);

	hashTabel = InserareazaPrinChaining(hashTabel, s1);
	hashTabel = InserareazaPrinChaining(hashTabel, s2);
	hashTabel = InsereazaPrinProbing(hashTabel, s3);
	hashTabel = InsereazaPrinProbing(hashTabel, s4);

	AfiseazaHash(hashTabel);
	printf("\n");

	// Probam Cautari
	Student rezCautareChaining = CautaInHashChaining(hashTabel, "Lacey");
	Student rezCautareProbing = CautaInHashProbing(hashTabel, "Ceyla");
	Student rezCautareProbing2 = CautaInHashProbing(hashTabel, "Yecla");

	Student rez = CautaInHashChaining(hashTabel, "AAA");

	ScrieInFiser("fisier.txt", hashTabel);

	HashTabel hashTabelDinFisier = CreazaHashTabel(DIMENSIUNE_TABEL);
	hashTabelDinFisier = CitesteDinFisier("fisier.txt", hashTabelDinFisier);
	AfiseazaHash(hashTabelDinFisier);

	// TODO: Cautare generala Cautam mai intai prin chaining si apoi prin probing 
}