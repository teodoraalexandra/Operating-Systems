#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	//alocare statica a unui sir de caractere
	//char s1[50];

	//alocare dinamica a unui sir de caractere
	char* s2 = (char*)malloc(50 * sizeof(char));
	if (s2 == NULL) {
		perror("Error");
		return 1;
	}
	int i;
	for(i =0; i < 10; i++) {
		scanf("%c", &s2[i]);
	s2[10] = '\0'; 
	} 	
	//s2 = "dbcdbucbdcdicidcnd";
	printf("Sir s2: %s\n:",s2);

	//dealocare memorie alocata dinamic
	free(s2);
	return 0;
}
