#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	ft_printf("%s", readline());
	(void)argc;
	(void)argv;
	(void)envp;
}
