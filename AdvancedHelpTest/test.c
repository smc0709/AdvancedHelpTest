
/////   INCLUDES   /////

#include "AdvancedHelp/advanced_help.h"
#include <Windows.h>




/////   DEFINES   /////

#define MAX_KEYWORD_LEN 64




/////   FUNCTION DEFINITIONS   /////

int main(char* args);
static void printOK();
static void printNOK();




/////   FUNCTION IMPLEMENTATIONS   /////

static void printOK() {
	printf(" ________________\n");
	printf("|                |\n");
	printf("|    TEST  OK    |\n");
	printf("|________________|\n");
}
static void printNOK() {
	printf(" ________________\n");
	printf("|                |\n");
	printf("|   TEST  FAIL   |\n");
	printf("|________________|\n");
}




/////   MAIN   /////

int main(char* args){
	printf("TESTING AdvancedHelp module...\n");

	char keyword[MAX_KEYWORD_LEN] = "algo";
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



	///  TEST char FUNCTIONS  ///
		////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("\n");
	printf("=============================\n");
	printf("||     TEST  1  STARTS     ||\n");
	printf("=============================\n");
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
	printf("Obtained result (len=%d):\n", (NULL == result) ? -1 : (int)strlen(result));
	printf("--------------------------------------------------\n");
	printf("%s", (NULL == result) ? "NULL\n" : result);
	printf("--------------------------------------------------\n");
	error = getTextFromFile(text_result_filename, &text_result_ptr);
	printf("After getTextFromFile:\n");
	printf("error = %i\n", error);
	printf("text_result_ptr = %p\n", help_ptr);
	printf("Expected result (len=%d):\n", (NULL == text_result_ptr) ? -1 : (int)strlen(text_result_ptr));
	printf("--------------------------------------------------\n");
	printf("%s", (NULL == text_result_ptr) ? "NULL\n" : text_result_ptr);
	printf("--------------------------------------------------\n");


	// Check against expected result
	//printf("NULL == result --> %s\n", (NULL == result) ? "true" : "false");
	//printf("NULL == text_result_ptr --> %s\n", (NULL == text_result_ptr) ? "true" : "false");
	//printf("strlen(result)=%llu == strlen(text_result_ptr)=%llu --> %s\n", strlen(result), strlen(text_result_ptr), (strlen(result) == strlen(text_result_ptr)) ? "true" : "false");
	//printf("0 == strcmp(result, text_result_ptr) --> %s\n", (0 == strcmp(result, text_result_ptr)) ? "true" : "false");
	if (NULL != result && NULL != text_result_ptr && strlen(result) == strlen(text_result_ptr) && 0 == strcmp(result, text_result_ptr)) {
		printOK();
	} else {
		printNOK();
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



	////////////////////////////////////////////////////////////////////////////////////////////////////
	printf("\n\n\n");


	///  TEST wchar_t FUNCTIONS  ///

	printf("\n");
	printf("=============================\n");
	printf("||     TEST  2  STARTS     ||\n");
	printf("=============================\n");
	printf("\n");

	//--------------------------------------------------------------------------------
	// Example of how to transform char* into WCHAR*:
	//--------------------------------------------------------------------------------
	//WCHAR* help_filename_w = NULL;
	//size_t help_filename_len = strlen(help_filename);
	//help_filename_w = malloc(sizeof(WCHAR) * (help_filename_len + 1));
	//if (NULL == help_filename_w) {
	//	// ERROR
	// }
	//size_t res = mbstowcs(help_filename_w, help_filename, help_filename_len);
	// // Check res
	//help_filename_w[help_filename_len] = L'\0';
	//--------------------------------------------------------------------------------

	// Preparation of W variables
	WCHAR help_filename_w[MAX_PATH] = { 0 };
	size_t conv_chars = 0;
	error = mbstowcs_s(&conv_chars, help_filename_w, MAX_PATH, help_filename, MAX_PATH);

	WCHAR text_result_filename_w[MAX_PATH] = { 0 };
	error = mbstowcs_s(&conv_chars, text_result_filename_w, MAX_PATH, text_result_filename, MAX_PATH);

	WCHAR keyword_w[MAX_KEYWORD_LEN] = { 0 };
	error = mbstowcs_s(&conv_chars, keyword_w, MAX_KEYWORD_LEN, keyword, MAX_KEYWORD_LEN);

	WCHAR* result_w = NULL;
	WCHAR* text_result_ptr_w = NULL;

	// Init
	printf("Before init:\n");
	printf("help_ptr = %p\n", help_ptr);
	error = initAdvancedHelpW(help_filename_w, &help_ptr);
	printf("After init:\n");
	printf("error = %i\n", error);
	printf("help_ptr = %p\n", help_ptr);
	printf("\n");

	// Use function getAdvancedHelpForKeywordW()
	result_w = getAdvancedHelpForKeywordW(keyword_w, help_ptr);
	printf("Obtained result (len=%d):\n", (NULL == result_w) ? -1 : (int)wcslen(result_w));
	printf("--------------------------------------------------\n");
	printf("%ws", (NULL == result_w) ? L"NULL\n" : result_w);
	printf("--------------------------------------------------\n");
	error = getTextFromFileW(text_result_filename_w, &text_result_ptr_w);
	printf("After getTextFromFile:\n");
	printf("error = %i\n", error);
	printf("text_result_ptr = %p\n", help_ptr);
	printf("Expected result (len=%d):\n", (NULL == text_result_ptr_w) ? -1 : (int)wcslen(text_result_ptr_w));
	printf("--------------------------------------------------\n");
	printf("%ws", (NULL == text_result_ptr_w) ? L"NULL\n" : text_result_ptr_w);
	printf("--------------------------------------------------\n");


	// Check against expected result
	//printf("NULL == result --> %s\n", (NULL == result) ? "true" : "false");
	//printf("NULL == text_result_ptr --> %s\n", (NULL == text_result_ptr) ? "true" : "false");
	//printf("strlen(result)=%llu == strlen(text_result_ptr)=%llu --> %s\n", strlen(result), strlen(text_result_ptr), (strlen(result) == strlen(text_result_ptr)) ? "true" : "false");
	//printf("0 == strcmp(result, text_result_ptr) --> %s\n", (0 == strcmp(result, text_result_ptr)) ? "true" : "false");
	if (NULL != result_w && NULL != text_result_ptr_w && wcslen(result_w) == wcslen(text_result_ptr_w) && 0 == wcscmp(result_w, text_result_ptr_w)) {
		printOK();
	} else {
		printNOK();
	}

	// Clear variables
	if (NULL != result_w) {
		free(result_w);
		result_w = NULL;
	}
	if (NULL != text_result_ptr_w) {
		free(text_result_ptr_w);
		text_result_ptr_w = NULL;
	}
	printf("\n");


	// Free
	printf("Before free:\n");
	printf("help_ptr = %p\n", help_ptr);
	freeAdvancedHelp(&help_ptr);
	printf("After free:\n");
	printf("help_ptr = %p\n", help_ptr);
	printf("\n");


}
