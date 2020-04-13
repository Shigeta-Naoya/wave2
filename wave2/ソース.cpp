#include <windows.h>		//Windows環境
#include <windowsx.h>		//Windows環境
#include <stdio.h>			//入出力用
#include <process.h>		//スレッド用
#include <stdlib.h>

#pragma comment(lib,"winmm.lib")//高精度タイマ

#include "resource.h"		//リソースファイル
#include "ヘッダー.h"		//リソースファイル

//構造体
typedef struct {
	HWND	hwnd;
	HWND	hEdit;
}SEND_POINTER_STRUCT;

//メイン関数(ダイアログバージョン)
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	HANDLE hMutex;

	//多重起動判定
	hMutex = CreateMutex(NULL, TRUE, DEF_MUTEX_NAME);		//ミューテックスオブジェクトの生成
	if (GetLastError() == ERROR_ALREADY_EXISTS) {				//2重起動の有無を確認
		MessageBox(NULL, TEXT("既に起動されています．"), NULL, MB_OK | MB_ICONERROR);
		return 0;											//終了
	}

	//ダイアログ起動
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, MainDlgProc);

	return FALSE;			//終了
}

//メインプロシージャ（ダイアログ）
BOOL CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HFONT hFont;				//フォント
	static HANDLE hThread;
	static UINT thID;
	static SEND_POINTER_STRUCT Sps;
	static HWND hPict1;		//ウィンドウハンドル（PictureBox）
	static HWND hPict2;
	static HWND hWnd;

	switch (uMsg) {
	case WM_INITDIALOG:		//ダイアログ初期化
		Sps.hwnd = hDlg;
		


		//初期化(軸背景の描画の起動)

		return TRUE;

	case WM_COMMAND:		//ボタンが押された時
		switch (LOWORD(wParam)) {
		case IDOK:			//OKボタン
				
			hPict2 = GetDlgItem(hDlg, IDC_PICTBOX2);
			//開始ボタン無効化　　　　//EnableWindowで入力を無効または有効にする。

			WinInitialize(NULL, hDlg, (HMENU)110, "TEST", hPict2, WndProc, &hWnd);

			color = RGB(0, 0, 0);			//色指定
			InvalidateRect(hWnd, NULL, TRUE);
						//色指定
			

			return TRUE;

		case IDCANCEL:		//キャンセルボタン
			EndDialog(hDlg, 0);		//ダイアログ終了
			return TRUE;
			
		}
		break;

	case WM_CLOSE:
		EndDialog(hDlg, 0);			//ダイアログ終了
		return TRUE;
}

return FALSE;
}

HRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

	HDC			hdc1;				//デバイスコンテキストのハンドル
	HDC			hdc2;
	PAINTSTRUCT ps;					//(構造体)クライアント領域描画するための情報	
	HBRUSH		hBrush, hOldBrush;	//ブラシ
	HPEN		hPen, hOldPen;		//ペン

	switch (uMsg) {
	case WM_CREATE:
		colorPen = RGB(0, 0, 0);	//色指定
		//colorPen = color;	//色指定
		break;

	case WM_PAINT:

		/********************************

		PictureControlに描画するためには，HDC型のハンドルを別に取得する
		必要があります．

		例：hdc = BeginPaint(hWnd, &ps);
		hdc:デバイスコンテキストのハンドル
		hWnd:PictureControlのハンドル
		ps：(構造体)クライアント領域描画するための情報

		********************************/

		hdc1 = BeginPaint(hWnd, &ps);//デバイスコンテキストのハンドル取得
		hdc2 = BeginPaint(hWnd, &ps);

		/********************************

		PictureControlに描画するためには，線を引きたいときはペン，
		塗りつぶす際にはブラシが必要です．

		********************************/

		//ペン，ブラシ生成
		hBrush = CreateSolidBrush(color);				//ブラシ生成
		hOldBrush = (HBRUSH)SelectObject(hdc1, hBrush);	//ブラシ設定
		hOldBrush = (HBRUSH)SelectObject(hdc2, hBrush);
		hPen = CreatePen(PS_SOLID, 2, colorPen);		//ペン生成
		hOldPen = (HPEN)SelectObject(hdc1, hPen);		//ペン設定
		hOldPen = (HPEN)SelectObject(hdc2, hPen);

		//描画
		/********************************

		図形を描画するためには以下の関数を用います．
		長方形：Rectangle(HDC hdc ,int nLeftRect , int nTopRect ,int nRightRect , int nBottomRect);
		円：Ellipse(HDC hdc ,int nLeftRect , int nTopRect ,int nRightRect , int nBottomRect);

		 nLiftRect：長方形の左上X座標
		  nTopRect：左上Y座標
		  nRightRect：右下X座標
		  nBottomRect：右下のY座標

		線を引くには以下の関数を用います．

		線の始点設定：MoveToEx(HDC hdc , int X , int Y , NULL);
		  X,Y：線の始点の座標
		線；LineTo(HDC hdc , int nXEnd , int nYEnd);
		  nXEnd, nYEnd：線の終点の設定


		  以上を参考に図形を描画する関数を以下に記述しましょう
		********************************/
		//ここから

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
		//ペン，ブラシ廃棄
		/********************************

		使い終わったペンとブラシは破棄する必要があります．

		********************************/
		

		//デバイスコンテキストのハンドル破棄
		EndPaint(hWnd, &ps);
		break;
	}

	return TRUE;
}

BOOL WinInitialize(HINSTANCE hInst, HWND hPaWnd, HMENU chID, char* cWinName, HWND PaintArea, WNDPROC WndProc, HWND* hWnd)
{
	WNDCLASS wc;			//ウィンドウクラス
	WINDOWPLACEMENT	wplace;	//子ウィンドウ生成領域計算用（画面上のウィンドウの配置情報を格納する構造体）
	RECT WinRect;			//子ウィンドウ生成領域
	ATOM atom;				//アトム

	//ウィンドウクラス初期化
	wc.style = CS_HREDRAW ^ WS_MAXIMIZEBOX | CS_VREDRAW;	//ウインドウスタイル
	wc.lpfnWndProc = WndProc;									//ウインドウのメッセージを処理するコールバック関数へのポインタ
	wc.cbClsExtra = 0;											//
	wc.cbWndExtra = 0;
	wc.hCursor = NULL;										//プログラムのハンドル
	wc.hIcon = NULL;										//アイコンのハンドル
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);		//ウインドウ背景色
	wc.hInstance = hInst;										//ウインドウプロシージャがあるインスタンスハンドル
	wc.lpszMenuName = NULL;										//メニュー名
	wc.lpszClassName = (LPCTSTR)cWinName;									//ウインドウクラス名

	if (!(atom = RegisterClass(&wc))) {
		MessageBox(hPaWnd, TEXT("ウィンドウクラスの生成に失敗しました．"), NULL, MB_OK | MB_ICONERROR);
		return false;
	}

	GetWindowPlacement(PaintArea, &wplace);	//描画領域ハンドルの情報を取得(ウィンドウの表示状態を取得)
	WinRect = wplace.rcNormalPosition;		//描画領域の設定

	//ウィンドウ生成
	*hWnd = CreateWindow(
		(LPCTSTR)atom,
		(LPCTSTR)cWinName,
		WS_CHILD | WS_VISIBLE,//| WS_OVERLAPPEDWINDOW ^ WS_MAXIMIZEBOX ^ WS_THICKFRAME |WS_VISIBLE, 
		WinRect.left, WinRect.top,
		WinRect.right - WinRect.left, WinRect.bottom - WinRect.top,
		hPaWnd, chID, hInst, NULL
	);

	if (*hWnd == NULL) {
		MessageBox(hPaWnd, TEXT("ウィンドウの生成に失敗しました．"), NULL, MB_OK | MB_ICONERROR);
		return false;
	}

	return true;
}
