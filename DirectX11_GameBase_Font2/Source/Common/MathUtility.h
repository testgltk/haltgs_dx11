//==============================================================================
// File		MathUtility.h
// Comment	算術補助関数
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _MATHUTILITY_H_
#define _MATHUTILITY_H_

//------------------------------------------------------------------------------
// 名前空間
//------------------------------------------------------------------------------
namespace ns_MathUtility{

	//------------------------------------------------------------------------------
	// 定数
	//------------------------------------------------------------------------------
	static const float PI = 3.1415926535897932f;


	/** 絶対値取得*/
	template<typename T>
	static inline T abs(T a)
	{
		return (a < 0) ? -a : a;
	}

	/** 2つの値から大きい方取得*/
	template<typename T>
	static inline T max2(T x, T y)
	{
		return (x < y) ? x : y;
	}

	/** 2乗計算 */
	template<typename T>
	static inline T Square(T a)
	{
		return a * a;
	}

	/** 値を範囲内に丸め込む */
	template<typename T>
	static inline T clamp2(T &x, T min, T max)
	{
		return x < min ? min : x < max ? x : max;
	}

	/** 値が限界こえたら最小値に設定 */
	template<typename T>
	static inline T Loop2(T &x, T min, T max)
	{
		return x > max ? min : x;
	}

	/**
	* ラジアンを角度にコンバート.
	* @param	InRadian	Value in radians.
	* @return	Value in degrees.
	*/
	template<typename T>
	static inline T RadianToDegrees(T const& InRadian)
	{
		return InRadian * (180.f / PI);
	}

	/**
	* 角度をラジアンにコンバート.
	* @param	InDegree			Value in degrees.
	* @return					Value in radians.
	*/
	template<typename T>
	static inline T DegreeToRadian(T const& InDegree)
	{
		return InDegree * (PI / 180.f);
	}

	/**
	* ラジアンを正規化.
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
	* 角度を正規化.
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
	* 2値の線形補間
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
	* 2値の3次関数補間
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