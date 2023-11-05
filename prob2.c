#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INCREMENT_SIZE 512

typedef struct {
	char nume[64];
	float nota;
} ELEV;

ELEV* citire_date(int* n) {
	FILE* fin = fopen("Studenti.txt", "r");
	ELEV* vect = malloc(sizeof(ELEV) * INCREMENT_SIZE);

	if (fin == NULL) {
		perror("file error:");
		exit(EXIT_FAILURE);
	}

	if (vect == NULL) {
		perror("mem error:");
		exit(EXIT_FAILURE);
	}

	int i = 0, max_size = INCREMENT_SIZE;

	while (fgets(vect[i].nume, 64, fin)) {
		vect[i].nume[strcspn(vect[i].nume, "\n") - 1] = '\0';
		fscanf(fin, "%f\n", &vect[i].nota);

		i++;
		if (i == max_size) {
			max_size += INCREMENT_SIZE;
			if ((vect = realloc(vect, max_size * sizeof(ELEV))) == NULL) {
				perror("mem eror");
				exit(EXIT_FAILURE);
			}
		}

	}

	fclose(fin);
	*n = i;
	return vect;
}

void afisare_studenti(ELEV* vect, int n) {
	for (int i = 0; i < n; i++)
		printf("%s-%f\n", vect[i].nume, vect[i].nota);
}

void insertion_sort(ELEV a[], int n)
{
	int i, j;
	ELEV tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (strcmp(tmp.nume, a[j - 1].nume) < 0); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

void swap(ELEV* a, ELEV* b) {
	ELEV tmp = *a;
	*a = *b;
	*b = tmp;
}

void ord_promovare(ELEV* vect, int n) {
	int j = 0;

	for (int i = 0; i < n; i++)
		if (vect[i].nota >= 5) {
			swap(&vect[i], &vect[j]);
			j++;
		}
}

void quicksort(ELEV a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	ELEV pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].nota < pivot.nota)
			stanga++;
		while (pivot.nota < a[dreapta].nota)
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}

int main(void) {
	ELEV* elevi = NULL;
	int n;
	elevi = citire_date(&n);

	insertion_sort(elevi, n);
	//afisare_studenti(elevi, n);

	ord_promovare(elevi, n);
	//afisare_studenti(elevi, n);

	quicksort(elevi, 0, n - 1);
	afisare_studenti(elevi, n);



	return 0;
}