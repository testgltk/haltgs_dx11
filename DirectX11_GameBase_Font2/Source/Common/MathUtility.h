//==============================================================================
// File		MathUtility.h
// Comment	�Z�p�⏕�֐�
// Author	TOMOHIRO KOUNO
// Create	2014�N12��31��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

//------------------------------------------------------------------------------
// ���O���
//------------------------------------------------------------------------------
namespace ns_MathUtility{

	//------------------------------------------------------------------------------
	// �萔
	//------------------------------------------------------------------------------
	static const float PI = 3.1415926535897932f;


	/** ��Βl�擾*/
	template<typename T>
	static inline T abs(T a)
	{
		return (a < 0) ? -a : a;
	}

	/** 2�̒l����傫�����擾*/
	template<typename T>
	static inline T max2(T x, T y)
	{
		return (x < y) ? x : y;
	}

	/** 2��v�Z */
	template<typename T>
	static inline T Square(T a)
	{
		return a * a;
	}

	/** �l��͈͓��Ɋۂߍ��� */
	template<typename T>
	static inline T clamp2(T &x, T min, T max)
	{
		return x < min ? min : x < max ? x : max;
	}

	/** �l�����E��������ŏ��l�ɐݒ� */
	template<typename T>
	static inline T Loop2(T &x, T min, T max)
	{
		return x > max ? min : x;
	}

	/**
	* ���W�A�����p�x�ɃR���o�[�g.
	* @param	InRadian	Value in radians.
	* @return	Value in degrees.
	*/
	template<typename T>
	static inline T RadianToDegrees(T const& InRadian)
	{
		return InRadian * (180.f / PI);
	}

	/**
	* �p�x�����W�A���ɃR���o�[�g.
	* @param	InDegree			Value in degrees.
	* @return					Value in radians.
	*/
	template<typename T>
	static inline T DegreeToRadian(T const& InDegree)
	{
		return InDegree * (PI / 180.f);
	}

	/**
	* ���W�A���𐳋K��.
	* @param	A	Value in radians.
	* @return	out degrees.
	*/
	static float ReviceRadians(float A)
	{
		if (A > PI)
		{
			A -= PI * 2.0f;
		}

		else if (A < -PI)
		{
			A += PI * 2.0f;
		}

		return A;
	}

	/**
	* �p�x�𐳋K��.
	* @param	A	Value in radians.
	* @return	out degrees.
	*/
	static float ReviceDegrees(float A)
	{
		if (A > 180.f)
		{
			A -= 360.f;
		}

		else if (A < -180.f)
		{
			A += 360.f;
		}

		return A;
	}

	/**
	* 2�l�̐��`���
	* @param	A	StartPosition.
	* @param	B	DestinationPosition.
	* @return	Linear Interpolatein Value.
	*/
	template<class T, class U>
	static T Lerp(const T& A, const T& B, const U& Rate)
	{
		if (Rate > 1.0f)
		{
			return B;
		}
		return static_cast<T>(A + (B - A) * Rate);
	}

	/**
	* 2�l��3���֐����
	* @param	A	StartPosition.
	* @param	B	DestinationPosition.
	* @return	Linear Interpolatein Value.
	*/
	template<class T, class U>
	static T CubicLerp(const T& A, const T& B, const U& Rate)
	{
		if (Rate > 1.0f)
		{
			return B;
		}
		float convertRate = Rate * Rate * (3.f - 2.f * Rate);
		return static_cast<T>(A + (B - A) * convertRate);
	}
}
#endif