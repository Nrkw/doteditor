#include "12_1_0\DxLib.h"
#include "Body.hpp"
#include <iostream>
#include <memory>
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
    {
		std::cout << "初期化に失敗しました" << std::endl;
		return -1;
	}
	ChangeWindowMode(FALSE);
	SetGraphMode(1920, 1080, 16);
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(TRUE);
	std::cout << "DxLib_Init" << std::endl;
	// 背景を白色に設定
	SetBackgroundColor(255, 255, 255);

    std::unique_ptr<Body> body = std::make_unique<Body>();
    while(ProcessMessage() == 0)
    {
        // 画面をクリア
        ClearDrawScreen();

        body->Render();
		body->AcceptInput();
		
		// デバッグ用
		SetFontSize(50);
		// DrawString(400, 100, (const TCHAR *)"CurrentColor", body->getCurrentBlockColor());

        // 画面の更新
        ScreenFlip();


    }
	// ＤＸライブラリ使用の終了処理
	DxLib_End();
	return 0;
}
