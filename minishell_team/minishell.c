#include "minishell.h"


int	is_redirection(const char *s)
{
	return (!ft_strcmp(s, ">") || !ft_strcmp(s, ">>")
		|| !ft_strcmp(s, "<") || !ft_strcmp(s, "<<"));
}

int	is_operator(const char *s)
{
	return (is_redirection(s) || !ft_strcmp(s, "|"));
}


static int is_all_redirection_chars(const char *s)
{
    int i;

    i = 0;
    if (!s || !*s)
        return 0;
    while (s[i])
    {
        if (s[i] != '>' && s[i] != '<')
            return 0;
        i++;
    }
    return 1;
}

static int contains_operator_char(const char *s)
{
    int i;
    i = 0;
    while (s[i])
    {
        if (s[i] == '<' || s[i] == '>')
            return 1;
        i++;
    }
    return 0;
}

int validate_syntax_tokens(t_token *tokens, t_shell *shell)
{
    for (int i = 0; tokens[i].value; i++)
    {
        const char *cur = tokens[i].value;
        const char *next = tokens[i + 1].value;

        if (is_all_redirection_chars(cur) && ft_strlen(cur) > 2)
        {
            fprintf(stderr, "syntax error near unexpected token `%s'\n", cur);
            shell->last_status = 2;
            return 0;
        }

        if (is_redirection(cur))
        {
            if (!next)
            {
                fprintf(stderr, "syntax error near unexpected token `newline'\n");
                shell->last_status = 2;
                return 0;
            }
            if (is_operator(next))
            {
                fprintf(stderr, "syntax error near unexpected token `%s'\n", next);
                shell->last_status = 2;
                return 0;
            }
            if (contains_operator_char(next))
            {
                fprintf(stderr, "syntax error near unexpected token `newline'\n");
                shell->last_status = 2;
                return 0;
            }
        }

        if (is_redirection(cur) && next && is_redirection(next))
        {
            fprintf(stderr, "syntax error near unexpected token `%s'\n", next);
            shell->last_status = 2;
            return 0;
        }
    }
    return 1;
}

char *expand_variables(const char *str, t_shell *shell)
{
    char *result = ft_calloc(1, 1);
    size_t i = 0;
    char quote = 0;

    while (str[i])
    {
        if (is_quote(str[i]))
        {
            if (quote == 0)
                quote = str[i];
            else if (quote == str[i])
                quote = 0;
            else
            {
                result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + 2);
                ft_strcat(result, (char[2]){str[i], 0});
            }
            i++;
            continue;
        }

        if (quote != '\'' && str[i] == '$')
        {
            i++;
            char var_name[256] = {0};
            int k = 0;

            if (str[i] == '?')
            {
                char status_str[12];
                sprintf(status_str, "%d", shell->last_status);
                result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + ft_strlen(status_str) + 1);
                ft_strcat(result, status_str);
                i++;
                continue;
            }
            
            if (!ft_isalpha(str[i]) && str[i] != '_')
            {
                 result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + 2);
                 ft_strcat(result, "$");
                 continue;
            }

            while (ft_isalnum(str[i]) || str[i] == '_')
                var_name[k++] = str[i++];
            
            char *val = get_env_value(var_name, shell->envp);
            if (val)
            {
                result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + ft_strlen(val) + 1);
                ft_strcat(result, val);
            }
        }
        else 
        {
            result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + 2);
            ft_strcat(result, (char[2]){str[i], 0});
            i++;
        }
    }
    return result;
}

char *expand_variables_with_control(const char *str, t_shell *shell, int preserve_quotes)
{
	char *expanded = expand_variables(str, shell);
	if (preserve_quotes)
		return expanded;

	char quote_type;
	char *stripped = strip_quotes(expanded, &quote_type);
	free(expanded);
	return stripped;
}

