#ifndef EXEC_PIPELINE_H
# define EXEC_PIPELINE_H

/* * * * * * * * * * * * * * * * * Structures * * * * * * * * * * * * * * * * */
// struct
typedef enum	e_bltn {
	NOT_BLTN
	CD,
	ECHO,
	ENV,
	EXIT,
	EXPORT,
	PWD,
	UNSET
}					t_bltn;


/* * * * * * * * * * * * * * * * * Functions  * * * * * * * * * * * * * * * * */
// exec_pipeline.c
int	*exec_pipeline(t_exec *pipeline, t_exdata *exdata);

// utils.c

#endif
