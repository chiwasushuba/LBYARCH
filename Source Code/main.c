#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <windows.h>

extern void imgCvtGrayFloatToInt(float* input, uint8_t* output, int width, int height);

void printUint8Image(uint8_t* img, int width, int height) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%3d ", img[y * width + x]);
        }
        printf("\n");
    }
}

void runManualInput() {
    int width, height;
    printf("Enter height and width: ");
    if (scanf("%d %d", &height, &width) != 2 || width <= 0 || height <= 0) {
        printf("Invalid input.\n");
        return;
    }

    int total = width * height;
    float* input = (float*)malloc(sizeof(float) * total);
    uint8_t* output = (uint8_t*)malloc(sizeof(uint8_t) * total);

    if (!input || !output) {
        printf("Memory allocation failed.\n");
        free(input);
        free(output);
        return;
    }

    printf("Enter %d float values (0.0 to 1.0):\n", total);
    for (int i = 0; i < total; i++) {
        if (scanf("%f", &input[i]) != 1) {
            printf("Invalid input detected.\n");
            free(input);
            free(output);
            return;
        }
    }

    imgCvtGrayFloatToInt(input, output, width, height);

    printf("\nConverted uint8 grayscale image:\n");
    printUint8Image(output, width, height);

    free(input);
    free(output);
}

void runAutomaticPerformanceTest() {
    int sizes[] = { 10, 100, 1000 };

    printf("\n=== Automatic Performance Test ===\n");
    for (int s = 0; s < 3; s++) {
        int width = sizes[s];
        int height = sizes[s];
        int total = width * height;

        float* input = (float*)malloc(sizeof(float) * total);
        uint8_t* output = (uint8_t*)malloc(sizeof(uint8_t) * total);

        if (!input || !output) {
            printf("Memory allocation failed for size %dx%d\n", width, height);
            free(input);
            free(output);
            continue;
        }

        // Fill input with random floats
        for (int i = 0; i < total; i++) {
            input[i] = (float)rand() / RAND_MAX;
        }

        LARGE_INTEGER freq, start, end;
        QueryPerformanceFrequency(&freq);
        QueryPerformanceCounter(&start);

        for (int i = 0; i < 30; i++) {
            imgCvtGrayFloatToInt(input, output, width, height);
        }

        QueryPerformanceCounter(&end);
        double elapsed = (double)(end.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart;
        double avg = elapsed / 30.0;

        printf("Size %4dx%-4d → Avg time: %.6f ms over 30 runs\n", width, height, avg);

        free(input);
        free(output);
    }
}

int main() {
    srand((unsigned int)time(NULL));

    int mode;
    printf("Choose mode:\n");
    printf(" 1 - Manual Input and Output\n");
    printf(" 0 - Automatic Performance Test\n");
    printf("Enter choice: ");
    if (scanf("%d", &mode) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (mode == 1) {
        runManualInput();
    }
    else if (mode == 0) {
        runAutomaticPerformanceTest();
    }
    else {
        printf("Unknown mode.\n");
    }

    return 0;
}
