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
	// 두점 사이 거리
	float getDistance(float startX, float startY, float endX, float endY);

	// 스타트 -> 엔드 -> 각을 라디안으로
	float getAngle(float startX, float startY, float endX, float endY);
}
