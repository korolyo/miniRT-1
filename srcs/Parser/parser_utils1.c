/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zurag <zurag@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 19:52:16 by zurag             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/03/08 19:27:33 by acollin          ###   ########.fr       */
=======
/*   Updated: 2022/03/09 20:36:38 by zurag            ###   ########.fr       */
>>>>>>> miniRT/zurag
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_numbers_vec(char **num, t_vect *vec)
{
	vec->x = ft_atof(num[0]);
	vec->y = ft_atof(num[1]);
	vec->z = ft_atof(num[2]);
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
