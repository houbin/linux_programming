#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a: add new record",
	"d: delete record",
	"q: quit",
	NULL
};

int GetChoice(char *greet, char *choice[])
{
	int ret;
	char **option;
	int input;
	int selected = 0;

	if (greet != NULL)
		printf("\nGetChoice: %s\n", greet);
	
	do 
	{
		option = choice;
		int i = 0;
		while (option[i])
		{
			printf("\t %s\n", option[i]);
			i++;
		}

		do
		{
			input = getchar();
		}while (input == '\n');

		option = choice;
		i = 0;
		while (option[i])
		{
			if (option[i][0] == input)
			{
				selected = 1;
				printf("You select choice: %c\n", input);
				break;
			}

			i++;
		}

		if (selected == 0)
		{
			printf("input error, please select a new choice\n");
		}
	} while(selected == 0);

	return input;
}

int main()
{
	int input;
	do
	{
		input = GetChoice("Please select a choice", menu);
	}while(input != 'q');

	return 0;
}
