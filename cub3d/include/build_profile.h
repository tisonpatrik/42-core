/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_profile.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 13:30:50 by ptison            #+#    #+#             */
/*   Updated: 2026/08/10 13:30:50 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILD_PROFILE_H
# define BUILD_PROFILE_H

# include <stdbool.h>

# ifdef BONUS_BUILD
#  define CUB_BONUS_ENABLED true
# else
#  define CUB_BONUS_ENABLED false
# endif

#endif
