#include "../inc/minishell.h"

char* get_current_dir(void) {
	char *cwd;

	// Get the current working directory
	cwd = (char *)malloc(sizeof(char) * 1024);
	if (!cwd)
		return NULL;

	if (getcwd(cwd, sizeof(char) * 1024) == NULL) {
		dprintf(1, "%s\n", cwd);
		free(cwd);
		return NULL;
	}
	return cwd;
}

// déclaration des variables
int argc; // nombre d'arguments passés à la fonction cd
char** argv; // tableau des arguments passés à la fonction cd
char* homeDir; // chemin absolu du répertoire HOME


// fonction pour aller au répertoire HOME
void goToHomeDir() {
	char* homeDir;
	homeDir = getenv("HOME"); // récupérer le chemin absolu du répertoire HOME
	if (homeDir == NULL) {
		perror("");
		exit(1);
	}
	else {
		// changer le répertoire courant au répertoire HOME
		if (chdir(homeDir) == -1) {
			perror("");
			exit(1);
		}
	}
}

// fonction pour aller à un chemin absolu
void goToAbsolutePath(char* path) {
	// changer le répertoire courant au chemin spécifié
	if (chdir(path) == -1) {
		perror("");
		exit(1);
	}
}

// fonction pour aller à un chemin relatif
void goToRelativePath(char* path) {
	// changer le répertoire courant au chemin spécifié
	if (chdir(path) == -1) {
		perror("");
		exit(1);
	}
}

// fonction principale
int cd(int argc, char** argv) {
	if (argc == 1)
		goToHomeDir();
	else
		if (argv[1][0] == '/')
			goToAbsolutePath(argv[1]);
		else
			goToRelativePath(argv[1]);
	return 0;
}

// int main(int argc, char** argv) {
//     dprintf(1, "%s\n", get_current_dir());
// 	if (cd(argc, argv) == 0) {
// 		printf("Le répertoire a été changé avec succès.\n");
// 	}
//     dprintf(1, "%s\n", get_current_dir());
// 	return 0;
// }