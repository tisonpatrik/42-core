#ifndef BUILD_PROFILE_H
# define BUILD_PROFILE_H

# include <stdbool.h>

# ifdef BONUS_BUILD
#  define CUB_BONUS_ENABLED true
# else
#  define CUB_BONUS_ENABLED false
# endif

#endif
