// オブジェクトマネージャ

// インクルード
#include "ObjectManager.h"

// コンストラクタ
CObjectManager::CObjectManager()
{

}

// デストラクタ
CObjectManager::~CObjectManager()
{

}

// 更新
void CObjectManager::Update()
{

}

// 描画
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

// オブジェクト追加
void CObjectManager::Add(int nPriority, CObject2D* pObj)
{

}

// EOF