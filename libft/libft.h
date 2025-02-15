/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbudau <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 21:34:03 by gbudau            #+#    #+#             */
/*   Updated: 2021/01/27 21:08:42 by gbudau           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <errno.h>
# include <string.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

enum	e_state
{
	STATE_OUT_WORD,
	STATE_IN_WORD
};

enum	e_strjoin_free
{
	FREE_FIRST,
	FREE_SECOND,
	FREE_BOTH
};

/*
** String functions
*/
int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isspace(int c);
int				ft_isblank(int c);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
char			*ft_strnstr(const char *hay, const char *need, size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
char			*ft_strjoin_free(char *s1, char *s2, size_t flag);
char			*ft_strcpy(char *dst, const char *src);
size_t			ft_str_count_c(const char *s, char c);
size_t			ft_str_count_s(const char *s, const char *delim);
int				ft_strcmp(const char *str1, const char *str2);
size_t			ft_strarrlen(char **info);
char			**ft_free_strarr(char **info);
char			**ft_split_str(const char *s, const char *delim);
int				get_next_line(int fd, char **line);

/*
** Memory functions
*/
void			ft_bzero(void *s, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);

/*
** Integer functions
*/
char			*ft_itoa(int n);
int				ft_min(int a, int b);
int				ft_max(int a, int b);
int				ft_abs(int n);

/*
** Linked list functions
*/
t_list			*ft_lstnew(void *content);
void			ft_lstadd_front(t_list **alst, t_list *newnode);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list	*lst);
void			ft_lstadd_back(t_list **alst, t_list *newnode);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *l, void *(*f)(void *), void (*del)(void *));
void			ft_lstrev(t_list **lst);
size_t			ft_lstdelcmp(t_list **head,
									int (*compar)(const void *, const void *),
									void *match, void (*del)(void *));
void			ft_lstmergesort(t_list **alist,
									int (*fcmp)(const void *, const void *));

/*
** Other functions
*/
void			ft_perror(char *s);

#endif
