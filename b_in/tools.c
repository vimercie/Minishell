#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// fonction qui retourne le nom du shell
char* getShellName() {
	char* shellName = getenv("SHELL");
	if (shellName == NULL) {
		perror("Erreur : impossible de trouver le shell");
		exit(1);
	}
	// trouver l'index du dernier '/'
	int lastSlashIndex = 0;
	for (int i = 0; i < strlen(shellName); i++) {
		if (shellName[i] == '/') {
			lastSlashIndex = i;
		}
	}
	// tronquer le chemin du shell
	shellName[lastSlashIndex] = '\0';
	// retourner le nom du shell
	return &shellName[lastSlashIndex + 1];
}

int main(int argc, char** argv) {
	char* shellName = getShellName();
	printf("Le shell est %s\n", shellName);
	return 0;
}