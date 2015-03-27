//
// �I�u�W�F�N�g�}�l�[�W��
// Author : Ryo Kobayashi
// Data : 2015/3/27
//

#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

// �C���N���[�h�t�@�C��
// common
#include "common/kbList.h"

// object2D
#include "Object2D.h"

class CObjectManager
{
public:

	// �D��x
	static const int MAX_PRIORITY = 8;

	// �R���X�g���N�^
	CObjectManager();

	// �f�X�g���N�^
	~CObjectManager();

	// �X�V
	void Update();

	// �`��
	void Draw();

	// �I�u�W�F�N�g�ǉ�
	void Add(int nPriority, CObject2D* pObj);

private:

	kb::List<CObject2D> m_objList[MAX_PRIORITY];
};

#endif	// _OBJECT_MANAGER_H_

// EOF