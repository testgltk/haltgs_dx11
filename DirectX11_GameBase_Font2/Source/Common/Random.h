//==============================================================================
// File		Random.h
// Comment	Xofshift�@�ɂ�闐������
// Author	TOMOHIRO KOUNO
// Create	2014�N12��31��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _RANDOM_H_
#define _RANDOM_H_


/**
* @brief Xorshift���������N���X
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

	//�Q�[���̃f���p�Ɏg�p���闐���̃��Z�b�g
	static void Reset(unsigned int seed = 8867512);

	// 0�`2^32-1�͈̗̔͂����𐶐�
	static unsigned int Get(void);

	// min�`max�͈̗̔͂����𐶐�
	static int GetRange(int min, int max);

	// min�`max�͈̗̔͂����𐶐�
	static int GetRange(const RANGE& range);

private:
	static unsigned int x, y, z, w;
};


#endif
