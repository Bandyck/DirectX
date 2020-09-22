#include "stdafx.h"
#include "cMainGame.h"
#include "cVector3.h"
#include "cMatrix.h"
cMainGame::cMainGame() : m_hBitmap(NULL), m_vEye(0, 0, -5), m_vLookAt(0, 0, 0), m_vUp(0, 1, 0)
{
}
cMainGame::~cMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::Setup()
{
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	ReleaseDC(g_hWnd, hdc);

	{
		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, -1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, -1.0f));

		m_vecVertex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(-1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, 1.0f, 1.0f));
		m_vecVertex.push_back(cVector3(1.0f, -1.0f, 1.0f));
	}
	// : clockwise(시계방향)
	// : front
	{
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(2);

		m_vecIndex.push_back(0);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(3);
	}
	// : back
	{
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(5);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(7);
		m_vecIndex.push_back(6);
	}
	// : left
	{
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(1);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(0);
	}
	// : right
	{
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(2);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(3);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(7);
	}
	// : up
	{
		m_vecIndex.push_back(1);
		m_vecIndex.push_back(5);
		m_vecIndex.push_back(6);

		m_vecIndex.push_back(1);
		m_vecIndex.push_back(6);
		m_vecIndex.push_back(2);
	}
	// : down
	{
		m_vecIndex.push_back(4);
		m_vecIndex.push_back(0);
		m_vecIndex.push_back(3);

		m_vecIndex.push_back(4);
		m_vecIndex.push_back(3);
		m_vecIndex.push_back(7);
	}
	for (float i = -5.f; i < 6.f; i += 1.f)
	{
		m_vecGrid.push_back(cVector3(i, 0, -5));
		m_vecGrid.push_back(cVector3(i, 0, 5));
		m_vecGrid.push_back(cVector3(-5, 0, i));
		m_vecGrid.push_back(cVector3(5, 0, i));
	}
	m_matWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);
}
void cMainGame::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vLookAt = cVector3(0.0f, 0.0f, 0.0f);
	m_vEye = cVector3(0.0f, 5.0f, -5.0f);

	m_matView = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj = cMatrix::Projection(PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::Viewport(0, 0, rc.right, rc.bottom, 0, 1);
}
void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS);
	cMatrix matWVP = m_matWorld * m_matView * m_matProj;
	cMatrix matWVPGrid = m_matView * m_matProj;
	for (size_t i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
		LineTo(m_MemDC, v3.x, v3.y);
		LineTo(m_MemDC, v1.x, v1.y);
	}
	for (int i = 0; i < 11; i++)
	{
		cVector3 v1 = m_vecGrid[4 * i + 0];
		cVector3 v2 = m_vecGrid[4 * i + 1];
		cVector3 v3 = m_vecGrid[4 * i + 2];
		cVector3 v4 = m_vecGrid[4 * i + 3];

		v1 = cVector3::TransformCoord(v1, matWVPGrid);
		v2 = cVector3::TransformCoord(v2, matWVPGrid);
		v3 = cVector3::TransformCoord(v3, matWVPGrid);
		v4 = cVector3::TransformCoord(v4, matWVPGrid);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);
		v4 = cVector3::TransformCoord(v4, m_matViewport);

		MoveToEx(m_MemDC, v1.x, v1.y, NULL);
		LineTo(m_MemDC, v2.x, v2.y);
		MoveToEx(m_MemDC, v3.x, v3.y, NULL);
		LineTo(m_MemDC, v4.x, v4.y);
	}
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}
void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
	{
		static float delta = 0;
		static float forward = 0;
		switch (wParam)
		{
		case 'A':	case 'a':
		{
			delta += 10;
			m_matWorld = cMatrix::RotationY(delta);
			break;
		}
		case 'D':	case 'd':
		{
			delta -= 10;
			m_matWorld = cMatrix::RotationY(delta);
			break;
		}
		case 'W':	case 'w':
		{
			forward += 1;
			cVector3 c(forward*cosf(delta), 0, forward*sinf(delta));
			m_matWorld = cMatrix::RotationY(delta)*cMatrix::Translation(c);
			break;
		}
		case 'S':	case 's':
		{
			forward -= 1;
			cVector3 c(forward*cosf(delta), 0, forward*sinf(delta));
			m_matWorld = cMatrix::RotationY(delta)*cMatrix::Translation(c);
			break;
		}
		default:
			break;
		}
	}
	break;
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_MOUSEWHEEL:
		break;
	default:
		break;
	}
}
