/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   latency_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:16:55 by ptison            #+#    #+#             */
/*   Updated: 2025/09/24 17:22:00 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#define _POSIX_C_SOURCE 200809L
#include <time.h>
#include <stdio.h>
#include "../include/minitalk.h"

static void ack_handler(int sig) { (void)sig; }

static void send_bit(pid_t pid, int bit)
{
    int s = bit ? SIGUSR1 : SIGUSR2;
    if (kill(pid, s) == -1) { ft_putstr_fd("Error\n", 2); exit(EXIT_FAILURE); }
    pause(); // \u010dek�me na ACK
}

static void send_byte(pid_t pid, unsigned char uc)
{
    for (int j = 7; j >= 0; --j)
        send_bit(pid, (uc >> j) & 1);
}

static void send_message(pid_t pid, const char *msg)
{
    for (int i = 0; msg[i]; ++i)
        send_byte(pid, (unsigned char)msg[i]);
    send_byte(pid, '\0'); // termina\u010dn� bajt
}

static double sec_since(const struct timespec *a, const struct timespec *b)
{
    return (b->tv_sec - a->tv_sec) + (b->tv_nsec - a->tv_nsec) / 1e9;
}

int main(int argc, char **argv)
{
    if (argc < 3) { ft_putstr_fd("usage: ./client_latency <pid> <msg>\n", 2); return 1; }

    pid_t pid = (pid_t)ft_atoi(argv[1]);
    if (pid < 1) exit(EXIT_FAILURE);

    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = ack_handler;
    sigaction(SIGUSR2, &sa, NULL);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    send_message(pid, argv[2]);
    clock_gettime(CLOCK_MONOTONIC, &t1);

    int len = (int)ft_strlen(argv[2]);
    double total = sec_since(&t0, &t1);
    double per_char = (len > 0) ? total / len : total;

    printf("Total: %.6fs, chars: %d, avg/char: %.6f s, approx/bit: %.6f s\n",
              total, len, per_char, per_char / 8.0);
    return 0;
}
