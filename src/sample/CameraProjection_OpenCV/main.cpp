#include "opencv2/opencv.hpp"

#include "Camera.h"

#include <vectormath/cpp/vectormath_aos.h>


#define WINDOWNAME "Sample Application"

int W = 1280;
int H = 720;

const float sensor_w = 3.2f;
const float sensor_h = 1.8f;

const float fx = 300;
const float fy = 300 * sensor_h / sensor_w;

const float u = 0;
const float v = 0;
const float s = 0;

const float rx = 0;
const float ry = 0;
const float rz = 0;

const float tx = 0;
const float ty = 0;
const float tz = 100;


void printMatrix3(const Vectormath::Aos::Matrix3 &m)
{
	printf(
		"%11.4f, %11.4f, %11.4f\n"
		"%11.4f, %11.4f, %11.4f\n"
		"%11.4f, %11.4f, %11.4f\n",
		m[0][0], m[0][1], m[0][2],
		m[1][0], m[1][1], m[1][2],
		m[2][0], m[2][1], m[2][2]);
}


void printMatrix4(const Vectormath::Aos::Matrix4 &m)
{
	printf(
		"%11.4f, %11.4f, %11.4f, %11.4f\n"
		"%11.4f, %11.4f, %11.4f, %11.4f\n"
		"%11.4f, %11.4f, %11.4f, %11.4f\n"
		"%11.4f, %11.4f, %11.4f, %11.4f\n",
		//m[0][0], m[1][0], m[2][0], m[3][0],
		//m[0][1], m[1][1], m[2][1], m[3][1],
		//m[0][2], m[1][2], m[2][2], m[3][2],
		//m[0][3], m[1][3], m[2][3], m[3][3]);
		m[0][0], m[0][1], m[0][2], m[0][3],
		m[1][0], m[1][1], m[1][2], m[1][3],
		m[2][0], m[2][1], m[2][2], m[2][3],
		m[3][0], m[3][1], m[3][2], m[3][3]);
}


int main(int argc, char **argv)
{
	cvNamedWindow(WINDOWNAME);

	IplImage *image = cvCreateImage(cvSize(W, H), IPL_DEPTH_8U, 3);

	Vectormath::Aos::Matrix3 R;

	const float rrx = (float)(rx / 180.0 * 3.141592);
	const float rry = (float)(ry / 180.0 * 3.141592);
	const float rrz = (float)(rz / 180.0 * 3.141592);

	R[0][0] = cos(rry)*cos(rrz);
	R[0][1] = sin(rrx)*sin(rry)*cos(rrz) - cos(rrx)*sin(rrz);
	R[0][2] = cos(rrx)*sin(rry)*cos(rrz) + sin(rrx)*sin(rrz);

	R[1][0] = cos(rry)*sin(rrz);
	R[1][1] = sin(rrx)*sin(rry)*sin(rrz) + cos(rrx)*cos(rrz);
	R[1][2] = cos(rrx)*sin(rry)*sin(rrz) - sin(rrx)*cos(rrz);

	R[2][0] = -sin(rry);
	R[2][1] = sin(rrx)*cos(rry);
	R[2][2] = cos(rrx)*cos(rry);

	printf("--- R\n");
	printMatrix3(R);
	
	Vectormath::Aos::Matrix4 RT;
	RT[0][0] = R[0][0]; RT[0][1] = R[0][1]; RT[0][2] = R[0][2]; RT[0][3] = tx;
	RT[1][0] = R[1][0]; RT[1][1] = R[1][1]; RT[1][2] = R[1][2]; RT[1][3] = ty;
	RT[2][0] = R[2][0]; RT[2][1] = R[2][1]; RT[2][2] = R[2][2]; RT[2][3] = tz;
	RT[3][0] = 0; RT[3][1] = 0; RT[3][2] = 0; RT[3][3] = 1;

	printf("--- RT\n");
	printMatrix4(RT);

	Vectormath::Aos::Matrix4 A;
	A[0][0] = fx; A[0][1] = s; A[0][2] = u; A[0][3] = 0;
	A[1][0] = 0; A[1][1] = fy; A[1][2] = v; A[1][3] = 0;
	A[2][0] = 0; A[2][1] = 0; A[2][2] = 1; A[2][3] = 0;
	A[3][0] = 0; A[3][1] = 0; A[3][2] = 0; A[3][3] = 1;

	printf("--- A\n");
	printMatrix4(A);

	Vectormath::Aos::Matrix4 P = A * RT;

	printf("--- P\n");
	printMatrix4(P);

	for (int j = -5; j <= 5; j++)
	{
		for (int i = -5; i <= 5; i++)
		{
			Vectormath::Aos::Vector4 X(i * 10, j * 10, 0, 1);

			Vectormath::Aos::Vector4 x = Vectormath::Aos::transpose(P) * X;
			printf("%f, %f, %f, %f\n", x[0], x[1], x[2], x[3]);

			int xi = (x[0] / x[2] + 0.5f) + W / 2;
			int yi = (x[1] / x[2] + 0.5f) + H / 2;
			printf("x:%5d y:%5d\n", xi, yi);

			cvCircle(image, cvPoint(xi, yi), 2, CV_RGB(255, 0, 0), -1);
		}
	}

	cvShowImage(WINDOWNAME, image);
	cvWaitKey();

	cvReleaseImage(&image);

	cvDestroyWindow(WINDOWNAME);

	return 0;
}

