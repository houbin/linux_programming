#include <stdio.h>
#include <stdlib.h>

char *menu[] = {
	"a: add new record",
	"d: delete record",
	"q: quit",
	NULL
};

int GetChoice(char *greet, char *choice[], FILE *in, FILE *out)
{
	int ret;
	char **option;
	int input;
	int selected = 0;

	if (greet != NULL)
		fprintf(out, "\nGetChoice: %s\n", greet);
	
	do 
	{
		option = choice;
		int i = 0;
		while (option[i])
		{
			fprintf(out, "\t %s\n", option[i]);
			i++;
		}

		do
		{
			input = getc(in);
		}while (input == '\n');

		option = choice;
		i = 0;
		while (option[i])
		{
			if (option[i][0] == input)
			{
				selected = 1;
				fprintf(out, "You select choice: %c\n", input);
				break;
			}

			i++;
		}

		if (selected == 0)
		{
			fprintf(out, "input error, please select a new choice\n");
		}
	} while(selected == 0);

	return input;
}

int main()
{
	FILE *in, *out;

	in = fopen("/dev/tty", "r");
	out = fopen("/dev/tty", "w");
	if (!(in && out))
	{
		fprintf(stderr, "fopen tty error!\n");
		return -1;
	}

	int input;
	do
	{
		input = GetChoice("Please select a choice", menu, in, out);
	}while(input != 'q');

	return 0;
}
