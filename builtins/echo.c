// Logica da nflag pode ou nao ter que ser mudada, dependendo da nossa
// implementacao da chamada da ft_echo Temos de ver se juntamos os varios
// argumentos antes de os passar para o ft_echo ou se passamos os argumentos
// todos e juntamos aqui

#include "../headers/tacoshell.h"

int ft_echo(int nflag, char *arg)
{
	int	i;
	i = 0;

	while (arg[i])
	{
		write(1, &arg[i], 1);
		i++;
	}
	if (!nflag)
		write(1, "\n", 1);
	return (EXIT_SUCCESS);
}
