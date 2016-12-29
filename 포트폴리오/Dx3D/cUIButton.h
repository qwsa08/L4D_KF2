#pragma once

class cUIButton;

class iUIButtonDelegate
{
public:
	virtual int OnClick(cUIButton* pSender) = 0;
};

class cUIButton : public cUIObject
{
protected:
	enum eButtonState
	{
		E_STATE_NORMAL,
		E_STATE_MOVER,
		E_STATE_SELECTED,
		E_STATE_COUNT
	};

	LPDIRECT3DTEXTURE9	m_aTexture[E_STATE_COUNT];
	eButtonState		m_eButtonState;
	SYNTHESIZE(iUIButtonDelegate*, m_pDelegate, Delegate);

public:
	cUIButton(void);
	virtual ~cUIButton(void);

	void SetTexture(char* szNor, char* szOvr, char* szSel);

	// cUIObject override
	virtual void Update(bool isSelected, OUT int* button) override;
	virtual void Render(LPD3DXSPRITE pSprite) override;
};

