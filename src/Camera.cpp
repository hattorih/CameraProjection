#include "Camera.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glut.h>


namespace utvl
{


namespace graphics
{


CameraOrtho2D::CameraOrtho2D(
	const double &width_, const double &height_) :
	mWidth(width_), mHeight(height_)
{
	;
}


CameraOrtho2D::~CameraOrtho2D(void)
{
	;
}


void CameraOrtho2D::enable(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	gluOrtho2D(0, mWidth, mHeight, 0);
}


void CameraOrtho2D::disable(void)
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}


CameraPerspective::CameraPerspective(
	const double &fov_, const double &aspect_, const double &near_, const double &far_,
	const double &eyex_, const double &eyey_, const double &eyez_,
	const double &centerx_, const double &centery_, const double &centerz_,
	const double &upx_, const double &upy_, const double &upz_) :
	mFov(fov_),
	mAspect(aspect_),
	mNear(near_), mFar(far_),
	mEyex(eyex_), mEyey(eyey_), mEyez(eyez_),
	mCenterx(centerx_), mCentery(centery_), mCenterz(centerz_),
	mUpx(upx_), mUpy(upy_), mUpz(upz_)
{
	;
}


CameraPerspective::~CameraPerspective(void)
{
	;
}


void CameraPerspective::enable(void)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(mFov, mAspect, mNear, mFar);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(mEyex, mEyey, mEyez, mCenterx, mCentery, mCenterz, mUpx, mUpy, mUpz);
}


void CameraPerspective::disable(void)
{
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
}


} // namespace graphics


} // namespace utvl

