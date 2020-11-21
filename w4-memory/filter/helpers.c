#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for(int row=0; row<height; row++){
		for(int col=0; col<width; col++){
			int avg = round((image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed)/3);
			image[row][col].rgbtBlue = avg;
			image[row][col].rgbtGreen = avg;
			image[row][col].rgbtRed = avg;
		}
	}
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	for(int row=0; row<height; row++) {
		int start = 0;
		int end = width - 1;
		while(start < end) {
			RGBTRIPLE temp = image[row][start];
			image[row][start] = image[row][end];
			image[row][end] = temp;
			start ++;
			end --;
		}
	}
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