char *expand_variables_no_quotes(const char *str, t_shell *shell)
{
	char *result = ft_calloc(1, 1);
	size_t i = 0;

	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			char var_name[256] = {0};
			int k = 0;

			if (str[i] == '?')
			{
				char status_str[12];
				sprintf(status_str, "%d", shell->last_status);
				result = ft_realloc(result, ft_strlen(result) + 1,
					ft_strlen(result) + ft_strlen(status_str) + 1);
				ft_strcat(result, status_str);
				i++;
				continue;
			}

			while (ft_isalnum(str[i]) || str[i] == '_')
				var_name[k++] = str[i++];

			char *val = get_env_value(var_name, shell->envp);
			if (val)
			{
				result = ft_realloc(result, ft_strlen(result) + 1,
					ft_strlen(result) + ft_strlen(val) + 1);
				ft_strcat(result, val);
			}
		}
		else
		{
			result = ft_realloc(result, ft_strlen(result) + 1, ft_strlen(result) + 2);
			ft_strcat(result, (char[2]){str[i], 0});
			i++;
		}
	}
	return result;
}

static int contains_unquoted_dollar(const char *s)
{
    char quote = 0;
    int i = 0;
    while(s[i])
    {
        if (is_quote(s[i]))
        {
            if (quote == 0)
                quote = s[i];
            else if (quote == s[i])
                quote = 0;
        }
        if (s[i] == '$' && quote != '\'')
            return (1);
        i++;
    }
    return (0);
}

char **expand_variables_and_split(const char *str, t_shell *shell, int preserve_quotes)
{
    int should_split = contains_unquoted_dollar(str);
    char **final_args;

    if (preserve_quotes) {
        should_split = 0;
    }

    char *expanded_str = expand_variables(str, shell);

    if (should_split)
    {
        final_args = ft_split(expanded_str, ' ');
    }
    else
    {
        final_args = ft_calloc(2, sizeof(char *));
        if (final_args)
        {
            char quote_type;
            final_args[0] = strip_quotes(expanded_str, &quote_type);
        }
    }
    
    free(expanded_str);
    return final_args;
}


char **split_args_with_expansion(const char *cmd, t_shell *shell)
{
	t_token *tokens = shell_split(cmd);
	if (!tokens)
		return NULL;

    int args_cap = 16;
    char **final_args = ft_calloc(args_cap, sizeof(char*));
    if (!final_args) {
        free_tokens(tokens);
        return NULL;
    }
    int args_count = 0;

	int is_export = tokens[0].value && ft_strcmp(tokens[0].value, "export") == 0;

	for (int i = 0; tokens[i].value; i++)
	{
		if (ft_strcmp(tokens[i].value, "<") == 0 ||
			ft_strcmp(tokens[i].value, ">") == 0 ||
			ft_strcmp(tokens[i].value, ">>") == 0 ||
			ft_strcmp(tokens[i].value, "<<") == 0 ||
			(tokens[i].value[0] >= '0' && tokens[i].value[1] == '>'))
		{
			i++;
			continue;
		}

		char **sub_args = NULL;
		int preserve = (is_export && i > 0);

		if (tokens[i].quote == '\'') {
            sub_args = ft_calloc(2, sizeof(char*));
            if (sub_args)
			{
                char quote_type;
                sub_args[0] = strip_quotes(tokens[i].value, &quote_type);
            }
        }
		else
		{
            sub_args = expand_variables_and_split(tokens[i].value, shell, preserve);
        }

        if (!sub_args)
		{
            continue;
        }

        for (int k = 0; sub_args[k]; k++)
		{
            if (args_count >= args_cap - 1) {
                int old_cap = args_cap;
                args_cap *= 2;
                final_args = ft_realloc(final_args, old_cap * sizeof(char*), args_cap * sizeof(char*));
            }
            final_args[args_count] = ft_strdup(sub_args[k]);
			args_count++;
        }
        ft_free_split(sub_args);
	}
	final_args[args_count] = NULL;
	free_tokens(tokens);
	return final_args;
}

void	ft_free_split(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	is_unclosed_quote(const char *line)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		if (!quote && (line[i] == '\'' || line[i] == '"'))
			quote = line[i];
		else if (quote && line[i] == quote)
			quote = 0;
		i++;
	}
	return (quote != 0);
}

