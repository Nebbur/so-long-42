/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboia-pe <rboia-pe@student.42porto.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:19:58 by rboia-pe          #+#    #+#             */
/*   Updated: 2023/04/07 02:19:58 by rboia-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	get_lines(char *map)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		i++;
	}
	close(fd);
	return (i);
}

void	verify_alloc(void *alloc, game_data *game)
{
	if (alloc == NULL)
	{
		free_to_all(game);
		ft_printf("Erro.\nFalha na alocação de memória.\n");
		exit(EXIT_FAILURE);
	}
}

/*
s_type = sprite_type | define se o sprite é um tile_lava, player, etc..
	1 = player
	2 = tile_rock
	3 = tile_lava
*/

// Função para converter decimal para binário e retornar como inteiro
int	decimal_para_binario(int decimal)
{
	int	binario;
	int	base;
	int	resto;

	base = 1;
	binario = 0;
	if (decimal == 0)
		return (0);
	while (decimal > 0)
	{
		resto = decimal % 2;
		binario = binario + resto * base;
		decimal = decimal / 2;
		base = base * 10;
	}
	return (binario);
}
