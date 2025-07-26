#include "minishell.h"

char	*get_env_value(const char *name, char **envp)
{
	size_t	len;
	int		i;

	i = 0;
	len = ft_strlen(name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*create_env_entry(const char *key, const char *value)
{
	size_t	key_len;
	size_t	val_len;
	char	*entry;

	key_len = ft_strlen(key);
	val_len = ft_strlen(value);
	entry = malloc(key_len + val_len + 2);
	if (!entry)
		return (NULL);
	ft_memcpy(entry, key, key_len);
	entry[key_len] = '=';
	ft_memcpy(entry + key_len + 1, value, val_len);
	entry[key_len + 1 + val_len] = '\0';
	return (entry);
}

char	**overwrite_env(const char *key, const char *value, char **envp)
{
	size_t	key_len;
	char	*new_entry;
	int		count;
	char	**new_envp;
	int		i;

	i = 0;
	key_len = ft_strlen(key);
	new_entry = create_env_entry(key, value);
	if (!new_entry)
		return (envp);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, key_len) == 0 && envp[i][key_len] == '=')
		{
			free(envp[i]);
			envp[i] = new_entry;
			return (envp);
		}
		i++;
	}
	count = 0;
	while (envp[count])
		count++;
	new_envp = malloc(sizeof(char *) * (count + 2));
	if (!new_envp)
	{
		free(new_entry);
		return (envp);
	}
	i = 0;
	while (i < count)
	{
		new_envp[i] = envp[i];
		i++;
	}
	new_envp[count] = new_entry;
	new_envp[count + 1] = NULL;
	free(envp);
	return (new_envp);
}

void	execute_echo(char **args)
{
	int	i;
	int	newline;
	int	j;

	i = 1;
	newline = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (newline)
		write(STDOUT_FILENO, "\n", 1);
}

void	execute_cd(char **args, t_shell *shell)
{
	char	cwd[1024];
	char	*target;
	char	*oldpwd;
	int		needs_free;
	char	*home;
	char	*suffix;

	target = NULL;
	oldpwd = NULL;
	needs_free = 0;
	if (args[2])
	{
		write(STDERR_FILENO, "cd: too many arguments\n",
			ft_strlen("cd: too many arguments\n"));
		shell->last_status = 1;
		return ;
	}
	if (!getcwd(cwd, sizeof(cwd)))
		oldpwd = ft_strdup(get_env_value("PWD", shell->envp));
	else
		oldpwd = ft_strdup(cwd);
	if (!oldpwd)
	{
		perror("cd: failed to get current directory");
		shell->last_status = 1;
		return ;
	}
	if (args[1] && args[1][0] == '-' && ft_strcmp(args[1], "-") != 0
		&& ft_strcmp(args[1], "--") != 0)
	{
		write(STDERR_FILENO, "cd: ", ft_strlen("cd: "));
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, ": invalid option\n",
			ft_strlen(": invalid option\n"));
		free(oldpwd);
		shell->last_status = 2;
		return ;
	}
	if (!args[1] || (args[1][0] == '~' && args[1][1] == '\0')
		|| ft_strcmp(args[1], "--") == 0)
	{
		target = get_env_value("HOME", shell->envp);
		if (!target)
		{
			write(STDERR_FILENO, "cd: HOME not set\n",
				ft_strlen("cd: HOME not set\n"));
			free(oldpwd);
			shell->last_status = 1;
			return ;
		}
		needs_free = 0;
	}
	else if (args[1][0] == '~' && args[1][1] == '/')
	{
		home = get_env_value("HOME", shell->envp);
		if (!home)
		{
			write(STDERR_FILENO, "cd: HOME not set\n",
				ft_strlen("cd: HOME not set\n"));
			free(oldpwd);
			shell->last_status = 1;
			return ;
		}
		suffix = args[1] + 1;
		target = malloc(ft_strlen(home) + ft_strlen(suffix) + 1);
		if (!target)
		{
			perror("malloc");
			free(oldpwd);
			shell->last_status = 1;
			return ;
		}
		ft_strcpy(target, home);
		ft_strcat(target, suffix);
		needs_free = 1;
	}
	else if (ft_strcmp(args[1], "-") == 0)
	{
		target = get_env_value("OLDPWD", shell->envp);
		if (!target)
		{
			write(STDERR_FILENO, "cd: OLDPWD not set\n",
				ft_strlen("cd: OLDPWD not set\n"));
			free(oldpwd);
			shell->last_status = 1;
			return ;
		}
		write(STDOUT_FILENO, target, ft_strlen(target));
		write(STDOUT_FILENO, "\n", 1);
		needs_free = 0;
	}
	else
	{
		target = args[1];
		needs_free = 0;
	}
	if (!target || chdir(target) != 0)
	{
		perror("cd");
		if (needs_free)
			free(target);
		free(oldpwd);
		shell->last_status = 1;
		return ;
	}
	shell->envp = overwrite_env("OLDPWD", oldpwd, shell->envp);
	free(oldpwd);
	if (getcwd(cwd, sizeof(cwd)))
		shell->envp = overwrite_env("PWD", cwd, shell->envp);
	else
		shell->envp = overwrite_env("PWD", target, shell->envp);
	if (needs_free)
		free(target);
	shell->last_status = 0;
}