char	**copy_envp(char **envp)
{
	int		count;
	char	**copy;

	count = 0;
	while (envp[count])
		count++;
	copy = malloc(sizeof(char *) * (count + 1));
	if (!copy)
		return (NULL);
	for (int i = 0; i < count; i++)
		copy[i] = ft_strdup(envp[i]);
	copy[count] = NULL;
	return (copy);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	my_rand(int max)
{
	static unsigned int	lcg_seed = 123456789;

	lcg_seed = (lcg_seed * 1103515245 + 12345) % 0x7FFFFFFF;
	return (lcg_seed % max);
}


int setup_heredoc(char *limiter, t_shell *shell)
{
	int		fd;
	char	*line;
	char	tmp_file[1000];

	sprintf(tmp_file, "/tmp/%d.tmp", my_rand(2147483647));
	fd = open(tmp_file, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd < 0)
		return (-1);

	while (1)
	{
		line = readline("> ");
		if (!line)
			break;

		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break;
		}

		char *expanded = expand_variables(line, shell);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(line);
	}
	close(fd);
	return open(tmp_file, O_RDONLY);
}

static char	*join_path_cmd(char *path, char *cmd)
{
	char	*full;
	size_t	len;

	len = ft_strlen(path) + ft_strlen(cmd) + 2;
	full = malloc(len);
	if (!full)
		return (NULL);
	ft_strcpy(full, path);
	ft_strcat(full, "/");
	ft_strcat(full, cmd);
	return (full);
}

static char	*find_full_path(char *cmd, char **envp, int i)
{
	char	**paths;
	char	*path_env;
	char	*full_path;

	path_env = envp[i] + 5;
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full_path = join_path_cmd(paths[i], cmd);
		if (access(full_path, X_OK) == 0)
		{
			while (paths[i])
				free(paths[i++]);
			return (free(paths), full_path);
		}
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	return (free(paths), NULL);
}


char	*find_path(char *cmd, char **envp)
{
	char	*full_path;
	int		i = 0;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		else
			return NULL;
	}

	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;

	if (!envp[i])
	{
		const char *fallback_paths[] = { "/bin", "/usr/bin", NULL };
		for (int j = 0; fallback_paths[j]; j++)
		{
			full_path = join_path_cmd((char *)fallback_paths[j], cmd);
			if (access(full_path, X_OK) == 0)
				return full_path;
			free(full_path);
		}
		return NULL;
	}

	return find_full_path(cmd, envp, i);
}

int has_whitespace(const char *str)
{
    if (!str)
        return 0;
    
    while (*str)
    {
        if (*str == ' ' || *str == '\t')
            return 1;
        str++;
    }
    return 0;
}

void    execute_cmd(t_cmd *cmd_node, t_shell *shell)
{
    char **args = cmd_node->args;
    char *cmd = args[0];

	int i = 0;
	while(!cmd || is_empty_or_whitespace(cmd))
	{
		if(!args[i + 1])
			exit(0);
		cmd = args[i + 1];
		i++;
	}
	if (ft_strcmp(cmd, ".") == 0)
	{
		fprintf(stderr, ".: filename argument required\n");
		exit(2);
	}

	if(ft_strcmp(cmd, "~") == 0)
	{
		fprintf(stderr, "Is a directory");
		exit(126);
	}

	if (ft_strcmp(cmd, "..") == 0)
	{
		fprintf(stderr, "..: command not found\n");
		exit(127);
	}

    struct stat sb;
    if (ft_strchr(cmd, '/'))
    {
        if (stat(cmd, &sb) == -1)
        {
            fprintf(stderr, "%s: %s\n", cmd, strerror(errno));
			exit(127);
        }
        if (S_ISDIR(sb.st_mode))
        {
            fprintf(stderr, "%s: Is a directory\n", cmd);
			exit(126);
        }
        if (access(cmd, X_OK) == -1)
        {
            fprintf(stderr, "%s: %s\n", cmd, strerror(errno));
			exit(126);
        }
        execve(cmd, args, shell->envp);
        perror(cmd);
		exit(126);
    }

    if (is_builtin(cmd))
    {
        shell->last_status = execute_builtin(args, shell);
        exit(shell->last_status);
    }

    char *path = find_path(cmd, shell->envp);
    if (!path)
    {
        fprintf(stderr, "%s: command not found\n", cmd);
		exit(127);
    }
    execve(path, args, shell->envp);
    perror(path);
    exit(126);
}

