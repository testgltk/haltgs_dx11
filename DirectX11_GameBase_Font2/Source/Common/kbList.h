//=============================================================================
//
// 独自定義のリスト [kbList.h]
// Author : Ryo Kobayashi
// LastUpdate : 2014/6/15
//
//=============================================================================
#pragma once
#ifndef __KBR_LIST_H__
#define __KBR_LIST_H__

namespace kb
{
	//*****************************************************************************
	// リストクラス
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/15
	//*****************************************************************************
	template<class T>
	class List
	{
	public:
		
		//*****************************************************************************
		// リスト要素クラス
		// Author : Ryo Kobayashi
		// LastUpdate : 2014/6/15
		//*****************************************************************************
		class ListFactor
		{
		public:

			ListFactor() : 
			obj(0),
			next(0),
			prev(0)
			{}

			~ListFactor()
			{
				// 要素内にオブジェクトを保持していた場合、破棄する
				if(obj){ delete obj; }
				// この要素の次の要素が存在していたら、破棄する
				// この要素を内包するリストを削除すると、
				// 芋づる式にすべての要素が開放されるという仕組み
				// こいつだけ削除したい場合は、事前にリストから切り離そう
				if(next){ delete next; }
			}

			// このリスト要素が保持するオブジェクト
			T *obj;
			// リスト内の次の要素
			ListFactor *next;
			// リスト内の前の要素
			ListFactor *prev;
		private:
		};

		// デフォルトコンストラクタ
		List() :
		first(0), last(0), uLength(0)
		{}

		// 渡された数の要素数を保持するリストを作成するコンストラクタ
		List(const unsigned int& size) :
		first(0), last(0), uLength(0)
		{
			// 要素数が0だったとき何もせず返す
			if(size == 0)
			{
				return;
			}

			// 先頭の要素生成
			first = new ListFactor();
			// 要素の一時ポインタ
			ListFactor *temp = first;
			// 一時ポインタの前の要素を保持するポインタ
			ListFactor *tempPrev;
			// 要素の長さ初期化
			uLength = 1;
			// リスト生成ループ
			unsigned int idx = 0;
			while(idx < size)
			{
				// 新しいオブジェクトを生成
				temp->obj = new T();
				// 新しいリスト要素を生成
				temp->next = new ListFactor();
				// 新しいリスト要素の前の要素を現在の要素に設定
				temp->next->prev = temp;
				// 前の要素に現在の要素を保存
				tempPrev = temp;
				// 現在の要素に次の要素を設定
				temp = temp->next;

				idx++;
			}
			// 一時ポインタのオブジェクト生成
			temp->obj = new T();
			// 一時ポインタの前の要素設定
			temp->prev = tempPrev;
			// 最後尾の要素設定
			last = temp;
		}

		// デストラクタ
		~List()
		{
			// 芋づる式に消去される
			if(first){ delete first; }
		}
		
		// 先頭のリスト要素を取得
		ListFactor* GetFirstFactor(void) const { return first; }
		// 最後尾のリスト要素を取得
		ListFactor* GetLastFactor(void) const { return last; }

		// 先頭のリストオブジェクトへのポインタ取得
		T* GetFirstObject(void) const { return first->obj; }
		// 最後尾のリストオブジェクトへのポインタ取得
		T* GetLastObject(void) const { return last->obj; }

		// リストの長さを取得
		unsigned int GetLength(void) const { return uLength; }

		// リストの最後尾に追加
		void Addptr(T* obj)
		{
			ListFactor *listFactor = new ListFactor();
			listFactor->obj = obj;
			// リスト内に、まだ要素が存在していなかったとき
			if(uLength <= 0)
			{
				first	= listFactor;
				last	= listFactor;
				listFactor->next = 0;
				listFactor->prev = 0;
			}
			// リスト内に要素が存在するとき
			else
			{
				// 新しい要素の前の要素を最後尾の要素に
				listFactor->prev = last;
				// 新しい要素の前の要素の次の要素を新しい要素に
				listFactor->prev->next = listFactor;
				// 最後尾の要素を新しい要素に
				last = listFactor;
				// 新しい要素の次の要素を0
				listFactor->next = 0;
			}

			// リスト長増加
			uLength++;
		}
		
		// リストから切り離す(保持しているオブジェクトの開放はしない)
		void Unlinkptr(ListFactor* pFactor)
		{
			// 自分が先頭要素の時
			if(pFactor == first)
			{
				first = pFactor->next;
			}
			// 自分が最後尾の要素の時
			if(pFactor == last)
			{
				last = pFactor->prev;
			}
			// 自分の前の要素が存在するとき
			if(pFactor->prev)
			{
				// 自分の前の要素の次の要素を自分の次の要素に
				pFactor->prev->next = pFactor->next;
			}
			// 自分の次の要素が存在するとき
			if(pFactor->next)
			{
				// 自分の次の要素の前の要素を自分の前の要素に
				pFactor->next->prev = pFactor->prev;
			}
			// 自分の前後の要素へのポインタをクリア
			pFactor->next = 0;
			pFactor->prev = 0;
			// リスト要素数を減らす
			uLength--;
		}

		// ポインタで指定された要素を消去
		void Removeptr(ListFactor* pFactor)
		{
			Unlinkptr(pFactor);
			// 自己消去
			delete pFactor;
		}

