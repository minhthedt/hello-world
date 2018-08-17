#include <stdio.h>
#include <string.h>

int isEven(char *T, int a, int b)
{
	int i;
	int count[26];
	for (i = 0; i < 26; i++) 
		count[i] = 0;
	for (i = a; i <= b; i++)
		count[T[i] - 'a']++;
	for (i = 0; i < 26 ; i++)
		if (count[i] % 2 == 1)
			return 0;
	return 1;
}

	
int main()
{
	char buffer[50001];
	int i, j, t, T, len, count;
	scanf("%d", &T);
	for (t = 0; t < T; t++) {
		scanf("%s", buffer);
		len = strlen(buffer);
		count = 0;
		for (i = 0; i < len; i++) 
			for (j = i+1; j < len; j = j + 2) 
				count += isEven(buffer, i, j);
		printf("%d\n", count);
	}
	return 0;
}
			
				
