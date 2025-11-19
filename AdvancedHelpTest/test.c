
/////   INCLUDES   /////

#include "AdvancedHelp/advanced_help.h"
#include <Windows.h>


/////   FUNCTION DEFINITIONS   /////

int main(char* args);
void printOK();




/////   FUNCTION IMPLEMENTATIONS   /////

void printOK() {
	printf(" __________________\n");
	printf("|                  |\n");
	printf("|    RESULT  OK    |\n");
	printf("|__________________|\n");
}




/////   MAIN   /////

int main(char* args){
	printf("TESTING AdvancedHelp module...\n");

	char* keyword = "algo";
	char* result = NULL;
	int error = 0;

	char cwd[MAX_PATH];
	DWORD cwd_len;

	void* help_ptr = NULL;
	char help_filename[MAX_PATH] =			"help_example.txt";

	char* text_result_ptr = NULL;
	char text_result_filename[MAX_PATH] =	"help_example_result.txt";

	// Check cwd and adjust file folders
	cwd_len = GetCurrentDirectoryA(MAX_PATH, cwd);
	if (cwd_len > 0) {
		printf("CWD: %s\n", cwd);
		if (strstr(cwd, "x64")) {
			strcpy_s(help_filename, cwd_len,			"../../help_example.txt");
			strcpy_s(text_result_filename, cwd_len,		"../../help_example_result.txt");
		}
	} else {
		perror("ERROR: could not obtain CWD");
	}
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


	// Use function getAdvancedHelpForKeyword()
	result = getAdvancedHelpForKeyword(keyword, help_ptr);
	printf("Obtained result:\n");
	printf("--------------------------------------------------\n");
	printf("%s", (NULL == result) ? "NULL" : result);
	printf("--------------------------------------------------\n");
	error = getTextFromFile(text_result_filename, &text_result_ptr);
	printf("After getTextFromFile:\n");
	printf("error = %i\n", error);
	printf("text_result_ptr = %p\n", help_ptr);
	printf("Expected result:\n");
	printf("--------------------------------------------------\n");
	printf("%s", (NULL == text_result_ptr) ? "NULL" : text_result_ptr);
	printf("--------------------------------------------------\n");


	// Check against expected result
	//printf("NULL == result --> %s\n", (NULL == result) ? "true" : "false");
	//printf("NULL == text_result_ptr --> %s\n", (NULL == text_result_ptr) ? "true" : "false");
	//printf("strlen(result)=%llu == strlen(text_result_ptr)=%llu --> %s\n", strlen(result), strlen(text_result_ptr), (strlen(result) == strlen(text_result_ptr)) ? "true" : "false");
	//printf("0 == strcmp(result, text_result_ptr) --> %s\n", (0 == strcmp(result, text_result_ptr)) ? "true" : "false");
	if (NULL != result && NULL != text_result_ptr && strlen(result) == strlen(text_result_ptr) && 0 == strcmp(result, text_result_ptr)) {
		printOK();
	}


	// Clear variables
	if (NULL != result) {
		free(result);
		result = NULL;
	}
	if (NULL != text_result_ptr) {
		free(text_result_ptr);
		text_result_ptr = NULL;
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
