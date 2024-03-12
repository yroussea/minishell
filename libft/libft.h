/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yroussea <yroussea@student.42angouleme.fr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:31:20 by yroussea          #+#    #+#             */
/*   Updated: 2024/03/12 14:57:06 by yroussea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H	
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct s_stack
{
	int				content;
	int				nb;
	struct s_stack	*next;
}					t_stack;

int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);

void	*ft_calloc(size_t nmeb, size_t size);
void	ft_bzero(void *s, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *s, int c, size_t n);

void	ft_magic_free(char *str, ...);

int		ft_char_in_str(char const *s, char c);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	ft_free_split(char **result);
char	**ft_split(char const *s, char c);
char	**ft_split_charset(char const *s, char *charset);
char	**ft_split_first_sep(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_vjoin(size_t nb_str, char *sep, ...);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

size_t	ft_putmultstr_fd(char **strs, int fd);
size_t	ft_putlchar_fd(int c, int fd);
size_t	ft_putlhexa_low_fd(unsigned long int nb, int fd);
size_t	ft_putlhexa_up_fd(unsigned long int nb, int fd);
size_t	ft_putlnbr_fd(int n, int fd);
size_t	ft_putlunbr_fd(unsigned int n, int fd);
size_t	ft_putlpoint_fd(void *p, int fd);
size_t	ft_putlstr_fd(char *s, int fd);

size_t	ft_putlchar(int c);
size_t	ft_putlhexa_low(unsigned long int nb);
size_t	ft_putlhexa_up(unsigned long int nb);
size_t	ft_putlnbr(int n);
size_t	ft_putlunbr(unsigned int n);
size_t	ft_putlpoint(void *p);
size_t	ft_putlstr(char *s);
size_t	ft_putmultstr(char **strs);
size_t	ft_put_stack(t_stack *stack);

int		ft_printf(const char *str, ...);
int		ft_printf_fd(int fd, const char *str, ...);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void*));
void	ft_lstclear(t_list **lst, void (*del)(void*));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

void	ft_stackadd_back(t_stack **stack, t_stack *new);
void	ft_stackadd_front(t_stack **stack, t_stack *new);
t_stack	*ft_stacklast(t_stack *stack);
t_stack	*ft_stackbeforelast(t_stack *stack);
t_stack	*ft_stacknew(int content);
int		ft_stacksize(t_stack *stack);

int		ft_find_bn(const char *s);
size_t	ft_strcpy_until_bn(const char *s, char *result);
char	*get_next_line(int fd);

int		ft_abs(int nb);
int		ft_vmin(int number_of_number, ...);
int		ft_vmax(int number_of_number, ...);

#endif