void	execute_pwd(void)
{
	char	cwd[1024];
	char	*fallback_pwd;

	if (getcwd(cwd, sizeof(cwd)))
	{
		printf("%s\n", cwd);
	}
	else
	{
		fallback_pwd = getenv("PWD");
		if (fallback_pwd)
			printf("%s\n", fallback_pwd);
		else
			perror("pwd");
	}
}

int	is_valid_identifier(const char *str)
{
	int	i;

	i = 1;
	if (!str || !str[0])
		return (0);
	if (!isalpha(str[0]) && str[0] != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	execute_export(char **args, t_shell *shell)
{
	char	*eq;
	char	*plus_eq;
	char	key[256];
	size_t	key_len;
	char	*append_val;
	char	*old_val;
	char	*new_val;
	char	**env_ptr;
	char	**arg_ptr;

	if (!args[1])
	{
		env_ptr = shell->envp;
		while (*env_ptr)
		{
			eq = ft_strchr(*env_ptr, '=');
			if (eq)
			{
				*eq = '\0';
				printf("declare -x %s=\"%s\"\n", *env_ptr, eq + 1);
				*eq = '=';
			}
			else
				printf("declare -x %s\n", *env_ptr);
			env_ptr++;
		}
		return ;
	}
	if (args[1][0] == '-')
	{
		write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, "': invalid option\n",
			ft_strlen("': invalid option\n"));
		shell->last_status = 2;
		return ;
	}
	arg_ptr = &args[1];
	while (*arg_ptr)
	{
		plus_eq = ft_strstr(*arg_ptr, "+=");
		if (plus_eq)
		{
			key_len = plus_eq - *arg_ptr;
			ft_memcpy(key, *arg_ptr, key_len);
			key[key_len] = '\0';
			if (!is_valid_identifier(key))
			{
				write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
				write(STDERR_FILENO, *arg_ptr, ft_strlen(*arg_ptr));
				write(STDERR_FILENO, "': not a valid identifier\n",
					ft_strlen("': not a valid identifier\n"));
				shell->last_status = 1;
			}
			else
			{
				append_val = plus_eq + 2;
				old_val = get_env_value(key, shell->envp);
				if (old_val)
					new_val = ft_strjoin(old_val, append_val);
				else
					new_val = ft_strdup(append_val);
				shell->envp = overwrite_env(key, new_val, shell->envp);
				free(new_val);
			}
		}
		else
		{
			eq = ft_strchr(*arg_ptr, '=');
			if (eq)
			{
				*eq = '\0';
				if (!is_valid_identifier(*arg_ptr))
				{
					write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
					write(STDERR_FILENO, *arg_ptr, ft_strlen(*arg_ptr));
					write(STDERR_FILENO, "': not a valid identifier\n",
						ft_strlen("': not a valid identifier\n"));
					*eq = '=';
					shell->last_status = 1;
					return ;
				}
				shell->envp = overwrite_env(*arg_ptr, eq + 1, shell->envp);
				*eq = '=';
			}
			else
			{
				if (!is_valid_identifier(*arg_ptr))
				{
					write(STDERR_FILENO, "export: `", ft_strlen("export: `"));
					write(STDERR_FILENO, *arg_ptr, ft_strlen(*arg_ptr));
					write(STDERR_FILENO, "': not a valid identifier\n",
						ft_strlen("': not a valid identifier\n"));
					shell->last_status = 1;
					return ;
				}
				shell->envp = overwrite_env(*arg_ptr, "", shell->envp);
			}
		}
		arg_ptr++;
	}
}

void	execute_unset(char **args, t_shell *shell)
{
	size_t	key_len;
	char	**arg_ptr;
	int		env_idx;
	char	**shift_ptr;

	if (!args[1])
		return ;
	arg_ptr = &args[1];
	while (*arg_ptr)
	{
		if ((*arg_ptr)[0] == '-')
		{
			write(STDERR_FILENO, "unset: `", ft_strlen("unset: `"));
			write(STDERR_FILENO, &(*arg_ptr)[0], 1);
			write(STDERR_FILENO, &(*arg_ptr)[1], 1);
			write(STDERR_FILENO, "': invalid option\n",
				ft_strlen("': invalid option\n"));
			shell->last_status = 2;
			return ;
		}
		env_idx = 0;
		while ((shell->envp)[env_idx])
		{
			key_len = ft_strlen(*arg_ptr);
			if (ft_strncmp((shell->envp)[env_idx], *arg_ptr, key_len) == 0
				&& (shell->envp)[env_idx][key_len] == '=')
			{
				free((shell->envp)[env_idx]);
				shift_ptr = &((shell->envp)[env_idx]);
				while (*shift_ptr)
				{
					*shift_ptr = *(shift_ptr + 1);
					shift_ptr++;
				}
				break ;
			}
			env_idx++;
		}
		arg_ptr++;
	}
}

void	execute_env(char **args, t_shell *shell)
{
	int	i;

	i = 0;
	if (args[1])
	{
		write(STDERR_FILENO, "env: ", ft_strlen("env: "));
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, ": No such file or directory\n",
			ft_strlen(": No such file or directory\n"));
		shell->last_status = 127;
		return ;
	}
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			printf("%s\n", shell->envp[i]);
		i++;
	}
	shell->last_status = 0;
}

