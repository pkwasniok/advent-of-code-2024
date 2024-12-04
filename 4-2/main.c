/*
 * Advent of Code 2024 / Day 4 / Puzzle 2 (Solved)
 *
 * The Elf looks quizzically at you. Did you misunderstand the assignment?
 *
 * Looking for the instructions, you flip over the word search to find that
 * this isn't actually an XMAS puzzle; it's an X-MAS puzzle in which you're
 * supposed to find two MAS in the shape of an X. One way to achieve that
 * is like this:
 * M.S
 * .A.
 * M.S
 *
 * Irrelevant characters have again been replaced with . in the above diagram.
 * Within the X, each MAS can be written forwards or backwards.
 *
 * Here's the same example from before, but this time all of the X-MASes have
 * been kept instead:
 * .M.S......
 * ..A..MSMS.
 * .M.S.MAA..
 * ..A.ASMSM.
 * .M.S.M....
 * ..........
 * S.S.S.S.S.
 * .A.A.A.A..
 * M.M.M.M.M.
 * ..........
 *
 * In this example, an X-MAS appears 9 times.
 *
 * Flip the word search from the instructions back over to the word search
 * side and try again. How many times does an X-MAS appear?
*/

#include <stdio.h>
#include <string.h>

int main() {
    int x, y, size, answer;
    char c;
    char matrix[1024][1024];

    answer = 0;

    x = y = 0;
    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            y += 1;
            x = 0;
        } else {
            matrix[x++][y] = c;
        }
    }
    size = y;

    for (int x = 0; x < size - 2; x++) {
        for (int y = 0; y < size - 2; y++) {
            char buffer_diag[4], buffer_ctdiag[4];
            buffer_diag[3] = '\0';
            buffer_ctdiag[3] = '\0';

            // Diagonal
            for (int i = 0; i < 3; i++) {
                buffer_diag[i] = matrix[x+i][y+i];
            }

            // Counter diagonal
            for (int i = 0; i < 3; i++) {
                buffer_ctdiag[i] = matrix[x+2-i][y+i];
            }

            if ((strcmp(buffer_diag, "MAS") == 0 || strcmp(buffer_diag, "SAM") == 0) && (strcmp(buffer_ctdiag, "MAS") == 0 || strcmp(buffer_ctdiag, "SAM") == 0))
                answer += 1;
        }
    }

    printf("answer: %d\n", answer);

    return 0;
}

