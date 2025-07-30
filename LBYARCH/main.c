#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

//extern void asmhello();
extern void imgCvtGrayFloatToInt(int width, int height, float* img, int* conv);

int main() {
	int width, height;
	
	printf("Enter width and height: ");
	scanf("%d %d", &width, &height);

	while (width <= 0 || height <= 0) {
		printf("Invalid inputs, please enter width and height: ");
		scanf("%d %d", &width, &height);
	}

	float* img = malloc(sizeof(float) * (width * height));
	int* converted = malloc(sizeof(int) * (width * height));

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			printf("Pixel values (Row %d): ", i+1);
			scanf("%f ",);
		}
	}

	/*
	* while (input >= 1.0 || input <= 0.0) {
	*	invalid;
	*/

	imgCvtGrayFloatToInt(width, height, img, converted);
	int k = 0;

	do {
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				printf("%d ", converted[k]);
				k++;	
			}
			printf("\n");
			k++;
		}
	} while (k < (width * height));

	
	return 0;
}

