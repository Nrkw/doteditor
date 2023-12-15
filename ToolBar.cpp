#include "ToolBar.hpp"

ToolBar::ToolBar()
{
}
ToolBar::~ToolBar()
{
}
void ToolBar::Render()
{
    // ツールバーの枠を描画
    //ツールバーは画面最下部に固定される
    int x1 = 0;
    int x2 = 1500;
    int y1 = 1080 - 100;
    int y2 = 1080;

    DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), 10);
    DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), 10);

    // ツールバーの背景を描画
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

    // ツールバーのボタンを描画
    int button_x1 = 100;
    int button_x2 = 500;
    int button_y1 = 990;
    int button_y2 = 1050;;
    DrawBox(button_x1, button_y1, button_x2, button_y2, GetColor(255, 255, 255), TRUE);
    DrawLine(button_x1, button_y1, button_x1, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x1, button_y1, button_x2, button_y1, GetColor(0, 0, 0), 10);
    DrawLine(button_x2, button_y1, button_x2, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x1, button_y2, button_x2, button_y2, GetColor(0, 0, 0), 10);

    // ボタンの中に文字を描画
    DrawFormatString(button_x1 + 10, button_y1 + 10, GetColor(0, 0, 0), (const TCHAR *)"テキストで保存");

    //二つ目のツールバーのボタンを描画
    int button_x3 = 600;
    int button_x4 = 1000;
    DrawBox(button_x3, button_y1, button_x4, button_y2, GetColor(255, 255, 255), TRUE);
    //枠を描画
    DrawLine(button_x3, button_y1, button_x3, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x3, button_y1, button_x4, button_y1, GetColor(0, 0, 0), 10);
    DrawLine(button_x4, button_y1, button_x4, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x3, button_y2, button_x4, button_y2, GetColor(0, 0, 0), 10);

    DrawString(button_x3 + 10, button_y1 + 10, (const TCHAR *)"画像を保存", GetColor(0, 0, 0));

    //三つ目のツールバーのボタンを描画
    int button_x5 = 1100;
    int button_x6 = 1500;
    DrawBox(button_x5, button_y1, button_x6, button_y2, GetColor(255, 255, 255), TRUE);
    //枠を描画
    DrawLine(button_x5, button_y1, button_x5, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x5, button_y1, button_x6, button_y1, GetColor(0, 0, 0), 10);
    DrawLine(button_x6, button_y1, button_x6, button_y2, GetColor(0, 0, 0), 10);
    DrawLine(button_x5, button_y2, button_x6, button_y2, GetColor(0, 0, 0), 10);
    //文字を描画
    DrawString(button_x5 + 10, button_y1 + 10, (const TCHAR *)"ファイルを開く", GetColor(0, 0, 0));

    //マウスの位置を取得して、saveボタンの範囲内だったらhandleClickSaveButton()を呼び出す
    {
        int pos_x;
        int pos_y;
        GetMousePoint(&pos_x, &pos_y);
        if(pos_x >= button_x1 && pos_x <= button_x2 && pos_y >= button_y1 && pos_y <= button_y2)
        {
            if(GetMouseInput() & MOUSE_INPUT_LEFT)
            {
                //いったんすべてのダイアログを閉じる
                turnOffAllMenus();
                is_save_button_clicked = true;
            }
        }else if(pos_x >= button_x3 && pos_x <= button_x4 + 200 && pos_y >= button_y1 && pos_y <= button_y2)
        {
            if(GetMouseInput() & MOUSE_INPUT_LEFT)
            {
                //いったんすべてのダイアログを閉じる
                turnOffAllMenus();
                is_save_graph_button_clicked = true;
            }
        }else if(pos_x >= button_x5 && pos_x <= button_x6 && pos_y >= button_y1 && pos_y <= button_y2)
        {
            if(GetMouseInput() & MOUSE_INPUT_LEFT)
            {
                //いったんすべてのダイアログを閉じる
                turnOffAllMenus();
                is_open_button_clicked = true;
            }
        }
    }
}

void ToolBar::AcceptInput()
{
    
}

void ToolBar::turnOffAllMenus()
{
    is_save_button_clicked = false;
    is_save_graph_button_clicked = false;
    is_open_button_clicked = false;
}

bool ToolBar::isSaveButtonClicked()
{
    return is_save_button_clicked;
}

bool ToolBar::isSaveGraphButtonClicked()
{
    return is_save_graph_button_clicked;
}
bool ToolBar::isOpenButtonClicked()
{
    return is_open_button_clicked;
}