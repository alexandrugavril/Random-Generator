#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

int getRandom()
{
	unsigned int rnd = 0;
    __builtin_ia32_rdrand32_step(&rnd);
    return rnd;
}

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		printf("Usage: %s <noOfNumbers>\n", argv[0]);
		return -1;
	}
	int numbers = atoi(argv[1]);

	FILE *file = fopen("./sts-2.1.2/randomNumbers.txt", "w");
	for(int i = 0; i < numbers; i++)
	{
		int randf;
	    randf = getRandom();
		char str[31];
		for (int c = 31; c >= 0; c--)
	    {
	        int k = randf >> c;
	    	
	        if (k & 1)
	            str[c] = '1';
	        else
	            str[c] = '0';
	    }

		int results = fprintf(file, "%s\n", str);
	}
	fclose(file);

	char command[200];
	sprintf ( command, "cd sts-2.1.2 && %s %d %s %s", "./assess", numbers, "./randomNumbers.txt", "../summaryFile.txt");
	printf("Running command  %s...\n", command);
	system(command);


    

    return 0;
}