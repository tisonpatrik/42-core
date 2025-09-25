/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stress_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptison <ptison@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:21:13 by ptison            #+#    #+#             */
/*   Updated: 2025/09/24 17:22:09 by ptison           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#define _POSIX_C_SOURCE 200809L
#include "../include/minitalk.h"
#include <time.h>
#include <stdio.h>

static void ack_handler(int sig){ (void)sig; }
static void send_bit(pid_t pid, int bit){ int s = bit ? SIGUSR1 : SIGUSR2; if (kill(pid,s)==-1){ ft_putstr_fd("Error\n",2); exit(EXIT_FAILURE);} pause(); }
static void send_byte(pid_t pid, unsigned char uc){ for (int j=7;j>=0;--j) send_bit(pid,(uc>>j)&1); }
static void send_message(pid_t pid, const char *msg){ for (int i=0; msg[i]; ++i) send_byte(pid,(unsigned char)msg[i]); send_byte(pid,'\0'); }

static double sec_since(const struct timespec *a, const struct timespec *b){ return (b->tv_sec - a->tv_sec) + (b->tv_nsec - a->tv_nsec)/1e9; }

int main(int argc, char **argv)
{
    if (argc < 4) { ft_putstr_fd("usage: ./client_stress <pid> <count> <base_message>\n", 2); return 1; }
    pid_t pid = (pid_t)ft_atoi(argv[1]);
    int count = ft_atoi(argv[2]);
    if (pid < 1 || count < 1) exit(EXIT_FAILURE);

    struct sigaction sa; sigemptyset(&sa.sa_mask); sa.sa_flags=0; sa.sa_handler=ack_handler; sigaction(SIGUSR2,&sa,NULL);

    struct timespec t0, t1; clock_gettime(CLOCK_MONOTONIC,&t0);
    int ok = 0;
    for (int i=1; i<=count; ++i) {
        char *msg = ft_strjoin(argv[3], " ");           // base + " "
        char *num = ft_itoa(i);                          // číslo iterace
        char *full = ft_strjoin(msg, num);               // "base i"
        if (!msg || !num || !full) { ft_putstr_fd("alloc fail\n",2); exit(EXIT_FAILURE); }
        send_message(pid, full);
        free(msg); free(num); free(full);
        ++ok;
    }
    clock_gettime(CLOCK_MONOTONIC,&t1);

    double total = sec_since(&t0,&t1);
    printf("Sent: %d msgs; Total: %.3fs; Avg/msg: %.6fs\n", ok, total, total/ok);
    return 0;
}
