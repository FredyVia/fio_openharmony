#ifndef CONFIG_HAVE_STATX

#ifdef CONFIG_HAVE_STATX_SYSCALL

#ifndef __LITEOS_A__
#include <linux/stat.h>
#include <sys/stat.h>
#else
#include "los_syscall.h"
#include <sys/stat.h>
#endif
#else
#define STATX_ALL 0
#undef statx
struct statx
{
};
#endif

int statx(int dfd, const char *pathname, int flags, unsigned int mask,
	  struct statx *buffer);
#endif
