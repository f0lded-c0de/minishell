#ifndef PARSING_H
# define PARSING_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_type {
	WORD,
	PIPE,
	OR,
	AND,
	RED_IN,
	RED_OUT,
	HEREDOC,
	APP_OUT,
	PAR_OPEN,
	PAR_CLOSE,
}	t_type;

typedef enum	e_quote {
	NONE,
	SINGLE,
	DOUBLE
}	t_quote;

// struct
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