int	is_builtin(char *cmd)
{
	return (!ft_strcmp(cmd, "echo") || !ft_strcmp(cmd, "cd")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "exit"));
}

void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].value)
		free(tokens[i++].value);
	free(tokens);
}

void parse_redirection_token(t_token *op_token, t_token *file_tok, t_cmd *cmd, t_shell *shell)
{
	if (cmd->has_redir_error)
		return;
	if (!op_token || !file_tok || !file_tok->value)
		return;

	char *expanded_path;

	if (ft_strcmp(op_token->value, "<<") == 0)
	{
		expanded_path = ft_strdup(file_tok->value);
	}
	else if (file_tok->quote == '\'')
	{
		expanded_path = ft_strdup(file_tok->value);
	}
	else
	{
		expanded_path = expand_variables(file_tok->value, shell);
	}

	const char *path = expanded_path;
	int fd = -1;
	int target_fd = STDOUT_FILENO;

	if (ft_strcmp(op_token->value, "<") == 0)
		fd = open(path, O_RDONLY);
	else if (ft_strcmp(op_token->value, ">") == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (ft_strcmp(op_token->value, ">>") == 0)
		fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (ft_strcmp(op_token->value, "<<") == 0)
		fd = setup_heredoc((char *)path, shell);
	else if (op_token->value[0] >= '0' && op_token->value[1] == '>')
	{
		target_fd = op_token->value[0] - '0';
		if (op_token->value[2] == '>')
			fd = open(path, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);

		if (fd == -1)
		{
			struct stat sb;
			if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
				fprintf(stderr, "%s: Is a directory\n", path);
			else
				perror(path);
			cmd->has_redir_error = 1;
			free(expanded_path);
			return;
		}

		if (dup2(fd, target_fd) == -1)
		{
			perror("dup2");
			close(fd);
			cmd->has_redir_error = 1;
			free(expanded_path);
			return;
		}
		close(fd);
		free(expanded_path);
		return;
	}

	if (fd == -1)
	{
		struct stat sb;
		if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
			fprintf(stderr, "%s: Is a directory\n", path);
		else
			perror(path);
		cmd->has_redir_error = 1;
		free(expanded_path);
		return;
	}

	if (op_token->value[0] == '<')
	{
		if (cmd->infile != STDIN_FILENO && cmd->infile != -1)
			close(cmd->infile);
		cmd->infile = fd;
	}
	else
	{
		if (cmd->outfile != STDOUT_FILENO && cmd->outfile != -1)
			close(cmd->outfile);
		cmd->outfile = fd;
	}

	free(expanded_path);
}

static t_cmd	*new_cmd_node(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->has_redir_error = 0;
	cmd->infile = STDIN_FILENO;
	cmd->outfile = STDOUT_FILENO;
	cmd->next = NULL;
	return (cmd);
}

static int  is_space(char c)
{
	return (c == ' ' || c == '\t');
}
int  is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int  is_op_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static const char *two_char_op(const char *s)
{
    if (!s[0] || !s[1])
		return NULL;
    if ((s[0] == '<' && s[1] == '<') || (s[0] == '>' && s[1] == '>'))
        return s;
    return NULL;
}

static int is_fd_redirection(const char *s)
{
	if (!s || !s[0] || !s[1])
		return 0;
	if ((s[0] >= '0' && s[0] <= '9') &&
		(s[1] == '>' || s[1] == '<'))
		return 1;
	return 0;
}

t_token *shell_split(const char *s)
{
	size_t   cap = TOK_INIT_CAP, j = 0;
	t_token *tok = malloc(sizeof(t_token) * cap);
	if (!tok)
		return NULL;

	size_t i = 0;
	while (s[i])
	{
		while (is_space(s[i]))
			i++;
		if (!s[i])
			break;

		if (s[i] == '>' && s[i + 1] == '|')
		{
			if (j + 1 >= cap) {
				size_t old = sizeof(t_token) * cap;
				cap *= 2;
				tok = ft_realloc(tok, old, sizeof(t_token) * cap);
			}
			tok[j].value = ft_strndup(&s[i], 2);
			tok[j].quote = 0;
			j++;
			i += 2;
			continue;
		}

		if (two_char_op(&s[i]) || is_fd_redirection(&s[i]))
		{
			char op[4] = {0};
			op[0] = s[i];
			op[1] = s[i + 1];
			if (s[i + 1] && s[i + 1] == '>' && s[i + 2] && s[i + 2] == '>')
			{
				op[2] = s[i + 2];
				i += 3;
			}
			else
				i += 2;

			if (j + 1 >= cap) {
				size_t old = sizeof(t_token) * cap;
				cap *= 2;
				tok = ft_realloc(tok, old, sizeof(t_token) * cap);
			}
			tok[j].value = ft_strdup(op);
			tok[j].quote = 0;
			j++;
			continue;
		}

		if (is_op_char(s[i]))
		{
			char op[2] = { s[i], 0 };
			if (j + 1 >= cap) {
				size_t old = sizeof(t_token) * cap;
				cap *= 2;
				tok = ft_realloc(tok, old, sizeof(t_token) * cap);
			}
			tok[j].value = ft_strdup(op);
			tok[j].quote = 0;
			j++;
			i++;
			continue;
		}

		size_t start = i;
		int    quote = 0;
		while (s[i] && (!is_space(s[i]) || quote) && !(!quote && is_op_char(s[i])))
		{
			if (is_quote(s[i]))
			{
				if (!quote)
					quote = s[i];
				else if (quote == s[i])
					quote = 0;
			}
			i++;
		}
		if (j + 1 >= cap) {
			size_t old = sizeof(t_token) * cap;
			cap *= 2;
			tok = ft_realloc(tok, old, sizeof(t_token) * cap);
		}
		tok[j].value = ft_strndup(s + start, i - start);
		tok[j].quote = 0;
		j++;
	}


	tok[j].value = NULL;
	tok[j].quote = 0;
	return tok;
}

char	*strip_quotes(const char *str, char *quote_type)
{
	size_t	len = ft_strlen(str);

	if (len >= 2 && ((str[0] == '\'' && str[len - 1] == '\'') || (str[0] == '"' && str[len - 1] == '"')))
	{
		*quote_type = str[0];
		return ft_strndup(str + 1, len - 2);
	}
	else
	{
		*quote_type = 0;
		return ft_strdup(str);
	}
}

void	free_cmd_list(t_cmd *head)
{
	t_cmd *tmp;

	while (head)
	{
		tmp = head;

		if (tmp->infile != STDIN_FILENO && tmp->infile != -1)
			close(tmp->infile);

		if (tmp->outfile != STDOUT_FILENO && tmp->outfile != -1)
			close(tmp->outfile);

		ft_free_split(tmp->args);

		head = head->next;
		free(tmp);
	}
}

static void add_arg_to_cmd(t_cmd *cmd, char *arg)
{
    int count = 0;
    if (cmd->args)
    {
        while (cmd->args[count])
            count++;
    }

    char **new_args = malloc(sizeof(char *) * (count + 2));
    if (!new_args)
        return;

    for (int i = 0; i < count; i++)
        new_args[i] = cmd->args[i];

    new_args[count] = ft_strdup(arg);
    new_args[count + 1] = NULL;

    if (cmd->args)
        free(cmd->args);
    
    cmd->args = new_args;
}

t_cmd *parse_commands(char *line, t_shell *shell)
{
	t_cmd   *head = NULL;
	t_cmd   *curr = NULL;
	t_cmd   *iter = NULL;
	t_token *tokens = shell_split(line);

	if (!tokens || !tokens[0].value)
	{
		free_tokens(tokens);
		return NULL;
	}
	if (!validate_syntax_tokens(tokens, shell))
	{
		free_tokens(tokens);
		free_cmd_list(head);
		return NULL;
	}

	for (int i = 0; tokens && tokens[i].value; i++)
	{
		if (ft_strcmp(tokens[i].value, "|") == 0)
		{
			if (!curr || !curr->args || !curr->args[0])
			{
				fprintf(stderr, "syntax error near unexpected token `|'\n");
				shell->last_status = 2;
				free_tokens(tokens);
				free_cmd_list(head);
				return NULL;
			}
			curr = NULL;
			continue;
		}

		if (!curr)
		{
			curr = new_cmd_node();
			curr->args = ft_calloc(1, sizeof(char *));
			if (!head)
				head = curr;
			else
			{
				iter = head;
				while (iter->next)
					iter = iter->next;
				iter->next = curr;
			}
		}

		if (tokens[i].quote == 0
			&& (ft_strcmp(tokens[i].value, "<")  == 0
			 || ft_strcmp(tokens[i].value, ">")  == 0
			 || ft_strcmp(tokens[i].value, "<<") == 0
			 || ft_strcmp(tokens[i].value, ">>") == 0))
		{
			if (!tokens[i + 1].value || is_operator(tokens[i + 1].value))
			{
				fprintf(stderr, "syntax error near unexpected token `%s'\n", tokens[i + 1].value ? tokens[i + 1].value : "newline");
				shell->last_status = 2;
				free_tokens(tokens);
				free_cmd_list(head);
				return NULL;
			}

			parse_redirection_token(&tokens[i], &tokens[i + 1], curr, shell);
			i++;
			continue;
		}


		char **expanded_args = expand_variables_and_split(tokens[i].value, shell, 0);
		if (expanded_args)
		{
			for (int j = 0; expanded_args[j]; j++)
				add_arg_to_cmd(curr, expanded_args[j]);
			ft_free_split(expanded_args);
		}
	}

	free_tokens(tokens);
	return head;
}

int check_redirection_errors(t_cmd *cmds)
{
	t_cmd *current = cmds;
	int has_error = 0;

	while (current)
	{
		if (current->infile == -1 || current->outfile == -1)
		{
			has_error = 1;
		}
		current = current->next;
	}
	return has_error;
}

void	execute_pipeline(char *line, t_shell *shell)
{
	t_cmd	*cmds = parse_commands(line, shell);
	t_cmd	*cur;
	int		pipefd[2];
	int		prev_fd = -1;
	pid_t	last_pid = -1;

	if (!cmds)
		return;
	
	int	devnull = open("/dev/null", O_RDONLY);
	if (devnull == -1)
	{
		perror("open /dev/null");
		close(devnull);
		return;
	}
	for (cur = cmds; cur; cur = cur->next)
	{
		if (cur->has_redir_error)
		{
			if (cur->infile == -1) cur->infile = devnull;
			if (cur->outfile == -1) cur->outfile = STDOUT_FILENO;
			if (cur->args)
			{
				ft_free_split(cur->args);
				cur->args = ft_calloc(1, sizeof(char *));
			}
		}
	}
	
	cur = cmds;
	while (cur)
	{
		if (cur->next)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				shell->last_status = 1;
			}
		}

		last_pid = fork();
		if (last_pid == -1)
		{
			perror("fork");
			shell->last_status = 1;
		}

		if (last_pid == 0)
		{
			if (cur->has_redir_error)
			{
				exit(1);
			}
			if (cur->infile != STDIN_FILENO)
			{
				dup2(cur->infile, STDIN_FILENO);
				close(cur->infile);
			}
			else if (prev_fd != -1)
			{
				dup2(prev_fd, STDIN_FILENO);
			}

			if (cur->outfile != STDOUT_FILENO)
			{
				dup2(cur->outfile, STDOUT_FILENO);
				close(cur->outfile);
			}
			else if (cur->next)
			{
				dup2(pipefd[1], STDOUT_FILENO);
			}
			
			if (prev_fd != -1) close(prev_fd);
			if (cur->next)
			{
				close(pipefd[0]);
				close(pipefd[1]);
			}

			if (!cur->args || !cur->args[0])
				exit(0);
			execute_cmd(cur, shell);
		}
		
		if (prev_fd != -1)
			close(prev_fd);
		if (cur->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cur = cur->next;
	}

	if (prev_fd != -1)
		close(prev_fd);
	
	if (last_pid == -1)
	{
		free_cmd_list(cmds);
		close(devnull);
		return;
	}

	int status;
	if (waitpid(last_pid, &status, 0) == -1)
		perror("waitpid");

	while (wait(NULL) > 0);

	if (WIFEXITED(status))
	{
		shell->last_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
	}

	free_cmd_list(cmds);
	close(devnull);
}

