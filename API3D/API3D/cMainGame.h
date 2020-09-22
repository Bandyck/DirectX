#pragma once
class cMainGame
{
public:
	cMainGame();
	~cMainGame();
private:
	HDC m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	vector<cVector3> m_vecVertex;
	vector<DWORD> m_vecIndex;

	vector<cVector3> m_vecGrid;

	cMatrix m_matWorld;
	cMatrix m_matView;
	cMatrix m_matProj;
	cMatrix m_matViewport;

	cVector3 m_vEye;
	cVector3 m_vLookAt;
	cVector3 m_vUp;
public:
	void Setup();
	void Update();
	void Render(HDC hdc);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};