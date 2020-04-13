#include <windows.h>		//Windows��
#include <windowsx.h>		//Windows��
#include <stdio.h>			//���o�͗p
#include <process.h>		//�X���b�h�p
#include <stdlib.h>

#pragma comment(lib,"winmm.lib")//�����x�^�C�}

#include "resource.h"		//���\�[�X�t�@�C��
#include "�w�b�_�[.h"		//���\�[�X�t�@�C��

//�\����
typedef struct {
	HWND	hwnd;
	HWND	hEdit;
}SEND_POINTER_STRUCT;

//���C���֐�(�_�C�A���O�o�[�W����)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HANDLE hMutex;

	//���d�N������
	hMutex = CreateMutex(NULL, TRUE, DEF_MUTEX_NAME);		//�~���[�e�b�N�X�I�u�W�F�N�g�̐���
	if (GetLastError() == ERROR_ALREADY_EXISTS) {				//2�d�N���̗L�����m�F
		MessageBox(NULL, TEXT("���ɋN������Ă��܂��D"), NULL, MB_OK | MB_ICONERROR);
		return 0;											//�I��
	}

	//�_�C�A���O�N��
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);

	return FALSE;			//�I��
}

//���C���v���V�[�W���i�_�C�A���O�j
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;				//�t�H���g
	static HANDLE hThread;
	static UINT thID;
	static SEND_POINTER_STRUCT Sps;
	static HWND hPict1;		//�E�B���h�E�n���h���iPictureBox�j
	static HWND hPict2;
	static HWND hWnd;

	switch (uMsg) {
	case WM_INITDIALOG:		//�_�C�A���O������
		Sps.hwnd = hDlg;
		


		//������(���w�i�̕`��̋N��)

		return TRUE;

	case WM_COMMAND:		//�{�^���������ꂽ��
		switch (LOWORD(wParam)) {
		case IDOK:			//OK�{�^��
				
			hPict2 = GetDlgItem(hDlg, IDC_PICTBOX2);
			//�J�n�{�^���������@�@�@�@//EnableWindow�œ��͂𖳌��܂��͗L���ɂ���B

			WinInitialize(NULL, hDlg, (HMENU)110, "TEST", hPict2, WndProc, &hWnd);

			color = RGB(0, 0, 0);			//�F�w��
			InvalidateRect(hWnd, NULL, TRUE);
						//�F�w��
			

			return TRUE;

		case IDCANCEL:		//�L�����Z���{�^��
			EndDialog(hDlg, 0);		//�_�C�A���O�I��
			return TRUE;
			
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);			//�_�C�A���O�I��
		return TRUE;
}

return FALSE;
}

HRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	HDC			hdc1;				//�f�o�C�X�R���e�L�X�g�̃n���h��
	HDC			hdc2;
	PAINTSTRUCT ps;					//(�\����)�N���C�A���g�̈�`�悷�邽�߂̏��	
	HBRUSH		hBrush, hOldBrush;	//�u���V
	HPEN		hPen, hOldPen;		//�y��

	switch (uMsg) {
	case WM_CREATE:
		colorPen = RGB(0, 0, 0);	//�F�w��
		//colorPen = color;	//�F�w��
		break;

	case WM_PAINT:

		/********************************

		PictureControl�ɕ`�悷�邽�߂ɂ́CHDC�^�̃n���h����ʂɎ擾����
		�K�v������܂��D

		��Fhdc = BeginPaint(hWnd, &ps);
		hdc:�f�o�C�X�R���e�L�X�g�̃n���h��
		hWnd:PictureControl�̃n���h��
		ps�F(�\����)�N���C�A���g�̈�`�悷�邽�߂̏��

		********************************/

		hdc1 = BeginPaint(hWnd, &ps);//�f�o�C�X�R���e�L�X�g�̃n���h���擾
		hdc2 = BeginPaint(hWnd, &ps);

		/********************************

		PictureControl�ɕ`�悷�邽�߂ɂ́C�������������Ƃ��̓y���C
		�h��Ԃ��ۂɂ̓u���V���K�v�ł��D

		********************************/

		//�y���C�u���V����
		hBrush = CreateSolidBrush(color);				//�u���V����
		hOldBrush = (HBRUSH)SelectObject(hdc1, hBrush);	//�u���V�ݒ�
		hOldBrush = (HBRUSH)SelectObject(hdc2, hBrush);
		hPen = CreatePen(PS_SOLID, 2, colorPen);		//�y������
		hOldPen = (HPEN)SelectObject(hdc1, hPen);		//�y���ݒ�
		hOldPen = (HPEN)SelectObject(hdc2, hPen);

		//�`��
		/********************************

		�}�`��`�悷�邽�߂ɂ͈ȉ��̊֐���p���܂��D
		�����`�FRectangle(HDC hdc ,int nLeftRect , int nTopRect ,int nRightRect , int nBottomRect);
		�~�FEllipse(HDC hdc ,int nLeftRect , int nTopRect ,int nRightRect , int nBottomRect);

		 nLiftRect�F�����`�̍���X���W
		  nTopRect�F����Y���W
		  nRightRect�F�E��X���W
		  nBottomRect�F�E����Y���W

		���������ɂ͈ȉ��̊֐���p���܂��D

		���̎n�_�ݒ�FMoveToEx(HDC hdc , int X , int Y , NULL);
		  X,Y�F���̎n�_�̍��W
		���GLineTo(HDC hdc , int nXEnd , int nYEnd);
		  nXEnd, nYEnd�F���̏I�_�̐ݒ�


		  �ȏ���Q�l�ɐ}�`��`�悷��֐����ȉ��ɋL�q���܂��傤
		********************************/
		//��������

		MoveToEx(hdc1, 10, 10, NULL);
		Rectangle(hdc1, 0, 0, 500, 500);

		MoveToEx(hdc2, 10, 10, NULL);
		Rectangle(hdc2, 200, 200, 500, 500);
		SelectObject(hdc2, hOldBrush);
		DeleteObject(hBrush);
		SelectObject(hdc2, hOldPen);
		DeleteObject(hPen);

		
		hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 255));
		hOldPen = (HPEN)SelectObject(hdc2, hPen);
		MoveToEx(hdc2, 80, 400, NULL);

		SelectObject(hdc2, hOldPen);
		DeleteObject(hPen);
		//�y���C�u���V�p��
		/********************************

		�g���I������y���ƃu���V�͔j������K�v������܂��D

		********************************/
		

		//�f�o�C�X�R���e�L�X�g�̃n���h���j��
		EndPaint(hWnd, &ps);
		break;
	}

	return TRUE;
}

BOOL WinInitialize(HINSTANCE hInst, HWND hPaWnd, HMENU chID, char* cWinName, HWND PaintArea, WNDPROC WndProc, HWND* hWnd)
{
	WNDCLASS wc;			//�E�B���h�E�N���X
	WINDOWPLACEMENT	wplace;	//�q�E�B���h�E�����̈�v�Z�p�i��ʏ�̃E�B���h�E�̔z�u�����i�[����\���́j
	RECT WinRect;			//�q�E�B���h�E�����̈�
	ATOM atom;				//�A�g��

	//�E�B���h�E�N���X������
	wc.style = CS_HREDRAW ^ WS_MAXIMIZEBOX | CS_VREDRAW;	//�E�C���h�E�X�^�C��
	wc.lpfnWndProc = WndProc;									//�E�C���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
	wc.cbClsExtra = 0;											//
	wc.cbWndExtra = 0;
	wc.hCursor = NULL;										//�v���O�����̃n���h��
	wc.hIcon = NULL;										//�A�C�R���̃n���h��
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//�E�C���h�E�w�i�F
	wc.hInstance = hInst;										//�E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
	wc.lpszMenuName = NULL;										//���j���[��
	wc.lpszClassName = (LPCTSTR)cWinName;									//�E�C���h�E�N���X��

	if (!(atom = RegisterClass(&wc))) {
		MessageBox(hPaWnd, TEXT("�E�B���h�E�N���X�̐����Ɏ��s���܂����D"), NULL, MB_OK | MB_ICONERROR);
		return false;
	}

	GetWindowPlacement(PaintArea, &wplace);	//�`��̈�n���h���̏����擾(�E�B���h�E�̕\����Ԃ��擾)
	WinRect = wplace.rcNormalPosition;		//�`��̈�̐ݒ�

	//�E�B���h�E����
	*hWnd = CreateWindow(
		(LPCTSTR)atom,
		(LPCTSTR)cWinName,
		WS_CHILD | WS_VISIBLE,//| WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME |WS_VISIBLE, 
		WinRect.left, WinRect.top,
		WinRect.right - WinRect.left, WinRect.bottom - WinRect.top,
		hPaWnd, chID, hInst, NULL
	);

	if (*hWnd == NULL) {
		MessageBox(hPaWnd, TEXT("�E�B���h�E�̐����Ɏ��s���܂����D"), NULL, MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}
