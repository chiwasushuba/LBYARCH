#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>  // For high-resolution timing

extern void imgCvtGrayFloatToInt(float* input, uint8_t* output, int width, int height);

void printUint8Image(uint8_t* img, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%3d ", img[y * width + x]);
        }
        printf("\n");
    }
}

int main() {
    int width, height;
    printf("Enter height and width: ");
    if (scanf("%d %d", &height, &width) != 2 || width <= 0 || height <= 0) {
        printf("Invalid input size.\n");
        return 1;
    }

    int total = width * height;
    float* input = (float*)malloc(sizeof(float) * total);
    uint8_t* output = (uint8_t*)malloc(sizeof(uint8_t) * total);
    if (!input || !output) {
        printf("Memory allocation failed.\n");
        free(input);
        free(output);
        return 1;
    }

    // Random grayscale float input between 0.0 and 1.0
    srand((unsigned)time(NULL));
    for (int i = 0; i < total; i++) {
        input[i] = (float)rand() / RAND_MAX;
    }

    // Timing setup
    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    // Run the conversion 30 times
    for (int i = 0; i < 30; i++) {
        imgCvtGrayFloatToInt(input, output, width, height);
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
    double avg_time = elapsed / 30.0;

    // Optional: only print image if small enough
    if (width <= 1000 && height <= 1000) {
        printf("\nConverted uint8 grayscale image:\n");
        printUint8Image(output, width, height);
    }

    printf("\nAverage execution time per run: %.6f ms\n", avg_time);

    free(input);
    free(output);
    return 0;
}
