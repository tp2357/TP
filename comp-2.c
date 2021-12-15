#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int *mot(const char *s) {
	int len = strlen(s);
	int *m = (int*) malloc(len * sizeof(int));
	int i=0;
	while (i < len) {
		if (s[i] >= 'a' && s[i] <= 'c') m[i] = (int) (s[i] - 'a');
		else m[i] = -1;
		i++;
	}
	return m;
}

int trace(int **M, int *m, int len) {
	if (m[0] == -1) return -1;
	int tr = M[0][m[0]];
	int i=1;
	while (i < len && tr != -1) {
		tr = M[tr][m[i]];
		i++;
	}
	return tr;
}

int **matrice(int l, int c) {
	int **m = (int**) malloc(l * sizeof(int*));
	int i, j;
	for (i=0; i<l; i++) {
		m[i] = (int*) malloc(c * sizeof(int));
	}
	
	for (i=0; i<l; i++) {
		for (j=0; j<c; j++) {
			printf("m[%d][%d] = ", i, j);
			scanf("%d", &m[i][j]);
		}
	}
	return m;
}

int **l_matrice(const char *filename, int *rl, int *rc) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) return NULL;
	int l, c;
	fscanf(fp, "%d %d", &l, &c);
	int **m = (int**) malloc(l * sizeof(int*));
        int i, j;
        for (i=0; i<l; i++) {
                m[i] = (int*) malloc(c * sizeof(int));
        }
	for (i=0; i<l; i++) {
		for (j=0; j<c; j++) {
			fscanf(fp, "%d", &m[i][j]);
		}
        }
	fclose(fp);
	*rl = l;
	*rc = c;
	return m;
}


int main() {
	int l, c;
	int i, j;
	int **M = l_matrice("Donnes_a_l.txt", &l, &c);
	char word[64] = {0};
	printf("saisir un mot : ");
	scanf("%s", word);
	while(word[i]) i++;	
	int *m = mot(word);
	int tr = trace(M, m, i);
	
	printf("etat final : %d\n", tr);
	for (i=0; i<l; i++) free(M[i]);
	free(M);
	free(m);
	return 0;
}
