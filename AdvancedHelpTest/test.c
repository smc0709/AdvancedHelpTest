
/////   INCLUDES   /////

#include "AdvancedHelp/advanced_help.h"
//#include <stdio.h>
//#include <io.h> // Para sistemas como Windows


/////   FUNCTION DEFINITIONS   /////

int main(char* args);
void prinCWD();




/////   FUNCTION IMPLEMENTATIONS   /////

void prinCWD() {
	char cwd[1024]; // Búfer para almacenar la ruta del directorio
	if (getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("CWD: %s\n", cwd);
	} else {
		perror("ERROR: could not obtain CWD");
	}
	return 0;
}




/////   MAIN   /////

int main(char* args){
	printf("TESTING AdvancedHelp module...\n");

	void* help_ptr = NULL;
	char* keyword = "algo";
	char* result = NULL;
	char* help_filename = "..\\..\\AdevancedHelp\\help_example.txt";
	int error = 0;


	// Print cwd
	prinCWD();
	printf("help_filename: %s\n", help_filename);
	printf("\n");

	// Init
	printf("Before init:\n");
	printf("help_ptr = %p\n", help_ptr);
	error = initAdvancedHelp(help_filename, &help_ptr);
	printf("After init:\n");
	printf("error = %i\n", error);
	printf("help_ptr = %p\n", help_ptr);
	printf("\n");

	// Use
	result = getAdvancedHelpForKeyword(keyword, help_ptr);
	printf("result:\n");
	printf("--------------------------------------------------\n");
	printf("%s", (NULL == result) ? "NULL" : result);
	printf("--------------------------------------------------\n");
	if (NULL != result) {
		free(result);
		result = NULL;
	}
	printf("\n");

	// Free
	printf("Before free:\n");
	printf("help_ptr = %p\n", help_ptr);
	freeAdvancedHelp(&help_ptr);
	printf("After free:\n");
	printf("help_ptr = %p\n", help_ptr);
	printf("\n");

	//printf("help_ptr = %s\n", (NULL == help_ptr) ? "NULL" : help_ptr);
}
