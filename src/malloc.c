#include <string.h>
#include "my.h"

t_save			save;

void			*malloc(size_t size)
{
  static bool		isInit = false;
  t_block		*new;

  size = my_getsize(size);
  init_malloc(&isInit);
  pthread_mutex_lock(&(save._m));
  add_space(&new, size);
  if (!new)
    return (NULL);
  pthread_mutex_unlock(&(save._m));
  return ((void *)((char *)new + BLOCK_SIZE));
}

void			free(void *ptr)
{
  t_block		*b_ptr;

  if (!ptr)
    return ;
  pthread_mutex_lock(&(save._m));
  b_ptr = (t_block *)((char *)ptr - BLOCK_SIZE);
  b_ptr->isFree = true;
  fusion_block(&b_ptr);
  pthread_mutex_unlock(&(save._m));
}

void			*calloc(size_t nb_elem, size_t size)
{
  void			*ptr;

  if ((ptr = malloc(nb_elem * size)) == NULL)
    return (NULL);
  return (ptr = memset(ptr, 0, nb_elem * size));
}

void			*realloc(void *ptr, size_t size)
{
  void			*new_ptr;
  t_block		*current;
  t_block		*block_ptr;

  if (!ptr)
    return (malloc(size));
  current = (t_block *)(((char *)ptr) - BLOCK_SIZE);;
  block_ptr = current;
  if (block_ptr->size >= size)
    return (ptr);
  free(ptr);
  new_ptr = malloc(size);
  if (!new_ptr)
    return (NULL);
  memcpy(new_ptr, ptr, block_ptr->size);
  return (new_ptr);
}
