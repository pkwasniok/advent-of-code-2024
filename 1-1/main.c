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

    qsort(left, N, sizeof(left[0]), compare);
    qsort(right, N, sizeof(right[0]), compare);

    for (int i = 0; i < N; i++) {
        result += abs(left[i] - right[i]);
    }

    printf("%d\n", result);

    return 0;
}

