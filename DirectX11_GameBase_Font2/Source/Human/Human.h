// 人間クラス

class CSprite;

class CHuman
{
public:

	enum STATE
	{
		DEFAULT,
		SELECTED,
		RELEASED
	};
	CHuman();

	~CHuman();

	void Update();

	void Draw();

	void onHit(/*object的な*/);
	bool onRelease();

	const XMFLOAT2& getPos();

	bool IsHit(const float x, const float y, float raidus);
	bool IsHit(const float x, const float y, float width, float height);

	void setSelected(bool bSel){ m_bSelected = bSel; }

	void setState(STATE st){ m_State = st; }

	void setParentPos(const float x, const float y);

	void updateParentPos(const float x, const float y){ m_ParentPos.x = x; m_ParentPos.y = y; }

	void reset();

	bool IsStateReleased(){ return (RELEASED == m_State ? true : false); }

private:

	static const int MOVE_DIR_CHANGE_SPAN = 90;

	CSprite* m_pSprite;

	XMFLOAT2 m_pos;
	XMFLOAT2 m_move;

	bool m_bSelected;

	int m_nMoveTimer;

	// 当たり判定半径
	static const float RADIUS;

	STATE m_State;

	XMFLOAT2 m_ParentPos;
	XMFLOAT2 m_OffsetPos;
};