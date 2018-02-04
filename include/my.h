#ifndef MY_H_
# define MY_H_

# include <pthread.h>
# include <stdbool.h>
# include <unistd.h>

typedef struct		s_block
{
  struct s_block	*next;
  struct s_block	*prev;
  bool			isFree;
  size_t		size;
  void			*byte;
}			t_block;

typedef struct		s_save
{
  t_block		*_begin;
  t_block		*_end;
  void			*_mem;
  void			*_brk;
  pthread_mutex_t	_m;
}			t_save;

# define BLOCK_SIZE sizeof(struct s_block)
# define PAGE_SIZE getpagesize()

void		init_sbrk(size_t size);
void		find_space(size_t size, t_block **new);
void		add_space(t_block **new, size_t size);
void		init_malloc(bool *isInit);
int		new_node(t_block **new, size_t size);
size_t		my_getsize(size_t x);
void		show_alloc_mem();
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
void		free(void *ptr);
void		*calloc(size_t nb_elem, size_t size);
void		fusion_block(t_block **ptr);

#endif /* !MY_H_ */
