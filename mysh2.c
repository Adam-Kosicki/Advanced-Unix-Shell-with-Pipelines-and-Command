#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define MAXQUOTES 1000
#define MAXLEN 1000
#define MAXCOMMANDS 1000

int fds[100][2];
int numPipes = 1;
char *commands[100];


	char *quotes[MAXQUOTES];
	int numQuotes=0;

void randomQuote(){
	

	char line[MAXLEN];

        FILE *fp = fopen("quotes.txt", "r");
        if (!fp) {
                puts("quotes.txt cannot be opened for reading.");
                exit(1);
        }
        int i=0;

        //read one line at a time, allocate memory, then copy the line into array
        while (fgets(line, MAXLEN, fp)) {
                quotes[i] = (char *) malloc (strlen(line)+1);
                strcpy(quotes[i], line);
                i++;
        }
        numQuotes = i;


        srand(getpid() + time(NULL) + getuid());
}
	

//runs a simple command
void runCommand(char *command) {		
//	use code from execvp2.c 
//	to split line into argument list
//	and invoke execvp()

	char *arguments[MAXLEN], line[MAXLEN];

//        printf("Enter your command: ");
//        fgets(line, MAXLEN, stdin);

        char *c = strtok(command, " \n");
        arguments[0] = c;

        int i=1;
        //keep getting tokens (individual words)
        while ((arguments[i] = strtok(NULL, " \n")) != NULL)
                i++;

//        printf("Invoking: %s\n", command);
//        printf("Arguments: ");
//        for(int j=0; j<i; j++)
//                printf("%s ", arguments[j]);
//        puts("\nExecuting the command now.\n");

        execvp(c, arguments);
        fputs("I hope you don't see me!\n", stderr);
}

// cmd1 | cmd2 | cmd3 
void child(int i){
	//rewire pipes
	//fds[i-1][0] to 0
	if (i > 0) {
		close(0);
		dup(fds[i-1][0]);
	}
		
	//fds[i][1] to 1
	if (i < numPipes) {
		close(1);
		dup(fds[i][1]);
	}

	for(int j=0; j<numPipes; j++) {
		close(fds[j][0]);
		close(fds[j][1]);
	}

	//close all open pipes
	runCommand(commands[i]);
}

void processLine(char *line) {
	char *pipePtr = strchr(line, '|');
	char *equalPtr = strchr(line, '=');
	if (pipePtr){ //not NULL
		//line has one or more | character
		
		// cmd1 | cmd2 | cmd3
		//split input line to multiple commands and count n
		commands[0] = strtok(line, "|\n");
		int numCommands = 1;
		while (commands[numCommands] = strtok(NULL, "|\n"))
			numCommands++;
		numPipes = numCommands - 1;

		for(int i=0; i<numPipes; i++)
			pipe(fds[i]);
		
		for(int i=1; i<numCommands; i++)
			if (fork() == 0)
				child(i);
		child(0);
	}

	else if (equalPtr){
		//Example: "computer = user"
		//line has one = character
		char *cmd1 = line;
		*equalPtr = NULL;
		char *cmd2 = equalPtr+1;

		int tocmd1[2], tocmd2[2];
		pipe(tocmd1);
		pipe(tocmd2);
		if (fork() == 0){
			//replace fd 1 with tocmd1[1]
			close(1);
			dup(tocmd1[1]);
			//replace fd 0 with tocmd2[0]
			close(0);
			dup(tocmd2[0]);

			close(tocmd1[0]);
			close(tocmd1[1]);
			close(tocmd2[0]);
			close(tocmd2[1]);

			//take care of command2
			runCommand(cmd2);
		}
			else {
				//replace fd 0 with tocmd1[0]
				//replace fd 1 with tocmd2[1]
			close(1);
			dup(tocmd2[1]);
			//replace fd 0 with tocmd2[0]
			close(0);
			dup(tocmd1[0]);
				//take care of command1
			close(tocmd1[0]);
			close(tocmd1[1]);
			close(tocmd2[0]);
			close(tocmd2[1]);
			runCommand(cmd1);
			}
	}
	
	else	//it is a simple command
		runCommand(line);
}


int main(){

		randomQuote();
	while (1){
	
//        infinite loop
//        output a random quote
//        output prompt like "# "
// 	  read the input line

      int quoteNumber = rand() % numQuotes;
	  printf("%s", quotes[quoteNumber]);
		printf("# ");
		char line[1000];
     		fgets(line, 1000, stdin);
	        //spawn a child for taking care of it
        	if (fork() == 0)
                	processLine(line);

        	int x=0;
        	wait(&x);
	}

}

