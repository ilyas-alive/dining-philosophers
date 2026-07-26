#include "codexion.h"

long gettimenow()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (long)tv.tv_usec;
}
