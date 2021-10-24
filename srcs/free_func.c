/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadia <jbadia@student.42quebec.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 15:08:24 by jbadia            #+#    #+#             */
/*   Updated: 2021/10/18 16:46:14 by jbadia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

t_token *free_token_lst(t_token *tok)
{
	t_token *temp;

	temp = NULL;
	while (tok)
	{
		temp = tok->next;
		free(tok);
		tok = temp;
	}
	return (tok);
}