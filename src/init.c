#include "my.h"

extern t_save	save;

size_t		my_getsize(size_t x)
{
  size_t	nb;

  nb = 0;
  while (x > 0)
    {
      x >>= 1;
      nb += 1;
    }
  x = 1;
  x <<= nb;
  return (x);
}

void	init_malloc(bool *isInit)
{
  if (*isInit == true)
    return ;
  else
    *isInit = true;
  save._begin = NULL;
  save._end = NULL;
  save._mem = sbrk(0);
  save._brk = save._mem;
}
