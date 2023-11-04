#include "cubiomes/generator.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


bool includes(int arr[], int length, int element) {
    for (int i = 0; i < length; i++) {
        if (arr[i] == element) return true;
    }
    return false;
}

int* copyArray(int arr[], int length) {
    int newArr[length];
    for (int i = 0; i < length; i++) {
        newArr[i] = arr[i];
    }
    return newArr;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Please give the correct arguments: start, end, max_size, step.\n");
        return 0;
    }

    int start = atoi(argv[1]);
    int end = atoi(argv[2]);
    int max_size = atoi(argv[3]);
    int step = atoi(argv[4]);

    Generator g;
    setupGenerator(&g, MC_1_19_2, 0);

    int biomeCount = 8;
    int neededBiomes[8] = {desert, plains, forest, birch_forest, dark_forest, taiga, cold_ocean, river};

    uint64_t seed = start;
    while (seed <= end) {
        printf("TRY %" PRId64 "\n", (int64_t) seed);

        applySeed(&g, DIM_OVERWORLD, seed);

        int seedBiomes[8];
        int biomesFound = 0;

        int scale = 1;
        int x = -max_size, y = 1, z = -max_size;
        while (z < 2500) {
            int biomeId = getBiomeAt(&g, scale, x, y, z);
            if (includes(neededBiomes, biomeCount, biomeId) && !includes(seedBiomes, biomeCount, biomeId)) {\
                seedBiomes[biomesFound] = biomeId;
                biomesFound++;
            }

            if (biomesFound == biomeCount) {
                printf("FOUND %" PRId64 "\n", (int64_t) seed);
                break;
            }

            x = x + step;
            if (x >= max_size) {
                x = 0;
                z = z + step;
            }
        }
        seed++;
    }

    return 0;
}
