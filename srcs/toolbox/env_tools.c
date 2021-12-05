/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzennoun <kzennoun@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 08:42:57 by jchevet           #+#    #+#             */
/*   Updated: 2021/11/12 13:06:42 by kzennoun         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

static char	**cpy_env_to_tab(t_env *env_l, char **env_t)
{
	char	*save;
	int		i;

	i = 0;
	while (env_l)
	{
		if (env_l->value != NULL)
		{
			env_t[i] = ft_strjoin(env_l->name, "=");
			save = env_t[i];
			env_t[i] = ft_strjoin(save, env_l->value);
			free(save);
			if (env_t[i] == NULL)
			{
				ft_free_tab(env_t, i);
				return (NULL);
			}
			i++;
		}
		env_l = env_l->next;
	}
	return (env_t);
}

char	**get_env_tab(t_env *env_l)
{
	char	**env_t;
	int		len;

	len = env_list_size(env_l);
	env_t = ft_calloc(len + 1, sizeof(char *));
	if (env_t == NULL)
		return (NULL);
	env_t = cpy_env_to_tab(env_l, env_t);
	free_env_list(env_l);
	return (env_t);
}

/*
 * Return 1 if it founds "name" in env list and move pointer to it
 * Return 0 if it didn't find "name" and don't move the pointer on list
 */
int	env_seeker(t_env **env_l, const char *name)
{
	t_env	*save;

	if (env_l)
	{
		save = *env_l;
		while (*env_l)
		{
			if (ft_strcmp((*env_l)->name, name) == 0)
				return (1);
			*env_l = (*env_l)->next;
		}
		*env_l = save;
	}
	return (0);
}

void	env_ch_value(t_env *old, char *new)
{
	if (old->value)
		free(old->value);
	old->value = ft_strdup(new);
}

t_env	*get_env_list(char **env_main)
{
	t_env	*env;
	size_t	len;
	int		i;

	i = -1;
	env = NULL;
	while (env_main[++i])
	{
		len = ft_strchr(env_main[i], '=') - env_main[i];
		if (ft_strncmp("OLDPWD=", env_main[i], 7) == 0)
		{
			env_add_back(&env, new_env(\
			ft_substr(env_main[i], 0, len), NULL));
		}
		else
			env_add_back(&env, new_env(ft_substr(env_main[i], 0, len), \
			ft_strdup(env_main[i] + len + 1)));
	}
	return (env);
}