int	non_number(char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (!((c[i] >= '0' && c[i] <= '9') || c[i] == '-' || c[i] == '+'))
			return (1);
		i++;
	}
	return (0);
}

void	execute_exit(char **args)
{
	int			arg_count;
	long long	status;

	arg_count = 0;
	while (args[arg_count])
		arg_count++;
	if (!args[1])
		exit(0);
	if (non_number(args[1]))
	{
		write(1, "exit\n", 5);
		write(STDERR_FILENO, "exit: ", ft_strlen("exit: "));
		write(STDERR_FILENO, args[1], ft_strlen(args[1]));
		write(STDERR_FILENO, ": numeric argument required\n",
			ft_strlen(": numeric argument required\n"));
		exit(2);
	}
	if (arg_count > 2)
	{
		write(STDERR_FILENO, "exit: too many arguments\n",
			ft_strlen("exit: too many arguments\n"));
		exit(1);
	}
	if (arg_count == 2)
	{
		status = ft_atoll(args[1]) % 256;
		exit(status);
	}
	exit(0);
}

int	execute_builtin(char **args, t_shell *shell)
{
	if (!ft_strncmp(args[0], "echo", 5))
		execute_echo(args);
	else if (!ft_strncmp(args[0], "cd", 3))
	{
		execute_cd(args, shell);
		return (shell->last_status);
	}
	else if (!ft_strncmp(args[0], "pwd", 4))
		execute_pwd();
	else if (!ft_strncmp(args[0], "export", 7))
	{
		execute_export(args, shell);
		return (shell->last_status);
	}
	else if (!ft_strncmp(args[0], "unset", 6))
	{
		execute_unset(args, shell);
		return (shell->last_status);
	}
	else if (!ft_strncmp(args[0], "env", 4))
	{
		execute_env(args, shell);
		return (shell->last_status);
	}
	else if (!ft_strncmp(args[0], "exit", 5))
		execute_exit(args);
	return (0);
}
