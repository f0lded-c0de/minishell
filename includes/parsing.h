#ifndef PARSING_H
# define PARSING_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
typedef enum	e_type {
	EMPTY,
	COMMAND,
	ARG,
	RED_IN,
	HEREDOC,
	RED_OUT,
	APP_OUT,
	AND,
	OR,
	PIPE,
	PAR_OPEN,
	PAR_CLOSE
}	t_type;

typedef struct	s_tkn {
	char			*str;
	t_type			type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_tkn;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// tokenisation.c
t_tkn	*tokenisation(char *str);

// tokens.c
t_tkn	*tkn_new(char *str, t_type type);
void	tkn_append(t_tkn *start, t_tkn *new);
void	tkn_free(t_tkn *tokens);

// get_tokens.c
t_tkn	get_token(t_tkn tokens, char *str, int *i);

// is_charset.c
int	is_meta(char *str);
int	is_ctrl(char *str);
int	is_space(char c);
int	is_redir(char c);

#endif
