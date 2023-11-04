#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFF_SIZE 1000

typedef struct {
	int an, durata;
	char titlu[128], categorii[64], premii[3];
} DATE_FILM;


void line_print(DATE_FILM* line) {
	printf("%d	%d	%s	%s	%s\n", line->an, line->durata, line->titlu, line->categorii, line->premii);
}

void swap(DATE_FILM* a, DATE_FILM* b) {
	DATE_FILM tmp = *a;
	*a = *b;
	*b = tmp;
}

DATE_FILM* citire_structura(int *n) {

	FILE* fin = fopen("Filme.txt", "r");
	DATE_FILM* date;

	if (fin == NULL) {
		perror("Open file error");
		exit(EXIT_FAILURE);
	}

	if ((date = malloc(sizeof(DATE_FILM) * BUFF_SIZE)) == NULL) {
		perror("Memory error:");
		exit(EXIT_FAILURE);
	}

	int i = 0, current_buff = BUFF_SIZE;
	char s[256];
	fgets(s, 256, fin);
	printf("%s", s);

	while (fscanf(fin, "%d\t%d\t%99[^\t]\t%99[^\t]\t%2s\n",&date[i].an, &date[i].durata, date[i].titlu, date[i].categorii, date[i].premii) == 5) {
	
		if (i == (current_buff-1)) {
			current_buff = 2 * current_buff;
			if ((date = realloc(date, sizeof(DATE_FILM) * current_buff)) == NULL) {
				perror("Memory error:");
				exit(EXIT_FAILURE);
			}
		}
		
		i++;
	}

	fclose(fin);
	(*n) = i;
	return date;
}

void insertion_sort(DATE_FILM *a, int n)
{
	int i, j;
	DATE_FILM tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && ((strcmp(tmp.titlu,a[j - 1].titlu)) < 0); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}

void sortare_premii(DATE_FILM* date, int n) {
	
	int j = 0;

	for (int i = 0; i < n ; i ++) 
		if (!strcmp(date[i].premii, "Da"))
		{
			swap(&date[j], &date[i]);
			j++;
		}
}

void quicksort(DATE_FILM a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	DATE_FILM pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].an < pivot.an)
			stanga++;
		while (pivot.an < a[dreapta].an)
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

void show_list(DATE_FILM* date, int n) {
	for (int i = 0; i < n; i++)
		line_print(&date[i]);
}

int main(void) {
	
	DATE_FILM* date = NULL;
	int n;
	date = citire_structura(&n);
	insertion_sort(date, n);
	//show_list(date, n);
	quicksort(date, 0, n - 1);
	show_list(date, n);
	sortare_premii(date, n);
	//show_list(date, n);
	


	return 0;
}