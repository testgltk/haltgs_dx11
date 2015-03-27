// �l��

#include "Human.h"
#include "sprite/sprite.h"

// �ÓI�����o�萔
// �����蔻�蔼�a
const float CHuman::RADIUS = 62.0f;

CHuman::CHuman() :
m_pSprite(nullptr),
m_pos(0,0),
m_move(0,0),
m_bSelected(false),
m_nMoveTimer(0),
m_State(DEFAULT)
{
	CSprite::PARAM param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/human.png" };
	m_pSprite = new CSprite(param);
	m_pSprite->SetWidth(128);
	m_pSprite->SetHeight(128);
	m_pSprite->SetPolygonAlign(CSprite::ALIGN_CENTER);

	reset();
}

CHuman::~CHuman()
{
	SafeDelete(m_pSprite);
}

void CHuman::Update()
{
	if(m_pSprite)
	{
		m_pSprite->Update();
	}

	if(SELECTED == m_State)
	{
		// �����A�j���[�V�������������炻��炵������
		m_pos.x = m_ParentPos.x + m_OffsetPos.x;
		m_pos.y = m_ParentPos.y + m_OffsetPos.y;
		m_pSprite->SetPosition(m_pos);
		return;
	}

	// �ړ��A�j���[�V����
	m_nMoveTimer++;

	if(m_nMoveTimer >= MOVE_DIR_CHANGE_SPAN)
	{
		m_move.x = -m_move.x;
		m_nMoveTimer = 0;
	}

	// �ړ�
	m_pos.x += m_move.x;

	if(m_pSprite)
	{
		m_pSprite->SetPosition(m_pos);
	}
}

void CHuman::Draw()
{
	m_pSprite->Draw();
}

void CHuman::onHit(/*object�I��*/)
{
	// ������

}

bool CHuman::onRelease()
{
	if(SELECTED != m_State) return false;
	m_pos.x = m_ParentPos.x + m_OffsetPos.x;
	m_pos.y = m_ParentPos.y + m_OffsetPos.y;
	m_State = RELEASED;

	return true;
}

const XMFLOAT2& CHuman::getPos()
{
	return m_pos;
}

bool CHuman::IsHit(const float x, const float y, float radius)
{
	if((m_pos.x - x) * (m_pos.x - x) +
	   (m_pos.y - y) * (m_pos.y - y) <=
		(RADIUS + radius) * (RADIUS + radius))
	{
		return true;
	}

	return false;
}

bool CHuman::IsHit(const float x, const float y, float width, float height)
{
	// RADIUS�𗬗p
	if((m_pos.x - RADIUS < x + width &&
		m_pos.x + RADIUS > x &&
		m_pos.y - RADIUS < y + height &&
		m_pos.y + RADIUS > y))
	{
		return true;
	}

	return false;
}

void CHuman::setParentPos(const float x, const float y)
{
	m_ParentPos.x = x;
	m_ParentPos.y = y;

	m_OffsetPos.x = m_pos.x - x;
	m_OffsetPos.y = m_pos.y - y;
}

void CHuman::reset()
{
	// �������W
	m_pos.x = Random::GetRange(900, 1050);
	m_pos.y = Random::GetRange(400, 650);
	// �ړ���
	m_move.x = 100.0f / Random::GetRange(10, 200);
	// ���݂̈ړ�����
	m_nMoveTimer = Random::GetRange(0, 60);

	// �I������
	m_bSelected = false;
	// �f�t�H���g�̏�Ԃ�
	m_State = DEFAULT;
}
