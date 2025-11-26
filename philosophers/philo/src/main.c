/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:28:24 by ptison            #+#    #+#             */
/*   Updated: 2025/11/04 20:34:25 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/validator.h"
#include <stdio.h>
#include <stdlib.h>

int main(int ac, char *av[]) {
  t_inputs inputs;
  if (ac < 5) {
    printf("Error, too few arguments\n");
    exit(EXIT_FAILURE);
  } else if ((ac == 5) || (ac == 6)) {
    inputs = get_inputs(ac - 1, av);
  } else {
    printf("Error, too much arguments\n");
    exit(EXIT_FAILURE);
  }
  return (EXIT_SUCCESS);
}
