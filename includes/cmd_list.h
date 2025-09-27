#ifndef CMD_LIST_H
# define CMD_LIST_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct
typedef struct	s_exec {
	char			**args;
	struct s_exec	*next;
	t_tkn			*redin;
	t_tkn			*redout;
}					t_exec;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// cmd_list.c

#endif
