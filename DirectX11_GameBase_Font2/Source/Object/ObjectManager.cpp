// �I�u�W�F�N�g�}�l�[�W��

// �C���N���[�h
#include "ObjectManager.h"

// �R���X�g���N�^
CObjectManager::CObjectManager()
{

}

// �f�X�g���N�^
CObjectManager::~CObjectManager()
{

}

// �X�V
void CObjectManager::Update()
{

}

// �`��
void CObjectManager::Draw()
{
	for(int nObj = 0; nObj < MAX_PRIORITY; nObj++)
	{
		auto pObj = m_objList[nObj].GetFirstFactor();

		if(!pObj)
		{
			continue;
		}

		auto pNext = pObj->next;

		while(pObj)
		{
			pObj->obj->Draw();

			pObj = pNext;
			if(pNext)
			{
				pNext = pNext;
			}
		}
	}
}

// �I�u�W�F�N�g�ǉ�
void CObjectManager::Add(int nPriority, CObject2D* pObj)
{

}

// EOF