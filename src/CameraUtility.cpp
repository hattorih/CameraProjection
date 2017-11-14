#include "CameraUtility.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>

#include <vectormath/cpp/vectormath_aos.h>


namespace utvl
{


namespace graphics
{


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


void print(void)
{
	using namespace Vectormath::Aos;

	printf("--- model-view\n");
	float temp_m[16] = { 0 };
	glGetFloatv(GL_MODELVIEW_MATRIX, temp_m);
	//for (int i = 0; i < 16; i++)
	//{
	//	printf("%11.4f\t", temp_m[i]);
	//	if ((i + 1) % 4 == 0)
	//		printf("\n");
	//}

	//Matrix4 mv(
	//	Vector4(temp_m[0], temp_m[1], temp_m[2], temp_m[3]),
	//	Vector4(temp_m[4], temp_m[5], temp_m[6], temp_m[7]),
	//	Vector4(temp_m[8], temp_m[9], temp_m[10], temp_m[11]),
	//	Vector4(temp_m[12], temp_m[13], temp_m[14], temp_m[15]));

	Matrix4 mv(
		Vector4(temp_m[0], temp_m[4], temp_m[8], temp_m[12]),
		Vector4(temp_m[1], temp_m[5], temp_m[9], temp_m[13]),
		Vector4(temp_m[2], temp_m[6], temp_m[10], temp_m[14]),
		Vector4(temp_m[3], temp_m[7], temp_m[11], temp_m[15]));

	printMatrix4(mv);

	printf("--- projection\n");
	float temp_p[16] = { 0 };
	glGetFloatv(GL_PROJECTION_MATRIX, temp_p);
	//for (int i = 0; i < 16; i++)
	//{
	//	printf("%11.4f\t", temp_p[i]);
	//	if ((i + 1) % 4 == 0)
	//		printf("\n");
	//}

	//Matrix4 p(
	//	Vector4(temp_p[0], temp_p[1], temp_p[2], temp_p[3]),
	//	Vector4(temp_p[4], temp_p[5], temp_p[6], temp_p[7]),
	//	Vector4(temp_p[8], temp_p[9], temp_p[10], temp_p[11]),
	//	Vector4(temp_p[12], temp_p[13], temp_p[14], temp_p[15]));

	Matrix4 p(
		Vector4(temp_p[0], temp_p[4], temp_p[8], temp_p[12]),
		Vector4(temp_p[1], temp_p[5], temp_p[9], temp_p[13]),
		Vector4(temp_p[2], temp_p[6], temp_p[10], temp_p[14]),
		Vector4(temp_p[3], temp_p[7], temp_p[11], temp_p[15]));

	printMatrix4(p);

	printf("--- model-view-projection\n");
	Matrix4 mvp = p * mv;

	//printf(
	//	"%11.4f, %11.4f, %11.4f, %11.4f\n%11.4f, %11.4f, %11.4f, %11.4f\n%11.4f, %11.4f, %11.4f, %11.4f\n%11.4f, %11.4f, %11.4f, %11.4f\n",
	//	mvp[0][0], mvp[1][0], mvp[2][0], mvp[3][0],
	//	mvp[0][1], mvp[1][1], mvp[2][1], mvp[3][1],
	//	mvp[0][2], mvp[1][2], mvp[2][2], mvp[3][2],
	//	mvp[0][3], mvp[1][3], mvp[2][3], mvp[3][3]);

	printMatrix4(mvp);

	Matrix4 mvp_inv = inverse(mvp);

	{
		Vector4 a(0.0f, 0.0f, 0, 1);

		Vector4 b = transpose(mvp) * a;

		if (b[2] != 0.0f)
			printf("==> %11.4f, %11.4f, %11.4f, %11.4f\n",
			b[0] / b[2], b[1] / b[2], b[2] / b[2], b[3] / b[2]);
	}

	{
		Vector4 a(50.0f, 50.0f, 0, 1);

		Vector4 b = transpose(mvp) * a;

		if (b[2] != 0.0f)
			printf("==> %11.4f, %11.4f, %11.4f, %11.4f\n",
			b[0] / b[2], b[1] / b[2], b[2] / b[2], b[3] / b[2]);
	}

	{
		Vector4 a(-50.0f, 50.0f, 0, 1);

		Vector4 b = transpose(mvp) * a;

		if (b[2] != 0.0f)
			printf("==> %11.4f, %11.4f, %11.4f, %11.4f\n",
			b[0] / b[2], b[1] / b[2], b[2] / b[2], b[3] / b[2]);
	}

	{
		Vector4 a(50.0f, -50.0f, 0, 1);

		Vector4 b = transpose(mvp) * a;

		if (b[2] != 0.0f)
			printf("==> %11.4f, %11.4f, %11.4f, %11.4f\n",
			b[0] / b[2], b[1] / b[2], b[2] / b[2], b[3] / b[2]);
	}

	{
		Vector4 a(-50.0f, -50.0f, 0, 1);

		Vector4 b = transpose(mvp) * a;

		if (b[2] != 0.0f)
			printf("==> %11.4f, %11.4f, %11.4f, %11.4f\n",
			b[0] / b[2], b[1] / b[2], b[2] / b[2], b[3] / b[2]);
	}
}


} // namespace graphics


} // namespace utvl