		// 全消去
		void RemoveAll(void)
		{
			if(first){ delete first; }
			first = 0;
			last = 0;
			uLength = 0;
		}

	private:

		// リストの先頭要素
		ListFactor	*first;
		// リストの最後尾の要素
		ListFactor	*last;
		// リストの長さ
		unsigned int	uLength;
	};
	
	//*****************************************************************************
	// リスト内のオブジェクトを破壊しないクラス
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/17
	//*****************************************************************************
	template<class T>
	class ConstObjectList
	{
	public:
		
		//*****************************************************************************
		// リスト要素クラス
		// Author : Ryo Kobayashi
		// LastUpdate : 2014/6/17
		//*****************************************************************************
		class ListFactor
		{
		public:

			ListFactor() : 
			obj(0),
			next(0),
			prev(0)
			{}

			~ListFactor()
			{
				if(next){ delete next; }
			}

			// このリスト要素が保持するオブジェクト
			T *obj;
			// リスト内の次の要素
			ListFactor *next;
			// リスト内の前の要素
			ListFactor *prev;
		private:
		};

		// デフォルトコンストラクタ
		ConstObjectList() :
		first(0), last(0), uLength(0)
		{}

		// 渡された数の要素数を保持するリストを作成するコンストラクタ
		ConstObjectList(const unsigned int& size) :
		first(0), last(0), uLength(0)
		{
			// 要素数が0だったとき何もせず返す
			if(size == 0)
			{
				return;
			}

			// 先頭の要素生成
			first = new ListFactor();
			// 要素の一時ポインタ
			ListFactor *temp = first;
			// 一時ポインタの前の要素を保持するポインタ
			ListFactor *tempPrev;
			// 要素の長さ初期化
			uLength = 1;
			// リスト生成ループ
			unsigned int idx = 0;
			while(idx < size)
			{
				// 新しいオブジェクトを生成
				temp->obj = new T();
				// 新しいリスト要素を生成
				temp->next = new ListFactor();
				// 新しいリスト要素の前の要素を現在の要素に設定
				temp->next->prev = temp;
				// 前の要素に現在の要素を保存
				tempPrev = temp;
				// 現在の要素に次の要素を設定
				temp = temp->next;

				idx++;
			}
			// 一時ポインタのオブジェクト生成
			temp->obj = new T();
			// 一時ポインタの前の要素設定
			temp->prev = tempPrev;
			// 最後尾の要素設定
			last = temp;
		}

		// デストラクタ
		~ConstObjectList()
		{
			// 芋づる式に消去される
			if(first){ delete first; }
		}
		
		// 先頭のリスト要素を取得
		ListFactor* GetFirstFactor(void) const { return first; }
		// 最後尾のリスト要素を取得
		ListFactor* GetLastFactor(void) const { return last; }

		// 先頭のリストオブジェクトへのポインタ取得
		T* GetFirstObject(void) const { return first->obj; }
		// 最後尾のリストオブジェクトへのポインタ取得
		T* GetLastObject(void) const { return last->obj; }

		// リストの長さを取得
		unsigned int GetLength(void) const { return uLength; }

		// リストの最後尾に追加
		void Addptr(T* obj)
		{
			ListFactor *listFactor = new ListFactor();
			listFactor->obj = obj;
			// リスト内に、まだ要素が存在していなかったとき
			if(uLength <= 0)
			{
				first	= listFactor;
				last	= listFactor;
				listFactor->next = 0;
				listFactor->prev = 0;
			}
			// リスト内に要素が存在するとき
			else
			{
				// 新しい要素の前の要素を最後尾の要素に
				listFactor->prev = last;
				// 新しい要素の前の要素の次の要素を新しい要素に
				listFactor->prev->next = listFactor;
				// 最後尾の要素を新しい要素に
				last = listFactor;
				// 新しい要素の次の要素を0
				listFactor->next = 0;
			}

			// リスト長増加
			uLength++;
		}
		
		// リストから切り離す(保持しているオブジェクトの開放はしない)
		void Unlinkptr(ListFactor* pFactor)
		{
			// 自分が先頭要素の時
			if(pFactor == first)
			{
				first = pFactor->next;
			}
			// 自分が最後尾の要素の時
			if(pFactor == last)
			{
				last = pFactor->prev;
			}
			// 自分の前の要素が存在するとき
			if(pFactor->prev)
			{
				// 自分の前の要素の次の要素を自分の次の要素に
				pFactor->prev->next = pFactor->next;
			}
			// 自分の次の要素が存在するとき
			if(pFactor->next)
			{
				// 自分の次の要素の前の要素を自分の前の要素に
				pFactor->next->prev = pFactor->prev;
			}
			// 自分の前後の要素へのポインタをクリア
			pFactor->next = 0;
			pFactor->prev = 0;
			// リスト要素数を減らす
			uLength--;
		}

		// ポインタで指定された要素を消去
		void Removeptr(ListFactor* pFactor)
		{
			Unlinkptr(pFactor);
			// 自己消去
			delete pFactor;
		}

		// 全消去
		void RemoveAll(void)
		{
			if(first){ delete first; }
			first = 0;
			last = 0;
			uLength = 0;
		}

	private:

		// リストの先頭要素
		ListFactor	*first;
		// リストの最後尾の要素
		ListFactor	*last;
		// リストの長さ
		unsigned int	uLength;
	};
}

#endif	// __KBR_LIST_H__


// EOF