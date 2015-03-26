//==============================================================================
// File		Random.h
// Comment	Xofshift法による乱数生成
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#include "Random.h"

unsigned int Random::x = 123456789;
unsigned int Random::y = 362436069;
unsigned int Random::z = 521288629;
unsigned int Random::w = 0; //シードが与えられる

Random::Random(void)
{
}


Random::~Random(void)
{

}

void Random::SetSeed(unsigned int seed)
{
	w = seed;
}

void Random::Reset(unsigned int seed)
{
	x = 123456789;
	y = 362436069;
	z = 521288629;
	w = seed;
}

unsigned int Random::Get(void)
{
	unsigned int t;
	t = x ^ (x << 11);
	x = y;
	y = z;
	z = w;
	w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
	return w;
}

int Random::GetRange(int min, int max)
{
	unsigned int value = Get();
	return min + value % (max - min);
}

int Random::GetRange(const RANGE& range)
{
	unsigned int value = Get();
	return range.Min + value % (range.Max - range.Min);
}