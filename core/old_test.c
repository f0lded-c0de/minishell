const char *type_to_str(t_tkn_type type)
{
	static const char *names[] = {
		"WORD", "PIPE", "RED_IN", "RED_OUT", "HEREDOC", "APP_OUT"
	};

	if (type >= 0 && type <= APP_OUT)
		return names[type];
	else
		return "UNKNOWN";
}

void	print_here_doc(t_tkn *tkn)
{
	char	*buffer;
	int		read_count;

	printf("heredoc content :\n\n");
	buffer = malloc(sizeof(char) * 101);
	read_count = read(tkn->hd_fd, buffer, 100);
	if (read_count == -1)
	{
		puterrno("debug: read() failed lmao: ");
		free(buffer);
		return ;
	}
	buffer[read_count] = '\0';
	while (read_count > 0)
	{
		printf("%s\n\n", buffer);
		read_count = read(tkn->hd_fd, buffer, 100);
		if (read_count == -1)
		{
			puterrno("debug: read() failed lmao: ");
			free(buffer);
			return ;
		}
		buffer[read_count] = '\0';
	}
	free(buffer);
}

void print_token_list(t_tkn *head)
{
	t_tkn	*tmp;
	if (!head)
	{
		printf("Empty token list");
		return;
	}
	tmp = head;
	while (tmp)
	{
		printf("Type : [%s]     Token: [%s]\n", type_to_str(tmp->type), tmp->str);
		if (tmp->type == HEREDOC)
			print_here_doc(tmp);
		tmp = tmp->next;
	}
	printf("----\n");
	tkn_free(head);
}
