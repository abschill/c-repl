#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PROMPT_MSG "custom-repl-msg > "

typedef struct {
	char* buffer;
	size_t buffer_length;
	ssize_t input_length;
} iBuffer;

ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/**
	Create new input buffer for user input
**/
iBuffer* new_ibuffer() {
	iBuffer* input_buffer = (iBuffer*)malloc(sizeof(iBuffer));
	input_buffer->buffer = NULL;
	input_buffer->buffer_length = 0;
	input_buffer->input_length = 0;

	return input_buffer;
}
/**
	close existing buffer from pointer ref
**/
void close_ibuffer(iBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// prompt msg
void pprompt() { printf(PROMPT_MSG); }

/**
	read input buf from user
**/
void read_ibuffer(iBuffer* input_buffer) {
  ssize_t bytes_read =
    	getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

	if (bytes_read <= 0) {
		printf("Error reading input\n");
		exit(EXIT_FAILURE);
	}

	// ignore trailing newline
	input_buffer->input_length = bytes_read - 1;
	input_buffer->buffer[bytes_read - 1] = 0;
}

int main(int argc, char* argv[]) {
	iBuffer* input_buffer = new_ibuffer();
	// loop inf
	while (true) {
		pprompt();
		read_ibuffer(input_buffer);
		// so first we want to establish an "exit" command that simply closes the repl
		if (strcmp(input_buffer -> buffer, ".exit") == 0) {
			close_ibuffer(input_buffer);
			exit(EXIT_SUCCESS);
		}
		// next lets register a "help" command to print some sort of menu to the user
		else if(strcmp(input_buffer -> buffer, ".help") == 0) {
			printf("Help Menu or something\n"); // could read this from manpage.txt or something
			close_ibuffer(input_buffer);
			exit(EXIT_SUCCESS);
		}
		// otherwise just print a no op
		else {
			printf("Unrecognized command '%s'.\n", input_buffer->buffer);
		}
	}
}
