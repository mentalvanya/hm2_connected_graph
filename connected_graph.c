#define _CRT_SECURE_NO_WARNINGS
#define UNIT 0101
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
int vertical_search(int* arr, bool* connect, int n, int m, int j)
{
	int dot1 = -1, dot2 = -1;
	bool found = 0;
	for (int i = 0; i < n; i++)
	{
		if (*(arr + i * m + j) == 1)
		{
			if (found == true)
			{
				dot2 = i;
			}
			else
			{
				dot1 = i;
				found = true;
			}
		}
	}
	if (*(connect + dot1) == false && *(connect + dot2) == true)
	{
		*(connect + dot1) = true;
		return true;
	}
	if (*(connect + dot1) == true && *(connect + dot2) == false)
	{
		*(connect + dot2) = true;
		return true;
	}
	return false;
}
int main(void)
{
	int vertex, edge;
	int i, j;
	int k;

	scanf_s("%d%d", &vertex, &edge);
	int* arr = (int*)malloc(vertex * edge * sizeof(int));
	printf("  ");
	for (j = 0; j < edge; j++)
	{
		printf("%2c", j + UNIT);
	}
	printf("\n");
	for (i = 0; i < vertex; i++)
	{
		printf("%d: ", (i + 1));
		for (j = 0; j < edge; j++)
		{
			scanf_s("%d", (arr + i * edge + j));
			if (!(*(arr + i * edge + j) == 0 || *(arr + i * edge + j) == 1))
			{
				printf("Input error");
				exit(-1);
			}

		}
	}
	printf(" ");
	for (j = 0; j < edge; j++)
	{
		printf("%3c", j + UNIT);
	}
	printf("\n");
	for (i = 0; i < vertex; i++)
	{
		printf("%d: ", (i + 1));
		for (j = 0; j < edge; j++)
		{
			printf("%d  ", *(arr + i * edge + j));
		}
		printf("%c", '\n');
	}
	bool* connect = (bool*)malloc(vertex * sizeof(bool));
	*(connect) = true;
	for (i = 1; i < vertex; i++)
	{
		*(connect + i) = false;
	}

	for (j = 0; j < edge; j++)
	{
		if (vertical_search(arr, connect, vertex, edge, j) == true)
		{
			j = 0;
		}
	}
	bool isCon = true;
	for (i = 0; i < vertex; i++)
	{
		if (*(connect + i) == false)
		{
			isCon = false;
			break;
		}
	}
	if (isCon)
	{
		printf("graph is conncted");
	}
	else
	{
		printf("graph is not conncted");
	}
	FILE* file;
	if ((file = fopen("Dot_file.txt", "w")) == NULL)
	{
		printf("Cannot open file.\n");
		exit(1);
	}
	fprintf(file, "graph G{\n");

	for (j = 0; j < edge; j++)
	{
		int dot1 = -1, dot2 = -1;
		bool found = false;
		bool second_dot = false;
		for (i = 0; i < vertex; i++)
		{

			if (*(arr + i * edge + j) == 1)
				if (!second_dot)
				{


					if (!found)
					{
						dot1 = i;
						found = true;
					}
					else
					{
						dot2 = i;
						second_dot = true;
					}
				}
			
		}
		if (second_dot)
		{
			fprintf(file, "%d -- %d;\n", (dot1 + 1), (dot2 + 1));
		}
		else if (found)
		{
			fprintf(file, "%d -- %d;\n", (dot1 + 1), (dot1 + 1));
		}
	}
	fprintf(file, "}");
	fclose(file);
	system("dot C:\\Users\\duhin\\source\\repos\\hm2_connected_graph\\connected_graph\\Dot_file.txt -Tbmp -o Dot_file.bmp");
	system("rundll32  \"%ProgramFiles%\\Windows Photo Viewer\\PhotoViewer.dll\", ImageView_Fullscreen C:\\Users\\duhin\\source\\repos\\hm2_connected_graph\\connected_graph\\Dot_file.bmp");
}
