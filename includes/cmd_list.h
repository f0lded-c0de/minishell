#ifndef CMD_LIST_H
# define CMD_LIST_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// enum
typedef enum	e_cmd_type {
	SIMPLE,
	COMPOUND
}	t_cmd_type;

// struct
typedef struct	s_cmd {
	void			*cmd;
	t_cmd_type		type;
	struct s_tkn	*prev;
	struct s_tkn	*next;
}					t_cmd;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// tokenisation.c

#endif
