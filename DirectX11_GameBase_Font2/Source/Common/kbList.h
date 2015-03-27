//=============================================================================
//
// �Ǝ���`�̃��X�g [kbList.h]
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
	// ���X�g�N���X
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/15
	//*****************************************************************************
	template<class T>
	class List
	{
	public:
		
		//*****************************************************************************
		// ���X�g�v�f�N���X
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
				// �v�f���ɃI�u�W�F�N�g��ێ����Ă����ꍇ�A�j������
				if(obj){ delete obj; }
				// ���̗v�f�̎��̗v�f�����݂��Ă�����A�j������
				// ���̗v�f�����郊�X�g���폜����ƁA
				// ���Â鎮�ɂ��ׂĂ̗v�f���J�������Ƃ����d�g��
				// ���������폜�������ꍇ�́A���O�Ƀ��X�g����؂藣����
				if(next){ delete next; }
			}

			// ���̃��X�g�v�f���ێ�����I�u�W�F�N�g
			T *obj;
			// ���X�g���̎��̗v�f
			ListFactor *next;
			// ���X�g���̑O�̗v�f
			ListFactor *prev;
		private:
		};

		// �f�t�H���g�R���X�g���N�^
		List() :
		first(0), last(0), uLength(0)
		{}

		// �n���ꂽ���̗v�f����ێ����郊�X�g���쐬����R���X�g���N�^
		List(const unsigned int& size) :
		first(0), last(0), uLength(0)
		{
			// �v�f����0�������Ƃ����������Ԃ�
			if(size == 0)
			{
				return;
			}

			// �擪�̗v�f����
			first = new ListFactor();
			// �v�f�̈ꎞ�|�C���^
			ListFactor *temp = first;
			// �ꎞ�|�C���^�̑O�̗v�f��ێ�����|�C���^
			ListFactor *tempPrev;
			// �v�f�̒���������
			uLength = 1;
			// ���X�g�������[�v
			unsigned int idx = 0;
			while(idx < size)
			{
				// �V�����I�u�W�F�N�g�𐶐�
				temp->obj = new T();
				// �V�������X�g�v�f�𐶐�
				temp->next = new ListFactor();
				// �V�������X�g�v�f�̑O�̗v�f�����݂̗v�f�ɐݒ�
				temp->next->prev = temp;
				// �O�̗v�f�Ɍ��݂̗v�f��ۑ�
				tempPrev = temp;
				// ���݂̗v�f�Ɏ��̗v�f��ݒ�
				temp = temp->next;

				idx++;
			}
			// �ꎞ�|�C���^�̃I�u�W�F�N�g����
			temp->obj = new T();
			// �ꎞ�|�C���^�̑O�̗v�f�ݒ�
			temp->prev = tempPrev;
			// �Ō���̗v�f�ݒ�
			last = temp;
		}

		// �f�X�g���N�^
		~List()
		{
			// ���Â鎮�ɏ��������
			if(first){ delete first; }
		}
		
		// �擪�̃��X�g�v�f���擾
		ListFactor* GetFirstFactor(void) const { return first; }
		// �Ō���̃��X�g�v�f���擾
		ListFactor* GetLastFactor(void) const { return last; }

		// �擪�̃��X�g�I�u�W�F�N�g�ւ̃|�C���^�擾
		T* GetFirstObject(void) const { return first->obj; }
		// �Ō���̃��X�g�I�u�W�F�N�g�ւ̃|�C���^�擾
		T* GetLastObject(void) const { return last->obj; }

		// ���X�g�̒������擾
		unsigned int GetLength(void) const { return uLength; }

		// ���X�g�̍Ō���ɒǉ�
		void Addptr(T* obj)
		{
			ListFactor *listFactor = new ListFactor();
			listFactor->obj = obj;
			// ���X�g���ɁA�܂��v�f�����݂��Ă��Ȃ������Ƃ�
			if(uLength <= 0)
			{
				first	= listFactor;
				last	= listFactor;
				listFactor->next = 0;
				listFactor->prev = 0;
			}
			// ���X�g���ɗv�f�����݂���Ƃ�
			else
			{
				// �V�����v�f�̑O�̗v�f���Ō���̗v�f��
				listFactor->prev = last;
				// �V�����v�f�̑O�̗v�f�̎��̗v�f��V�����v�f��
				listFactor->prev->next = listFactor;
				// �Ō���̗v�f��V�����v�f��
				last = listFactor;
				// �V�����v�f�̎��̗v�f��0
				listFactor->next = 0;
			}

			// ���X�g������
			uLength++;
		}
		
		// ���X�g����؂藣��(�ێ����Ă���I�u�W�F�N�g�̊J���͂��Ȃ�)
		void Unlinkptr(ListFactor* pFactor)
		{
			// �������擪�v�f�̎�
			if(pFactor == first)
			{
				first = pFactor->next;
			}
			// �������Ō���̗v�f�̎�
			if(pFactor == last)
			{
				last = pFactor->prev;
			}
			// �����̑O�̗v�f�����݂���Ƃ�
			if(pFactor->prev)
			{
				// �����̑O�̗v�f�̎��̗v�f�������̎��̗v�f��
				pFactor->prev->next = pFactor->next;
			}
			// �����̎��̗v�f�����݂���Ƃ�
			if(pFactor->next)
			{
				// �����̎��̗v�f�̑O�̗v�f�������̑O�̗v�f��
				pFactor->next->prev = pFactor->prev;
			}
			// �����̑O��̗v�f�ւ̃|�C���^���N���A
			pFactor->next = 0;
			pFactor->prev = 0;
			// ���X�g�v�f�������炷
			uLength--;
		}

		// �|�C���^�Ŏw�肳�ꂽ�v�f������
		void Removeptr(ListFactor* pFactor)
		{
			Unlinkptr(pFactor);
			// ���ȏ���
			delete pFactor;
		}

		// �S����
		void RemoveAll(void)
		{
			if(first){ delete first; }
			first = 0;
			last = 0;
			uLength = 0;
		}

	private:

		// ���X�g�̐擪�v�f
		ListFactor	*first;
		// ���X�g�̍Ō���̗v�f
		ListFactor	*last;
		// ���X�g�̒���
		unsigned int	uLength;
	};
	
	//*****************************************************************************
	// ���X�g���̃I�u�W�F�N�g��j�󂵂Ȃ��N���X
	// Author : Ryo Kobayashi
	// LastUpdate : 2014/6/17
	//*****************************************************************************
	template<class T>
	class ConstObjectList
	{
	public:
		
		//*****************************************************************************
		// ���X�g�v�f�N���X
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

			// ���̃��X�g�v�f���ێ�����I�u�W�F�N�g
			T *obj;
			// ���X�g���̎��̗v�f
			ListFactor *next;
			// ���X�g���̑O�̗v�f
			ListFactor *prev;
		private:
		};

		// �f�t�H���g�R���X�g���N�^
		ConstObjectList() :
		first(0), last(0), uLength(0)
		{}

		// �n���ꂽ���̗v�f����ێ����郊�X�g���쐬����R���X�g���N�^
		ConstObjectList(const unsigned int& size) :
		first(0), last(0), uLength(0)
		{
			// �v�f����0�������Ƃ����������Ԃ�
			if(size == 0)
			{
				return;
			}

			// �擪�̗v�f����
			first = new ListFactor();
			// �v�f�̈ꎞ�|�C���^
			ListFactor *temp = first;
			// �ꎞ�|�C���^�̑O�̗v�f��ێ�����|�C���^
			ListFactor *tempPrev;
			// �v�f�̒���������
			uLength = 1;
			// ���X�g�������[�v
			unsigned int idx = 0;
			while(idx < size)
			{
				// �V�����I�u�W�F�N�g�𐶐�
				temp->obj = new T();
				// �V�������X�g�v�f�𐶐�
				temp->next = new ListFactor();
				// �V�������X�g�v�f�̑O�̗v�f�����݂̗v�f�ɐݒ�
				temp->next->prev = temp;
				// �O�̗v�f�Ɍ��݂̗v�f��ۑ�
				tempPrev = temp;
				// ���݂̗v�f�Ɏ��̗v�f��ݒ�
				temp = temp->next;

				idx++;
			}
			// �ꎞ�|�C���^�̃I�u�W�F�N�g����
			temp->obj = new T();
			// �ꎞ�|�C���^�̑O�̗v�f�ݒ�
			temp->prev = tempPrev;
			// �Ō���̗v�f�ݒ�
			last = temp;
		}

		// �f�X�g���N�^
		~ConstObjectList()
		{
			// ���Â鎮�ɏ��������
			if(first){ delete first; }
		}
		
		// �擪�̃��X�g�v�f���擾
		ListFactor* GetFirstFactor(void) const { return first; }
		// �Ō���̃��X�g�v�f���擾
		ListFactor* GetLastFactor(void) const { return last; }

		// �擪�̃��X�g�I�u�W�F�N�g�ւ̃|�C���^�擾
		T* GetFirstObject(void) const { return first->obj; }
		// �Ō���̃��X�g�I�u�W�F�N�g�ւ̃|�C���^�擾
		T* GetLastObject(void) const { return last->obj; }

		// ���X�g�̒������擾
		unsigned int GetLength(void) const { return uLength; }

		// ���X�g�̍Ō���ɒǉ�
		void Addptr(T* obj)
		{
			ListFactor *listFactor = new ListFactor();
			listFactor->obj = obj;
			// ���X�g���ɁA�܂��v�f�����݂��Ă��Ȃ������Ƃ�
			if(uLength <= 0)
			{
				first	= listFactor;
				last	= listFactor;
				listFactor->next = 0;
				listFactor->prev = 0;
			}
			// ���X�g���ɗv�f�����݂���Ƃ�
			else
			{
				// �V�����v�f�̑O�̗v�f���Ō���̗v�f��
				listFactor->prev = last;
				// �V�����v�f�̑O�̗v�f�̎��̗v�f��V�����v�f��
				listFactor->prev->next = listFactor;
				// �Ō���̗v�f��V�����v�f��
				last = listFactor;
				// �V�����v�f�̎��̗v�f��0
				listFactor->next = 0;
			}

			// ���X�g������
			uLength++;
		}
		
		// ���X�g����؂藣��(�ێ����Ă���I�u�W�F�N�g�̊J���͂��Ȃ�)
		void Unlinkptr(ListFactor* pFactor)
		{
			// �������擪�v�f�̎�
			if(pFactor == first)
			{
				first = pFactor->next;
			}
			// �������Ō���̗v�f�̎�
			if(pFactor == last)
			{
				last = pFactor->prev;
			}
			// �����̑O�̗v�f�����݂���Ƃ�
			if(pFactor->prev)
			{
				// �����̑O�̗v�f�̎��̗v�f�������̎��̗v�f��
				pFactor->prev->next = pFactor->next;
			}
			// �����̎��̗v�f�����݂���Ƃ�
			if(pFactor->next)
			{
				// �����̎��̗v�f�̑O�̗v�f�������̑O�̗v�f��
				pFactor->next->prev = pFactor->prev;
			}
			// �����̑O��̗v�f�ւ̃|�C���^���N���A
			pFactor->next = 0;
			pFactor->prev = 0;
			// ���X�g�v�f�������炷
			uLength--;
		}

		// �|�C���^�Ŏw�肳�ꂽ�v�f������
		void Removeptr(ListFactor* pFactor)
		{
			Unlinkptr(pFactor);
			// ���ȏ���
			delete pFactor;
		}

		// �S����
		void RemoveAll(void)
		{
			if(first){ delete first; }
			first = 0;
			last = 0;
			uLength = 0;
		}

	private:

		// ���X�g�̐擪�v�f
		ListFactor	*first;
		// ���X�g�̍Ō���̗v�f
		ListFactor	*last;
		// ���X�g�̒���
		unsigned int	uLength;
	};
}

#endif	// __KBR_LIST_H__


// EOF