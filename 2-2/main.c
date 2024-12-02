/*
 * Advent of Code 2024 / Day 2 / Puzzle 2 (Solved)
 *
 * The engineers are surprised by the low number of safe reports until they
 * realize they forgot to tell you about the Problem Dampener.
 *
 * The Problem Dampener is a reactor-mounted module that lets the reactor
 * safety systems tolerate a single bad level in what would otherwise be a safe
 * report. It's like the bad level never happened!
 *
 * Now, the same rules apply as before, except if removing a single level from
 * an unsafe report would make it safe, the report instead counts as safe.
 *
 * More of the above example's reports are now safe:
 * - 7 6 4 2 1: Safe without removing any level.
 * - 1 2 7 8 9: Unsafe regardless of which level is removed.
 * - 9 7 6 2 1: Unsafe regardless of which level is removed.
 * - 1 3 2 4 5: Safe by removing the second level, 3.
 * - 8 6 4 4 1: Safe by removing the third level, 4.
 * - 1 3 6 7 9: Safe without removing any level.
 *
 * Thanks to the Problem Dampener, 4 reports are actually safe!
 *
 * Update your analysis by handling situations where the Problem Dampener can
 * remove a single level from unsafe reports. How many reports are now safe?
*/

#include <stdio.h>
#include <stdlib.h>

void copyWithoutElement(int source[], int target[], int len, int index) {
    int i = 0;
    int j = 0;

    while (i < len) {
        if (i == index) {
            i += 1;
        } else {
            target[j++] = source[i++];
        }
    }
}

bool checkIfSafe(int array[], int len) {
    int diff = 0;
    int diff_prev = 0;

    for (int i = 0; i < len-1; i++) {
        diff = array[i+1] - array[i];
        
        if (!(abs(diff) >= 1 && abs(diff) <= 3 && diff * diff_prev >= 0)) {
            return false;
        }

        diff_prev = diff;
    }

    return true;
}

int main() {
    int c_buffer, c_nums, answer;
    char c;
    int nums[128], nums_copy[128];
    char buffer[128];

    answer = 0;

    c_buffer = 0;
    c_nums = 0;
    while ((c = getchar()) != EOF) {
        if (c >= '0' && c <= '9') {
            buffer[c_buffer++] = c;
        } else if (c_buffer > 0) {
            buffer[c_buffer] = '\0';
            c_buffer = 0;

            nums[c_nums++] = atoi(buffer);

            if (c == '\n') {

                if (checkIfSafe(nums, c_nums)) {
                    answer += 1;
                } else {
                    for (int i = 0; i < c_nums; i++) {
                        copyWithoutElement(nums, nums_copy, c_nums, i);

                        if (checkIfSafe(nums_copy, c_nums-1)) {
                            answer += 1;
                            break;
                        }
                    }
                }

                c_nums = 0;
            }
        }
    }

    printf("answer = %d\n", answer);

    return 0;
}

