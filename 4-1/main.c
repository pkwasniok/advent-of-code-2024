/*
 * Advent of Code 2024 / Day 4 / Puzzle 1 (Solved)
 *
 * "Looks like the Chief's not here. Next!" One of The Historians pulls out
 * a device and pushes the only button on it. After a brief flash, you
 * recognize the interior of the Ceres monitoring station!
 *
 * As the search for the Chief continues, a small Elf who lives on the station
 * tugs on your shirt; she'd like to know if you could help her with her word
 * search (your puzzle input). She only has to find one word: XMAS.
 *
 * This word search allows words to be horizontal, vertical, diagonal, written
 * backwards, or even overlapping other words. It's a little unusual, though,
 * as you don't merely need to find one instance of XMAS - you need to find
 * all of them. Here are a few ways XMAS might appear, where irrelevant
 * characters have been replaced with .:
 * ..X...
 * .SAMX.
 * .A..A.
 * XMAS.S
 * .X....
 *
 * The actual word search will be full of letters instead. For example:
 * MMMSXXMASM
 * MSAMXMSMSA
 * AMXSXMAAMM
 * MSAMASMSMX
 * XMASAMXAMM
 * XXAMMXXAMA
 * SMSMSASXSS
 * SAXAMASAAA
 * MAMMMXMMMM
 * MXMXAXMASX
 *
 * In this word search, XMAS occurs a total of 18 times; here's the same word
 * search again, but where letters not involved in any XMAS have been replaced
 * with .:
 * ....XXMAS.
 * .SAMXMS...
 * ...S..A...
 * ..A.A.MS.X
 * XMASAMX.MM
 * X.....XA.A
 * S.S.S.S.SS
 * .A.A.A.A.A
 * ..M.M.M.MM
 * .X.X.XMASX
 *
 * Take a look at the little Elf's word search. How many times does XMAS appear?
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

    // Horizontal
    for (int x = 0; x < size - 3; x++) {
        for (int y = 0; y < size; y++) {
            char buffer[5];
            buffer[5] = '\0';

            for (int i = 0; i < 4; i++) {
                buffer[i] = matrix[x+i][y];
            }

            if (strcmp(buffer, "XMAS") == 0)
                answer += 1;
            if (strcmp(buffer, "SAMX") == 0)
                answer += 1;
        }
    }

    // Vertical
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size - 3; y++) {
            char buffer[5];
            buffer[5] = '\0';

            for (int i = 0; i < 4; i++) {
                buffer[i] = matrix[x][y+i];
            }

            if (strcmp(buffer, "XMAS") == 0)
                answer += 1;
            if (strcmp(buffer, "SAMX") == 0)
                answer += 1;
        }
    }

    // Diagonal
    for (int x = 0; x < size - 3; x++) {
        for (int y = 0; y < size - 3; y++) {
            char buffer[5];
            buffer[5] = '\0';

            for (int i = 0; i < 4; i++) {
                buffer[i] = matrix[x+i][y+i];
            }

            if (strcmp(buffer, "XMAS") == 0)
                answer += 1;
            if (strcmp(buffer, "SAMX") == 0)
                answer += 1;
        }
    }

    // Counter diagonal
    for (int x = 3; x < size; x++) {
        for (int y = 0; y < size - 3; y++) {
            char buffer[5];
            buffer[5] = '\0';

            for (int i = 0; i < 4; i++) {
                buffer[i] = matrix[x-i][y+i];
            }

            if (strcmp(buffer, "XMAS") == 0)
                answer += 1;
            if (strcmp(buffer, "SAMX") == 0)
                answer += 1;
        }
    }

    printf("answer: %d\n", answer);

    return 0;
}

