#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define PASSWORD_LENGTH 256

int main()
{
	int ret;
	char password[PASSWORD_LENGTH + 1];
	struct termios initial_setting;
	struct termios new_setting;

	ret = tcgetattr(fileno(stdin), &initial_setting);
	if (ret != 0)
	{
		fprintf(stderr, "tcgetattr initial setting error\n");
		return -1;
	}

	new_setting = initial_setting;
	new_setting.c_lflag &= ~ECHO;

	ret = tcsetattr(fileno(stdin), TCSANOW, &new_setting);
	if (ret != 0)
	{
		fprintf(stderr, "tcsetattr new setting error\n");
		return -1;
	}

	printf("please enter your password: ");
	fgets(password, PASSWORD_LENGTH, stdin);
	printf("\npassword is %s", password);
	tcsetattr(fileno(stdin), TCSANOW, &initial_setting);

	return 0;
}
