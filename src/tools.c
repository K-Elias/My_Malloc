#include <stdio.h>
#include "my.h"

extern t_save	save;

void		fusion_block(t_block **b_ptr)
{
  if ((*b_ptr)->prev != NULL && ((*b_ptr)->prev->isFree == true))
    {
      (*b_ptr)->prev->size += (*b_ptr)->size;
      (*b_ptr)->prev->next = (*b_ptr)->next;
      if ((*b_ptr) == save._end)
	save._end = (*b_ptr)->prev;
      else
	(*b_ptr)->next->prev = (*b_ptr)->prev;
      (*b_ptr) = (*b_ptr)->prev;
    }
  if ((*b_ptr)->next != NULL && ((*b_ptr)->next->isFree == true))
    {
      if ((*b_ptr)->next == save._end)
	save._end = (*b_ptr);
      else
	(*b_ptr)->next = (*b_ptr)->next->next;
      (*b_ptr)->size += (*b_ptr)->next->size;
      if ((*b_ptr)->next->next != NULL)
	(*b_ptr)->next->next->prev = (*b_ptr)->next;
    }
}

void		show_alloc_mem()
{
  t_block	*show;

  show = save._begin;
  printf("break : %p\n", save._brk);
  while (show->next != NULL)
    {
      printf("%p - %p : %zu bytes\n", show, show + show->size, show->size);
      show = show->next;
    }
}
