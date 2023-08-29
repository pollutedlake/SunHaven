#pragma once

#define DEGREE_RADIAN(_deg)        (PI * (_deg) / 180.f)

#define DEG_TO_RAD       0.017453f

#define PI               3.141592653f

#define PI_2             6.283185308f

#define FLPAT_EPSILON    0.001f

#define FLOAT_TO_INT(f1)		static_cast<int>(f1 + FLOAT_EPSIOLON)

#define FLOAT_EQUAL(f1,f2)      (fabs(f1-f2)<= FLOAT_EPSILON)

namespace MY_UTIL
{
	// ���� ���� �Ÿ�
	float getDistance(float startX, float startY, float endX, float endY);

	// ��ŸƮ -> ���� -> ���� ��������
	float getAngle(float startX, float startY, float endX, float endY);
}