void	sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int is_empty_or_whitespace(const char *str)
{
	if (!str)
		return 1;
	
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
			return 0;
		str++;
	}
	return 1;
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	char	*newline;
	char	*prompt_str;
	t_shell shell;

	newline = NULL;
	prompt_str = NULL;
	(void)argc;
	(void)argv;

	shell.envp = copy_envp(envp);
	shell.last_status = 0;
	setup_signals();
	while (1)
	{

		prompt = malloc(13);
		if (!prompt)
			break ;
		ft_strcpy(prompt, "minishell$ ");
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			free_envp(shell.envp);
    		exit(shell.last_status);
		}
		
		if (is_empty_or_whitespace(line))
		{
			free(line);
			continue;
		}
		
		while (is_unclosed_quote(line))
		{
			newline = readline("> ");
			if (!newline)
				break ;
			prompt_str = malloc(ft_strlen(line) + ft_strlen(newline) + 2);
			sprintf(prompt_str, "%s\n%s", line, newline);
			free(line);
			free(newline);
			line = prompt_str;
		}

		if (*line)
			add_history(line);

		if(ft_strncmp(line, "\'\'", 2) == 0)
		{
			fprintf(stderr, "\'\': command not found\n");
			free(line);
			shell.last_status = 127;
			continue;
		}

		if(ft_strncmp(line, "\"\"", 2) == 0)
		{
			fprintf(stderr, "\"\": command not found\n");
			free(line);
			shell.last_status = 127;
			continue;
		}

		if (!ft_strchr(line, '|') || (ft_strncmp(line, "export", 6) == 0 && ft_strchr(line, '|')))
		{
			if (ft_strcmp(line, "exit \"\"") == 0 || ft_strcmp(line, "exit \'\'") == 0)
			{
				fprintf(stderr, "exit: : numeric argument required");
				free(line);
				free_envp(shell.envp);
				exit(2);
			}
			char **args = split_args_with_expansion(line, &shell);
			if (args && args[0])
			{
				if (has_whitespace(args[0]))
				{
					fprintf(stderr, "%s: command not found\n", args[0]);
					shell.last_status = 127;
					ft_free_split(args);
					free(line);
					continue;
				}
				if (ft_strcmp(args[0], "exit") == 0)
				{
					execute_exit(args);
					ft_free_split(args);
					free(line);
					free_envp(shell.envp);
					exit(shell.last_status);
				}
				else if (ft_strcmp(args[0], "cd") == 0
					|| ft_strcmp(args[0], "export") == 0
					|| ft_strcmp(args[0], "unset") == 0)
				{
					shell.last_status = execute_builtin(args, &shell);
					ft_free_split(args);
					free(line);
					continue;
				}
			}
			ft_free_split(args);
		}


		execute_pipeline(line, &shell);
		free(line);
	}
	free_envp(shell.envp);
	return (0);
}
