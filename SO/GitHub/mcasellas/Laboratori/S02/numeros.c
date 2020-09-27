#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int
esNumero(char *str)
{
	const int	MAX_SIZE = 8;



	int		result;
	char		noustr    [strlen(str)];

	result = atoi(str);
	sprintf(noustr, "%d", result);


	result = strlen(noustr);

	if (str[0] == '-')
		--result;



	if (result > MAX_SIZE || strlen(noustr) != strlen(str))
		return 0;
	else
		return 1;



}

int
main(int argc, char *argv[])
{
	char		buf       [80];
	int		i;
	for (i = 1; i < argc; i++) {
		//Obviem el nom del executable amb i = 1
			if (1 == esNumero(argv[i])) {
			sprintf(buf, "%s sí és un número\n", argv[i]);
		} else
			sprintf(buf, "%s no és un número\n", argv[i]);
		write(1, buf, strlen(buf));
	}
	return 0;
}
