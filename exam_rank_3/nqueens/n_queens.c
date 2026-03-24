#include "n_queens.h"
#include <stdbool.h>

/*
** Vytiskne nalezene reseni ve spravnem formatu.
*/
void print_solution(int *board, int n) {
    int col = 0;

    while (col < n) {
        fprintf(stdout, "%d", board[col]);
        if (col < n - 1) {
            fprintf(stdout, " ");
        }
        col++;
    }
    fprintf(stdout, "\n");
}

/*
** Zjistí, zda je pozice pro novou královnu bezpečná.
*/
bool is_safe(int *board, int current_col, int test_row) {
    int prev_col = 0;

    while (prev_col < current_col) {
        int prev_row = board[prev_col];

        // 1. Kontrola stejného řádku
        if (prev_row == test_row) {
            return false;
        }

        // 2. Kontrola diagonál (šikmých směrů)
        // Jak daleko (o kolik sloupců) jsme od předchozí královny?
        int distance = current_col - prev_col;

        // Ohrožení šikmo dolů (stoupající index řádku)
        if (test_row == prev_row + distance) {
            return false;
        }

        // Ohrožení šikmo nahoru (klesající index řádku)
        if (test_row == prev_row - distance) {
            return false;
        }

        prev_col++;
    }

    return true; // Žádná hrozba nalezena
}

/*
** Najde dalsi bezpecny radek pro dany sloupec.
*/
int get_next_safe_row(int *board, int current_col, int start_row, int n) {
    int row = start_row;

    while (row < n) {
        if (is_safe(board, current_col, row)) {
            return row; // Našli jsme bezpečné místo
        }
        row++;
    }

    return -1; // Žádné místo v tomto sloupci neexistuje
}

/*
** Iterativni reseni N-Queens s maximalni pruhlednosti
*/
void solve_n_queens(int n, int max_board) {
    int board[max_board];
    int current_col = 0;

    board[0] = 0; // Začínáme vlevo nahoře

    while (current_col >= 0) {
        int start_row = board[current_col];
        int safe_row = get_next_safe_row(board, current_col, start_row, n);

        if (safe_row != -1) {
            // --- SCÉNÁŘ 1: NAŠLI JSME MÍSTO ---
            board[current_col] = safe_row;

            if (current_col == n - 1) {
                // Jsme na konci, máme řešení
                print_solution(board, n);
                board[current_col]++; // Hledáme dál (posuneme poslední královnu)
            } else {
                // Posuneme se dopředu do dalšího sloupce
                current_col++;
                board[current_col] = 0;
            }
        } else {
            // --- SCÉNÁŘ 2: NENAŠLI JSME MÍSTO (BACKTRACK) ---
            current_col--; // Krok zpět

            if (current_col >= 0) {
                board[current_col]++; // V předchozím sloupci zkusíme nižší řádek
            }
        }
    }
}

int main(int argc, char **argv) {
    int maxboard = 100;

    if (argc == 2) {
        int n = atoi(argv[1]);
        if (n > 0 && n <= maxboard) {
            solve_n_queens(n, maxboard);
        }
    }
    return 0;
}
