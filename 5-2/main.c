/*
 * Advent of Code 2024 / Day 5 / Puzzle 2 (Solved)
 *
 * While the Elves get to work printing the correctly-ordered updates, you have
 * a little time to fix the rest of them.
 *
 * For each of the incorrectly-ordered updates, use the page ordering rules to
 * put the page numbers in the right order. For the above example, here are the
 * three incorrectly-ordered updates and their correct orderings:
 *  - 75,97,47,61,53 becomes 97,75,47,61,53.
 *  - 61,13,29 becomes 61,29,13.
 *  - 97,13,75,29,47 becomes 97,75,47,29,13.
 *
 * After taking only the incorrectly-ordered updates and ordering them
 * correctly, their middle page numbers are 47, 29, and 47. Adding these
 * together produces 123.
 *
 * Find the updates which are not in the correct order. What do you get if you
 * add up the middle page numbers after correctly ordering just those updates?
*/

#include <stdio.h>
#include <stdlib.h>

int rules[1024][1024];

int compare(const void *a, const void *b) {
    int x = *((int*)a);
    int y = *((int*)b);

    int i = -1;
    while (rules[x][++i] != 0) {
        if (rules[x][i] == y) {
            return -1;
        }
    }

    return 1;
}

int main() {
    char string[1024];
    int answer = 0;

    // A. Parsing first part of the input (rules)
    for (int i = 0; i < 1024; i++) {
        for (int j = 0; j < 1024; j++) {
            rules[i][j] = 0;
        }
    }

    // Get first line of input
    fgets(string, 1024, stdin);

    int a, b;
    while (sscanf(string, "%d|%d", &a, &b) == 2) {
        // Find empty rules cell
        int i = -1;
        while(rules[a][++i] != 0);

        // Insert new rule
        rules[a][i] = b;

        // Get next line of input
        fgets(string, 1024, stdin);
    }

    // Print rules
    for (int i = 0; i < 1024; i++) {
        if (rules[i][0] != 0) {
            /*printf("%d: ", i);*/
            int j = 0;
            /*while (rules[i][j] != 0)*/
            /*    printf("%d ", rules[i][j++]);*/
            /*printf("\n");*/
        }
    }

    // B. Parsing second part of the input (updates)
    int updates[512][512];
    char c;

    for (int i = 0; i < 512; i++)
        for (int j = 0; j < 512; j++)
            updates[i][j] = 0;

    int i = 0;
    int j = 0;
    while ((c = getchar()) != EOF) {
        if (c == ',') {
            continue;
        }

        if (c == '\n') {
            i += 1;
            j = 0;
        } else {
            ungetc(c, stdin);
            scanf("%d", &a);
            updates[i][j++] = a;
        }
    }

    printf("\n\n");

    // Print updates
    i = 0;
    j = 0;
    while (updates[i][0] != 0) {
        while (updates[i][j] != 0) {
            /*printf("%d ", updates[i][j]);*/
            j += 1;
        }
        /*printf("\n");*/
        j = 0;
        i += 1;
    }

    // C. Algorithm

    /*printf("\n\n");*/

    i = 0;
    while (updates[i][0] != 0) {
        bool is_valid = true;

        j = 1;
        while (updates[i][j] != 0) {

            for (int k = j-1; k >= 0; k--) {
                int current = updates[i][j];
                int previous = updates[i][k];

                int l = 0;
                while (rules[current][l] != 0) {
                    if (previous == rules[current][l]) {
                        is_valid = false;
                        break;
                    }

                    l += 1;
                }

                if (is_valid == false) {
                    break;
                }
            }

            if (is_valid == false) {
                break;
            }

            j += 1;
        }

        if (is_valid == false) {
            // Find size of invalid row
            int size = -1;
            while (updates[i][++size] != 0);

            for (int k = 0; k < size; k++)
                printf("%d ", updates[i][k]);
            printf("\n");

            // Sort invalid array
            qsort(&updates[i], size, sizeof(int), compare);

            for (int k = 0; k < size; k++)
                printf("%d ", updates[i][k]);

            // Get middle value
            answer += updates[i][size / 2];

            printf("\n\n");
        }

        i += 1;
    }

    printf("answer: %d\n", answer);

    return 0;
}
