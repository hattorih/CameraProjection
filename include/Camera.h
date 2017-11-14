/********************************************************************************
 Copyright (c) 2013-2016 Hironori Hattori. All rights reserved.

 University of Tokyo <hattorih@iis.u-tokyo.ac.jp>
 Carnegie Mellon University <hattorih@cs.cmu.edu>
---------------------------------------------------------------------------------
 $Id: $
********************************************************************************/


#ifndef __UTVL_GRAPHICS_CAMERA_H__
#define __UTVL_GRAPHICS_CAMERA_H__


namespace utvl
{


namespace graphics
{


class CameraParametersResolution
{
public:
	CameraParametersResolution(
		const double &width = 1280.0, const double &height = 720.0) :
		mWidth(width), mHeight(height)
	{
		;
	}

	~CameraParametersResolution(void)
	{
		;
	}

	double mWidth;
	double mHeight;
};

	
class CameraParametersEye
{
public:
	double mEyex;
	double mEyey;
	double mEyez;
};


class CameraParametersCenter
{
public:
	double mCenterx;
	double mCentery;
	double mCenterz;
};


class CameraParametersUp
{
public:
	double mUpx;
	double mUpy;
	double mUpz;
};


/*!
@brief This class has same function as "gluOrtho2D".
*/
class CameraOrtho2D
{
public:
	CameraOrtho2D(
		const double &width_, const double &height_);

	virtual ~CameraOrtho2D(void);

	void enable(void);

	void disable(void);

private:
	double mWidth;
	double mHeight;
};


/*!
@brief This class has same function as "gluPerspective x gluLookAt".

gluLookAt
\f[
M_{mv}=
  \begin{bmatrix}
    r_{11} & r_{12} & r_{13} & t_{x} \\
    r_{21} & r_{22} & r_{23} & t_{y} \\
    r_{31} & r_{32} & r_{33} & t_{z} \\
    0 & 0 & 0 & 1
  \end{bmatrix}
\f]
*/
class CameraPerspective
{
public:
	CameraPerspective(
		const double &fov_, const double &aspect_, const double &near_, const double &far_,
		const double &eyex_, const double &eyey_, const double &eyez_,
		const double &centerx_, const double &centery_, const double &centerz_,
		const double &upx_, const double &upy_, const double &upz_);

	virtual ~CameraPerspective(void);

	void enable(void);

	void disable(void);

private:
	double mFov;
	double mAspect;

	double mNear;
	double mFar;

	double mEyex;
	double mEyey;
	double mEyez;

	double mCenterx;
	double mCentery;
	double mCenterz;

	double mUpx;
	double mUpy;
	double mUpz;
};


} // namespace graphics


} // namespace utvl


#endif // __UTVL_GRAPHICS_CAMERA_H__

