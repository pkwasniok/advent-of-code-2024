/*
 * Advent of Code 2024 / Day 3 / Puzzle 2
 *
 * As you scan through the corrupted memory, you notice that some of the
 * conditional statements are also still intact. If you handle some of the
 * uncorrupted conditional statements in the program, you might be able to get
 * an even more accurate result.
 *
 * There are two new instructions you'll need to handle:
 * - The do() instruction enables future mul instructions.
 * - The don't() instruction disables future mul instructions.
 *
 * Only the most recent do() or don't() instruction applies. At the beginning of the program, mul instructions are enabled.
 *
 * For example:
 * xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))
 *
 * This corrupted memory is similar to the example from before, but this time
 * the mul(5,5) and mul(11,8) instructions are disabled because there is
 * a don't() instruction before them. The other mul instructions function
 * normally, including the one at the end that gets re-enabled by a do()
 * instruction.
 *
 * This time, the sum of the results is 48 (2*4 + 8*5).
 *
 * Handle the new instructions; what do you get if you add up all of the
 * results of just the enabled multiplications?
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 'M' -> 'U' -> 'L' -> '(' -> '0'-'9' -> ',' -> '0'-'9' -> ')'

#define STATE_M      0
#define STATE_U      1
#define STATE_L      2
#define STATE_OP     3
#define STATE_NUM1   4
#define STATE_COMMA  5
#define STATE_NUM2   6
#define STATE_CP     7
#define STATE_ACCEPT 8

#define STATE_DO_D  0
#define STATE_DO_O  1
#define STATE_DO_OP 2
#define STATE_DO_CP 3

#define STATE_DONT_D  0
#define STATE_DONT_O  1
#define STATE_DONT_N  2
#define STATE_DONT_AP 3
#define STATE_DONT_T  4
#define STATE_DONT_OP 5
#define STATE_DONT_CP 6

int main() {
    int answer, state, state_do, state_dont, c_buffer, a, b;
    char buffer[3], c;
    bool enabled = true;

    answer = 0;
    state = STATE_M;
    state_do = STATE_DO_D;
    state_dont = STATE_DONT_D;
    c_buffer = 0;

    while ((c = getc(stdin)) != EOF) {

        switch(state_do) {
            case STATE_DO_D:
                    if (c == 'd')
                        state_do = STATE_DO_O;
                    else
                        state_do = STATE_DO_D;
                break;
            case STATE_DO_O:
                    if (c == 'o')
                        state_do = STATE_DO_OP;
                    else
                        state_do = STATE_DO_D;
                break;
            case STATE_DO_OP:
                    if (c == '(')
                        state_do = STATE_DO_CP;
                    else
                        state_do = STATE_DO_D;
                break;
            case STATE_DO_CP:
                if (c == ')') {
                    printf("do()\n");
                    enabled = true;
                }
                state_do = STATE_DO_D;
                break;
        }

        switch (state_dont) {
            case STATE_DONT_D:
                if (c == 'd')
                    state_dont = STATE_DONT_O;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_O:
                if (c == 'o')
                    state_dont = STATE_DONT_N;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_N:
                if (c == 'n')
                    state_dont = STATE_DONT_AP;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_AP:
                if (c == '\'')
                    state_dont = STATE_DONT_T;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_T:
                if (c == 't')
                    state_dont = STATE_DONT_OP;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_OP:
                if (c == '(')
                    state_dont = STATE_DONT_CP;
                else
                    state_dont = STATE_DONT_D;
                break;
            case STATE_DONT_CP:
                if (c == ')') {
                    enabled = false;
                    state_dont = STATE_DONT_D;
                    c_buffer = 0;
                    printf("don\'t()\n");
                }
                state = STATE_M;
                break;
        }

        if (enabled) {
            switch (state) {

                // Match 'm'
                case STATE_M:
                    if (c == 'm')
                        state = STATE_U;
                    else
                        state = STATE_M;
                    break;

                // Match 'u'
                case STATE_U:
                    if (c == 'u')
                        state = STATE_L;
                    else
                        state = STATE_M;
                    break;

                // Match 'l'
                case STATE_L:
                    if (c == 'l')
                        state = STATE_OP;
                    else
                        state = STATE_M;
                    break;

                // Match '('
                case STATE_OP:
                    if (c == '(')
                        state = STATE_NUM1;
                    else
                        state = STATE_M;
                    break;

                // Match 1-3 digit number
                case STATE_NUM1:
                    if (c >= '0' && c <= '9' && c_buffer < 3) {
                        buffer[c_buffer++] = c;
                    } else if (c_buffer >= 1) {
                        buffer[c_buffer] = '\0';
                        c_buffer = 0;

                        a = atoi(buffer);

                        state = STATE_COMMA;
                        ungetc(c, stdin);
                    } else {
                        c_buffer = 0;

                        state = STATE_M;
                        ungetc(c, stdin);
                    }
                    break;

                // Match ','
                case STATE_COMMA:
                    if (c == ',')
                        state = STATE_NUM2;
                    else
                        state = STATE_M;
                    break;

                // Match 1-3 digit number
                case STATE_NUM2:
                    if (c >= '0' && c <= '9' && c_buffer < 3) {
                        buffer[c_buffer++] = c;
                    } else if (c_buffer >= 1) {
                        buffer[c_buffer] = '\0';
                        c_buffer = 0;

                        b = atoi(buffer);

                        state = STATE_CP;
                        ungetc(c, stdin);
                    } else {
                        c_buffer = 0;

                        state = STATE_M;
                        ungetc(c, stdin);
                    }
                    break;

                // Match ')'
                case STATE_CP:
                    if (c == ')') {
                        printf("%d %d\n", a, b);
                        answer += a * b;
                    }
                    state = STATE_M;
                    break;

            }
        }
    }

    printf("answer: %d\n", answer);

    return 0;
}

