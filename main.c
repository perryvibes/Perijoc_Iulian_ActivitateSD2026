#include <stdio.h>

int main() {

	char text[] = "Activitate SDD";
	int textSize = sizeof(text) / sizeof(text[0]);

	for (int i = 0; i < textSize; i++) printf("%c", text[i]);

	return 0;
}