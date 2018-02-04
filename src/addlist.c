#include <stdlib.h>
#include "my.h"

extern	t_save	save;

void		find_space(size_t size, t_block **new)
{
  t_block	*n;

  n = save._begin;
  while (n != NULL)
    {
      if (n->isFree == true && n->size >= size + BLOCK_SIZE + 4)
	{
	  (*new) = n;
	  return ;
	}
      n = n->next;
    }
}

void		init_sbrk(size_t size)
{
  size_t	page;

  page = size + PAGE_SIZE - (size % PAGE_SIZE);
  if (BLOCK_SIZE + size > (size_t)(save._brk - save._mem))
    {
      if ((sbrk(page)) == (void *)-1)
	exit(1);
      save._brk += page;
    }
}

void		add_space(t_block **new, size_t size)
{
  init_sbrk(size);
  (*new) = (t_block *)save._mem;
  (*new)->size = size;
  (*new)->next = NULL;
  (*new)->isFree = false;
  (*new)->byte = (*new) + 1;
  if (save._begin != NULL)
    {
      (*new)->prev = save._end;
      save._end->next = (*new);
    }
  else
    {
      (*new)->prev = NULL;
      save._begin = (*new);
    }
  save._mem += (size + BLOCK_SIZE);
  save._end = (*new);
}

int		new_node(t_block **new, size_t size)
{
  int		verif;
  t_block	*node;

  verif = 0;
  if ((*new)->size >= size + BLOCK_SIZE + 4)
    {
      node = (t_block *)(((char *)((*new)->byte) + size));
      node->size = (*new)->size - (size + BLOCK_SIZE);
      node->next = (*new)->next;
      node->isFree = true;
      node->byte = node + 1;
      node->prev = (*new);
      (*new)->size = size;
      (*new)->isFree = false;
      (*new)->next = node;
      if ((*new)->next != NULL)
	(*new)->next->prev = node;
      (*new) = (*new)->next;
      verif = 1;
    }
  return (verif);
}
