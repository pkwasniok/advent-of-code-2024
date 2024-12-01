#include <stdio.h>
#include <stdlib.h>

#define N 1000

int compare(const void *a, const void *b) {
    return (*(int*)a) - (*(int*)b);
}

int main() {
    int left[N], right[N], result;

    result = 0;

    for (int i = 0; i < N; i++) {
        scanf("%d %d", &left[i], &right[i]);
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (left[i] == right[j]) {
                result += left[i];
            }
        }
    }

    printf("%d\n", result);

    return 0;
}

