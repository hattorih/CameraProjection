#include "opencv2/opencv.hpp"

#include "Camera.h"


#define WINDOWNAME "Sample Application"

int W = 1280;
int H = 720;


int main(int argc, char **argv)
{
	cvNamedWindow(WINDOWNAME);

	IplImage *image = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);

	cvShowImage(WINDOWNAME, image);
	cvWaitKey();

	cvReleaseImage(&image);

	cvDestroyWindow(WINDOWNAME);

	return 0;
}

