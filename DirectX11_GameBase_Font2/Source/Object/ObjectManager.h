//
// オブジェクトマネージャ
// Author : Ryo Kobayashi
// Data : 2015/3/27
//

#ifndef _OBJECT_MANAGER_H_
#define _OBJECT_MANAGER_H_

// インクルードファイル
// common
#include "common/kbList.h"

// object2D
#include "Object2D.h"

class CObjectManager
{
public:

	// 優先度
	static const int MAX_PRIORITY = 8;

	// コンストラクタ
	CObjectManager();

	// デストラクタ
	~CObjectManager();

	// 更新
	void Update();

	// 描画
	void Draw();

	// オブジェクト追加
	void Add(int nPriority, CObject2D* pObj);

private:

	kb::List<CObject2D> m_objList[MAX_PRIORITY];
};

#endif	// _OBJECT_MANAGER_H_

// EOF