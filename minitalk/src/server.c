/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 20:52:17 by ptison            #+#    #+#             */
/*   Updated: 2025/09/24 17:12:42 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

static void handle_signal(int sig, siginfo_t *info, void *context)
{
    static unsigned char character = 0;
    static int           bit_count = 0;
    static pid_t         client_pid = 0;

    (void)context;
    if (client_pid != info->si_pid) {
        bit_count = 0;
        character = 0;
    }
    client_pid = info->si_pid;

    character <<= 1;
    if (sig == SIGUSR1)
        character |= 1;
    bit_count++;

    if (bit_count == 8) {
        if (character == '\0') {
            write(1, "\n", 1);
        } else {
            write(1, &character, 1);
        }
        bit_count = 0;
        character = 0;
    }
    kill(client_pid, SIGUSR2);
}

static void setup_signal_handlers(void)
{
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = &handle_signal;
    sa.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);
}

int main(void)
{
    ft_printf("%d\n", getpid());
    setup_signal_handlers();
    while (1) pause();
    return EXIT_SUCCESS;
}
