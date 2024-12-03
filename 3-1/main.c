/*
 * Advent of Code 2024 / Day 3 / Puzzle 1
 *
 * "Our computers are having issues, so I have no idea if we have any Chief
 * Historians in stock! You're welcome to check the warehouse, though," says
 * the mildly flustered shopkeeper at the North Pole Toboggan Rental Shop. The
 * Historians head out to take a look.
 *
 * The shopkeeper turns to you. "Any chance you can see why our computers are
 * having issues again?"
 *
 * The computer appears to be trying to run a program, but its memory (your
 * puzzle input) is corrupted. All of the instructions have been jumbled up!
 *
 * It seems like the goal of the program is just to multiply some numbers. It
 * does that with instructions like mul(X,Y), where X and Y are each 1-3 digit
 * numbers. For instance, mul(44,46) multiplies 44 by 46 to get a result of
 * 2024. Similarly, mul(123,4) would multiply 123 by 4.
 *
 * However, because the program's memory has been corrupted, there are also
 * many invalid characters that should be ignored, even if they look like part
 * of a mul instruction. Sequences like mul(4*, mul(6,9!, ?(12,34), or
 * mul ( 2 , 4 ) do nothing.
 *
 * For example, consider the following section of corrupted memory:
 * xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))
 * Only the four highlighted sections are real mul instructions. Adding up the
 * result of each instruction produces 161 (2*4 + 5*5 + 11*8 + 8*5).
 *
 * Scan the corrupted memory for uncorrupted mul instructions.
 * What do you get if you add up all of the results of the multiplications?
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

int main() {
    int answer, state, c_buffer, a, b;
    char buffer[3], c;

    answer = 0;
    state = STATE_M;
    c_buffer = 0;

    while ((c = getc(stdin)) != EOF) {
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
                if (c == ')')
                    state = STATE_ACCEPT;
                else
                    state = STATE_M;
                break;

            // Accept
            case STATE_ACCEPT:
                printf("%d %d\n", a, b);
                answer += a * b;
                state = STATE_M;
                ungetc(c, stdin);
                break;

        }
    }

    printf("answer: %d\n", answer);

    return 0;
}

