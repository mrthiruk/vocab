#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>

#define LBUFF_SIZE	350

/*	Function Declarations	*/
int help(void);
int edit(void);
int add(void);
int list(void);
unsigned short op_list_size();


/*	Function Pointers	*/
int (*operations[])() = {
	&help,
	&edit,
	&add,
	&list,
};


/*	Op-strings	*/
char *op_list[] = {
	"-h",
	"-e",
	"-a",
	"-l",
};

/* Path to the database	*/
char pathname[250] = {0};

int main(int argc, char **argv){
	if(argc == 1){
		operations[0]();
		return 0;
	}
	
	/* Initializing path	*/
	strcpy(pathname, getenv("HOME"));
	strcat(pathname, "/Documents/test.md");

	for(unsigned i=0; i<op_list_size(); i++){
		if(!strcmp(argv[1], op_list[i])){
			operations[i]();
			return 0;
		}
	}
	puts("vocab:\tInvalid flag encountered.\n");
	help();
	return 0;
}

int help(){
	printf(
	"vocab:  A utility to improve your passive vocabulary.\n\nOptions:\n"
	"\t-a\tadd new words to the database\n"
	"\t-e\tedit the database\n"
	"\t-h\tdisplay this help message\n"
	"\t-l\tlist the words in the database\n"
	);
	return 0;
}

int edit(){
	FILE *fp = fopen(pathname, "r");
	char *editor = "/usr/bin/nvim";
	execl(editor, editor, pathname, (char*) NULL);
	fclose(fp);
	return 0;
}

int add(){
	FILE *fp = fopen(pathname, "a+");
	char word[55] = {0};
	char part_of_speech[52] = {0};
	char line_buffer[LBUFF_SIZE+10] = {0};
	char word_buffer[50] = {0};
	unsigned meaning_count = 1;
	
	/*	Adding Word	*/
	printf("Word:\t\t\t\t");
	scanf("%s", word_buffer);
	sprintf(word, "**%s**\n", word_buffer);
	fputs(word, fp);

	/*	Adding Part of Speech	*/
	printf("Part of speech:\t\t");
	scanf("%s", word_buffer);
	getchar();
	sprintf(part_of_speech, "%s.\n", word_buffer);
	part_of_speech[0] = toupper(part_of_speech[0]);
	fputs(part_of_speech, fp);
	
	/*	Adding Meanings	*/
	while(1){
		sprintf(line_buffer, "%u. ", meaning_count);
		printf("Meaning %u:\t", meaning_count);
		fgets(line_buffer+3, LBUFF_SIZE, stdin);
		if(line_buffer[3] == 'q') break;
		line_buffer[3] = toupper(line_buffer[3]);
		fputs(line_buffer, fp);
		meaning_count++;
	}
	sprintf(line_buffer, "e.g. *");
	printf("Example:\t");
	fgets(line_buffer+6, LBUFF_SIZE, stdin);
	sprintf(line_buffer + strlen(line_buffer) - 1, "*\n\\\n\n");
	fputs(line_buffer, fp);
	fclose(fp);
	return 0;
}

int list(){
	FILE *fp = fopen(pathname, "r");
	char line_buffer[LBUFF_SIZE] = {0};
	unsigned line_end;
	puts("Word List:\n");
	while(fgets(line_buffer, LBUFF_SIZE, fp)){
		line_end = strchr(line_buffer, '\n') - line_buffer;
		line_buffer[line_end] = '\0';
		if(line_buffer[0] == '*'){
			line_buffer[line_end - 2] = '\0';
			line_buffer[1] = ' ';
			printf("%s\n", line_buffer);
		}
	}
	fclose(fp);
	return 0;
}

unsigned short op_list_size(){
	return sizeof(op_list) / sizeof(op_list[0]);
}
