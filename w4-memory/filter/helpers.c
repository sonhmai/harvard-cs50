#include "helpers.h"
#include "math.h"
#include "stdio.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for(int row=0; row<height; row++){
		for(int col=0; col<width; col++){
			int avg = round((image[row][col].rgbtBlue 
				+ image[row][col].rgbtGreen + image[row][col].rgbtRed)/3);
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
	// create an 2d array to store the original RGB of image as we need them 
	// for calculating the average (the original image pixel RGB will be changed)
	RGBTRIPLE orig[height][width];
	for(int row=0; row<height; row++) {
		for(int col=0; col<width; col++) {
			orig[row][col] = image[row][col];
		}
	}
	// average of box 9 around the pixel
	for(int row=0; row<height; row++) {
		for(int col=0; col<width; col++) {
			int avgR = 0;
			int avgG = 0;
			int avgB = 0;
			// TODO Find a way to simplify the code below
			int count = 0;
			int tempRow = row;
			if (col-1 >= 0) {
					avgR += orig[tempRow][col-1].rgbtRed;
					avgG += orig[tempRow][col-1].rgbtGreen;
					avgB += orig[tempRow][col-1].rgbtBlue;
					count++;
				}
			if (col+1 < width) {
				avgR += orig[tempRow][col+1].rgbtRed;
				avgG += orig[tempRow][col+1].rgbtGreen;
				avgB += orig[tempRow][col+1].rgbtBlue;
				count++;
			}
			if (row-1 >= 0) {
				tempRow = row - 1;
				avgR += orig[tempRow][col].rgbtRed;
				avgG += orig[tempRow][col].rgbtGreen;
				avgB += orig[tempRow][col].rgbtBlue;
				count++;
				if (col-1 >= 0) {
					avgR += orig[tempRow][col-1].rgbtRed;
					avgG += orig[tempRow][col-1].rgbtGreen;
					avgB += orig[tempRow][col-1].rgbtBlue;
					count++;
				}
				if (col+1 < width) {
					avgR += orig[tempRow][col+1].rgbtRed;
					avgG += orig[tempRow][col+1].rgbtGreen;
					avgB += orig[tempRow][col+1].rgbtBlue;
					count++;
				}
			}
			if (row+1 < height) {
				tempRow = row + 1;
				avgR += orig[tempRow][col].rgbtRed;
				avgG += orig[tempRow][col].rgbtGreen;
				avgB += orig[tempRow][col].rgbtBlue;
				count++;
				if (col-1 >= 0) {
					avgR += orig[tempRow][col-1].rgbtRed;
					avgG += orig[tempRow][col-1].rgbtGreen;
					avgB += orig[tempRow][col-1].rgbtBlue;
					count++;
				}
				if (col+1 < width) {
					avgR += orig[tempRow][col+1].rgbtRed;
					avgG += orig[tempRow][col+1].rgbtGreen;
					avgB += orig[tempRow][col+1].rgbtBlue;
					count++;
				}
			}
			avgR = round(avgR / count);
			avgG = round(avgG / count);
			avgB = round(avgB / count);
			image[row][col].rgbtRed = avgR;
			image[row][col].rgbtGreen = avgG;
			image[row][col].rgbtBlue = avgB;
		}
	}
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
