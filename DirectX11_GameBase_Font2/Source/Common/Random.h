//==============================================================================
// File		Random.h
// Comment	Xofshift法による乱数生成
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _RANDOM_H_
#define _RANDOM_H_


/**
* @brief Xorshift乱数生成クラス
*/
class Random {
	
public:

	typedef struct RANGE_
	{
		int Min;
		int Max;
	}RANGE;

	/**
	* @brief	Constructor
	* @param	void
	* @return	void
	*/
	Random(void);

	/**
	* @brief Destructor
	*/
	~Random(void);

	static void SetSeed(unsigned int seed = 8867512);

	//ゲームのデモ用に使用する乱数のリセット
	static void Reset(unsigned int seed = 8867512);

	// 0～2^32-1の範囲の乱数を生成
	static unsigned int Get(void);

	// min～maxの範囲の乱数を生成
	static int GetRange(int min, int max);

	// min～maxの範囲の乱数を生成
	static int GetRange(const RANGE& range);

private:
	static unsigned int x, y, z, w;
};


#endif
