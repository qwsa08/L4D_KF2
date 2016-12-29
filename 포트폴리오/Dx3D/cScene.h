#pragma once

#include "cUIButton.h"

class cScene : public iUIButtonDelegate
{
private:
	cUIObject*		m_pUIRoot;
	LPD3DXSPRITE	m_pSprite;
	bool			m_isSelected;

public:
	cScene();
	~cScene();

	void Setup();
	void Update(int* button);
	void Render();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	// iUIButtonDelegate override
	virtual int OnClick(cUIButton* pSender) override;
};

