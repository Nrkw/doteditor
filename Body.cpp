#include "Body.hpp"
#include "Rect.hpp"
#include <string>
Body::Body()
{

}
Body::~Body()
{

}
void Body::Init()
{
    block_menu->Init();
}
void Body::Render()
{
    block_editor->Render();
    //ブロックメニューを描画
    block_menu->Render();

    tool_bar->Render();
    //ダイアログを描画する
    //注意！このif文はこのRender()関数の最後に書くこと！
    if(block_menu->isPlusButtonClicked())
    {
        RenderAddDialogue();
    }else if(tool_bar->isSaveButtonClicked())
    {
        RenderSaveDialogue();
    }else if(tool_bar->isSaveGraphButtonClicked())
    {
        RenderSaveGraphDialogue();
    }else if(tool_bar->isOpenButtonClicked())
    {
        //ファイルを開くダイアログを表示する
        RenderOpenDialogue();
    }
}
void Body::AcceptInput()
{
    if(!block_menu->isPlusButtonClicked() && !tool_bar->isSaveButtonClicked() && !tool_bar->isSaveGraphButtonClicked() && !tool_bar->isOpenButtonClicked())
    {
        //ブロックメニューの入力を受け付ける(Ctrl + Zキーの入力も受け付ける)
        block_menu->AcceptInput();
        block_editor->AcceptInput(block_menu->getCurrentBlockColor());

        getKeyCharAll();
        if(keyBuf[KEY_INPUT_LCONTROL] >= 1 && keyBuf[KEY_INPUT_Z] >= 1 && !controlZLock)
        {
            controlZLock = true;
            //Ctrl + Zキーが押されたら、一つ前の状態に戻す
            block_editor->restoreBlockInfo();
        }else if(keyBuf[KEY_INPUT_LCONTROL] == 0 && keyBuf[KEY_INPUT_Z] == 0)
        {
            controlZLock = false;
        }
    }
}
int Body::getCurrentBlockColor()
{
    return block_menu->getCurrentBlockColor();
}

void Body::addColor(int color)
{
    block_menu->addColor(color);
}

void Body::RenderAddDialogue()
{
    // ダイアログの枠を描画
    int x1 = 500;
    int x2 = 1400;
    int y1 = 300;
    int y2 = 700;
    DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), 10);
    DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), 10);

    // ダイアログの背景を描画
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

    // ダイアログの閉じるボタンを描画
    int close_button_x1 = x2 - 50;
    int close_button_x2 = x2 - 10;
    int close_button_y1 = y1 + 10;
    int close_button_y2 = y1 + 50;
    DrawLine(close_button_x1, close_button_y1, close_button_x2, close_button_y2, GetColor(0, 0, 0), 5);
    DrawLine(close_button_x1, close_button_y2, close_button_x2, close_button_y1, GetColor(0, 0, 0), 5);

    // ダイアログのタイトルを描画
    SetFontSize(50);
    DrawString(x1 + 50, y1 + 50, (const TCHAR *)"色を追加する", GetColor(0, 0, 0));

    // ダイアログのテキストを描画
    SetFontSize(30);
    DrawString(x1 + 50, y1 + 150, (const TCHAR *)"16進数で値を入力", GetColor(0, 0, 0));

    // ダイアログのテキストボックスを描画
    int text_box_x1 = x1 + 50;
    int text_box_x2 = x2 - 50;
    int text_box_y1 = y1 + 200;
    int text_box_y2 = y1 + 250;
    DrawLine(text_box_x1, text_box_y1, text_box_x1, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y1, text_box_x2, text_box_y1, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x2, text_box_y1, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y2, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5); 

//ここまでちらつかない
    // textboxのキー入力を受け付け
    char add = Dialogs_getKeyInput();
//    printfDx("%c", add);
//    DrawString(100, 100, (const TCHAR *)add, GetColor(255, 0, 0));
    if(add != '\0' && add != 'q' && addDialogue_text.size() < 6 && add != 'r')
    {
        addDialogue_text += add;
    }else if(add == 'q')
    {
        if(addDialogue_text.size() > 0)
        {
            addDialogue_text.pop_back();
        }
    }else if(add == 'r')
    {
        if(addDialogue_text.size() == 6)
        {
            int R = 0;
            int G = 0;
            int B = 0;

            //16進数の文字列をRGBに変換
            std::string R_str = addDialogue_text.substr(0, 2);
            std::string G_str = addDialogue_text.substr(2, 2);
            std::string B_str = addDialogue_text.substr(4, 2);
            R = std::stoi(R_str, nullptr, 16);
            G = std::stoi(G_str, nullptr, 16);
            B = std::stoi(B_str, nullptr, 16);

            //既に入力されている色と同じ色がないかチェック
            bool isSameColor = false;
            int colors_size = block_menu->getColorSize();
            for(int i = 0; i < colors_size; i++)
            {

                if(block_menu->getColor(i) == GetColor(R, G, B))
                {
                    isSameColor = true;
                    block_menu->setColor(GetColor(R, G, B));
                    break;
                }
            }
            addDialogue_text = "";
            if(!isSameColor)
            {
                //色を追加
                block_menu->addColor(GetColor(R, G, B));
                block_menu->turnOffPlusButtonClicked();
            }else
            {
                block_menu->turnOffPlusButtonClicked();
            }
        }
    }
//    addDialogue_text = "Hello";
    //textboxの中身を描画
    SetFontSize(30);
    std::string draw_text = "#" + addDialogue_text;
    DrawString(text_box_x1 + 10, text_box_y1 + 10, (const TCHAR *)draw_text.c_str(), GetColor(0, 0, 0));
    //色のプレビューを描画
    int preview_x1 = x1 + 50;
    int preview_x2 = x2 - 50;
    int preview_y1 = y1 + 300;
    int preview_y2 = y1 + 350;
    
    int R = 0;
    int G = 0;
    int B = 0;
    //16進数の文字列をRGBに変換
    if(addDialogue_text.size() == 6)
    {
        std::string R_str = addDialogue_text.substr(0, 2);
        std::string G_str = addDialogue_text.substr(2, 2);
        std::string B_str = addDialogue_text.substr(4, 2);
        R = std::stoi(R_str, nullptr, 16);
        G = std::stoi(G_str, nullptr, 16);
        B = std::stoi(B_str, nullptr, 16);
    }
    //プレビューの色の上に"preview"という文字を描画
    SetFontSize(30);
    DrawString(preview_x1 + 10, preview_y1 - 50, (const TCHAR *)"preview", GetColor(0, 0, 0));

    //プレビューの色を描画
    DrawBox(preview_x1, preview_y1, preview_x2, preview_y2, GetColor(R, G, B), TRUE);
    //ダイアログを閉じるボタンが押されたら
    if(GetMouseInput() & MOUSE_INPUT_LEFT)
    {
        
        int mouse_x;
        int mouse_y;
        GetMousePoint(&mouse_x, &mouse_y);
        if(mouse_x >= close_button_x1 && mouse_x <= close_button_x2 && mouse_y >= close_button_y1 && mouse_y <= close_button_y2)
        {
            block_menu->turnOffPlusButtonClicked();
        }
    }
}

void Body::RenderSaveDialogue()
{
    //ダイアログを描画
    // ダイアログの枠を描画
    int x1 = 500;
    int x2 = 1400;
    int y1 = 300;
    int y2 = 700;
    DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), 10);
    DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), 10);

    // ダイアログの背景を描画
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

    // ダイアログの閉じるボタンを描画
    int close_button_x1 = x2 - 50;
    int close_button_x2 = x2 - 10;
    int close_button_y1 = y1 + 10;
    int close_button_y2 = y1 + 50;
    DrawLine(close_button_x1, close_button_y1, close_button_x2, close_button_y2, GetColor(0, 0, 0), 5);
    DrawLine(close_button_x1, close_button_y2, close_button_x2, close_button_y1, GetColor(0, 0, 0), 5);

    // ダイアログのタイトルを描画
    SetFontSize(50);
    DrawString(x1 + 50, y1 + 50, (const TCHAR *)"保存する", GetColor(0, 0, 0));
    
    // ダイアログのテキストボックスを描画
    int text_box_x1 = x1 + 50;
    int text_box_x2 = x2 - 50;
    int text_box_y1 = y1 + 200;
    int text_box_y2 = y1 + 250;
    DrawLine(text_box_x1, text_box_y1, text_box_x1, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y1, text_box_x2, text_box_y1, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x2, text_box_y1, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y2, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);

    //文字を描画
    SetFontSize(30);
    DrawString(text_box_x1, text_box_y1 + 10, (const TCHAR *)saveDialogue_text.c_str(), GetColor(0, 0, 0));

    // textboxのキー入力を受け付け
    char add = getKeyCharAll();
    if(add != '\0')
    {
        saveDialogue_text += add;
    }
    if(keyBuf[KEY_INPUT_BACK] == 1)
    {
        if(saveDialogue_text.size() > 0)
        {
            saveDialogue_text.pop_back();
        }
    }else if(keyBuf[KEY_INPUT_RETURN] == 1)
    {
        //Enterキーが押されたら、ファイルを保存
        if(saveDialogue_text.size() > 0)
        {
            //ファイルを保存
            file_manager->saveText(saveDialogue_text, block_editor);
            saveDialogue_text = "";
            tool_bar->turnOffAllMenus();
        }
    }

    //もし、ダイアログを閉じるボタンが押されたら
    {
        int pos_x;
        int pos_y;
        GetMousePoint(&pos_x, &pos_y);
        if(pos_x >= close_button_x1 && pos_x <= close_button_x2 && pos_y >= close_button_y1 && pos_y <= close_button_y2 && ( GetMouseInput() & MOUSE_INPUT_LEFT ))
        {
            tool_bar->turnOffAllMenus();
        }
    }
}
// ダイアログの入力を受け付ける（どのダイアログでも共通する処理）
char Body::Dialogs_getKeyInput()
{
    char key = '\0';

    //まず、どんなパターンでもkeyLockをtrueにする
    //何も押されていない場合はkeyLockをfalseにする
    char lockFlag  = true;
    if(CheckHitKey(KEY_INPUT_0))
    {
        key = '0';
    }else if(CheckHitKey(KEY_INPUT_1))
    {
        key = '1';
    }else if(CheckHitKey(KEY_INPUT_2))
    {
        key = '2';
    }else if(CheckHitKey(KEY_INPUT_3))
    {
        key = '3';
    }else if(CheckHitKey(KEY_INPUT_4))
    {
        key = '4';
    }else if(CheckHitKey(KEY_INPUT_5))
    {
        key = '5';
    }else if(CheckHitKey(KEY_INPUT_6))
    {
        key = '6';
    }else if(CheckHitKey(KEY_INPUT_7))
    {
        key = '7';
    }else if(CheckHitKey(KEY_INPUT_8))
    {
        key = '8';
    }else if(CheckHitKey(KEY_INPUT_9))
    {
        key = '9';
    }else if(CheckHitKey(KEY_INPUT_A))
    {
        key = 'A';
    }else if(CheckHitKey(KEY_INPUT_B))
    {
        key = 'B';
    }else if(CheckHitKey(KEY_INPUT_C))
    {
        key = 'C';
    }else if(CheckHitKey(KEY_INPUT_D))
    {
        key = 'D';
    }else if(CheckHitKey(KEY_INPUT_E))
    {
        key = 'E';
    }else if(CheckHitKey(KEY_INPUT_F))
    {
        key = 'F';
    }else if(CheckHitKey(KEY_INPUT_BACK))
    {
        key = 'q';
    }else if(CheckHitKey(KEY_INPUT_RETURN))
    {
        key = 'r';
    }else
    {
        lockFlag = false;
    }

    //初めてキーが押されるとき
    if(lockFlag && !keyLock)
    {
        keyLock = true;
        return key;
    }else if(keyLock)
    {
        //キーが押され続けているとき

        if(!lockFlag)
        {
            //キーが離されたとき、keyLockをfalseにする
            keyLock = false;
        }
    }

    return '\0';
}

void Body::RenderSaveGraphDialogue()
{
    //ダイアログを表示する
    // ダイアログの枠を描画
    int x1 = 500;
    int x2 = 1400;
    int y1 = 300;
    int y2 = 700;
    DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), 10);
    DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), 10);

    // ダイアログの背景を描画
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

    //ダイアログのタイトルを描画
    SetFontSize(50);
    DrawString(x1 + 50, y1 + 50, (const TCHAR *)"画像を保存", GetColor(0, 0, 0));

    // ダイアログの閉じるボタンを描画
    int close_button_x1 = x2 - 50;
    int close_button_x2 = x2 - 10;
    int close_button_y1 = y1 + 10;
    int close_button_y2 = y1 + 50;
    DrawLine(close_button_x1, close_button_y1, close_button_x2, close_button_y2, GetColor(0, 0, 0), 5);
    DrawLine(close_button_x1, close_button_y2, close_button_x2, close_button_y1, GetColor(0, 0, 0), 5);

    char add = getKeyCharAll();
    if(add != '\0')
    {
        saveDialogue_text += add;
    }
    if(keyBuf[KEY_INPUT_BACK] == 1)
    {
        if(saveDialogue_text.size() > 0)
        {
            saveDialogue_text.pop_back();
        }
    }else if(keyBuf[KEY_INPUT_RETURN] == 1)
    {
        //Enterキーが押されたら、ファイルを保存
        if(saveDialogue_text.size() > 0)
        {
            //ファイルを保存
            file_manager->saveGraph(saveDialogue_text, block_editor);
            saveDialogue_text = "";
            tool_bar->turnOffAllMenus();
        }
    }
    
    //テキストボックスを描画
    int text_box_x1 = x1 + 50;
    int text_box_x2 = x2 - 50;
    int text_box_y1 = y1 + 200;
    int text_box_y2 = y1 + 250;
    DrawLine(text_box_x1, text_box_y1, text_box_x1, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y1, text_box_x2, text_box_y1, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x2, text_box_y1, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y2, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);
    //テキストボックスの中身を描画
    SetFontSize(30);
    DrawString(text_box_x1 + 10, text_box_y1 + 10, (const TCHAR *)saveDialogue_text.c_str(), GetColor(0, 0, 0));

    //もし閉じるボタンが押されたら、ダイアログを閉じる
    {
        int pos_x;
        int pos_y;
        GetMousePoint(&pos_x, &pos_y);
        if(pos_x >= close_button_x1 && pos_x <= close_button_x2 && pos_y >= close_button_y1 && pos_y <= close_button_y2 && ( GetMouseInput() & MOUSE_INPUT_LEFT ))
        {
            tool_bar->turnOffAllMenus();
        }
    }

    
}

void Body::RenderOpenDialogue()
{
    // ダイアログの枠を描画
    int x1 = 500;
    int x2 = 1400;
    int y1 = 300;
    int y2 = 700;
    DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), 10);
    DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), 10);
    DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), 10);

    // ダイアログの背景を描画
    DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), TRUE);

    // ダイアログの閉じるボタンを描画
    int close_button_x1 = x2 - 50;
    int close_button_x2 = x2 - 10;
    int close_button_y1 = y1 + 10;
    int close_button_y2 = y1 + 50;
    DrawLine(close_button_x1, close_button_y1, close_button_x2, close_button_y2, GetColor(0, 0, 0), 5);
    DrawLine(close_button_x1, close_button_y2, close_button_x2, close_button_y1, GetColor(0, 0, 0), 5);

    // ダイアログのタイトルを描画
    SetFontSize(50);
    DrawString(x1 + 50, y1 + 50, (const TCHAR *)"ファイルを開く", GetColor(0, 0, 0));

    // ダイアログのテキストボックスを描画
    int text_box_x1 = x1 + 50;
    int text_box_x2 = x2 - 50;
    int text_box_y1 = y1 + 200;
    int text_box_y2 = y1 + 250;
    DrawLine(text_box_x1, text_box_y1, text_box_x1, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y1, text_box_x2, text_box_y1, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x2, text_box_y1, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);
    DrawLine(text_box_x1, text_box_y2, text_box_x2, text_box_y2, GetColor(0, 0, 0), 5);

    //文字を描画
    SetFontSize(30);
    DrawString(text_box_x1, text_box_y1 + 10, (const TCHAR *)openDialogue_text.c_str(), GetColor(0, 0, 0));

    char add = getKeyCharAll();
    if(add != '\0')
    {
        openDialogue_text += add;
    }
    if(keyBuf[KEY_INPUT_BACK] == 1)
    {
        if(openDialogue_text.size() > 0)
        {
            openDialogue_text.pop_back();
        }
    }else if(keyBuf[KEY_INPUT_RETURN] == 1)
    {
        //Enterキーが押されたら、ファイルを開く
        if(openDialogue_text.size() > 0)
        {
            //ファイルを開く
            block_editor = file_manager->openText(openDialogue_text, block_menu);
            openDialogue_text = "";
            tool_bar->turnOffAllMenus();
        }
    }
}

/*
    キーの入力状況を取得する。
    返り値を使うことで、今どのキーが押されているかをchar型で取得できる。

    また、この関数を呼び出すと、keyBufの中身が更新される。
    この関数を呼び出した後に、if(keyBuf[KEY_INPUT_A] == 1)のようにすると、キーを押されたら一度だけ処理を行うことができる。
    また、if(keyBuf[KEY_INPUT_A] >= 1)のようにすると、キーを押されている間ずっと処理を行うことができる。

*/
char Body::getKeyCharAll()
{
    char tmpKey[256] = { 0 };
    GetHitKeyStateAll(tmpKey);
    for(int i = 0; i < 256; i++)
    {
        if(tmpKey[i] == 1)
        {
            keyBuf[i]++;
        }else
        {
            keyBuf[i] = 0;
        }
    }
    if(keyBuf[KEY_INPUT_0] == 1)
    {
        return '0';
    }
    if(keyBuf[KEY_INPUT_1] == 1)
    {
        return '1';
    }
    if(keyBuf[KEY_INPUT_2] == 1)
    {
        return '2';
    }
    if(keyBuf[KEY_INPUT_3] == 1)
    {
        return '3';
    }
    if(keyBuf[KEY_INPUT_4] == 1)
    {
        return '4';
    }
    if(keyBuf[KEY_INPUT_5] == 1)
    {
        return '5';
    }
    if(keyBuf[KEY_INPUT_6] == 1)
    {
        return '6';
    }
    if(keyBuf[KEY_INPUT_7] == 1)
    {
        return '7';
    }
    if(keyBuf[KEY_INPUT_8] == 1)
    {
        return '8';
    }
    if(keyBuf[KEY_INPUT_9] == 1)
    {
        return '9';
    }
    if(keyBuf[KEY_INPUT_A] == 1)
    {
        return 'A';
    }
    if(keyBuf[KEY_INPUT_B] == 1)
    {
        return 'B';
    }
    if(keyBuf[KEY_INPUT_C] == 1)
    {
        return 'C';
    }
    if(keyBuf[KEY_INPUT_D] == 1)
    {
        return 'D';
    }
    if(keyBuf[KEY_INPUT_E] == 1)
    {
        return 'E';
    }
    if(keyBuf[KEY_INPUT_F] == 1)
    {
        return 'F';
    }
    if(keyBuf[KEY_INPUT_G] == 1)
    {
        return 'G';
    }
    if(keyBuf[KEY_INPUT_H] == 1)
    {
        return 'H';
    }
    if(keyBuf[KEY_INPUT_I] == 1)
    {
        return 'I';
    }
    if(keyBuf[KEY_INPUT_J] == 1)
    {
        return 'J';
    }
    if(keyBuf[KEY_INPUT_K] == 1)
    {
        return 'K';
    }
    if(keyBuf[KEY_INPUT_L] == 1)
    {
        return 'L';
    }
    if(keyBuf[KEY_INPUT_M] == 1)
    {
        return 'M';
    }
    if(keyBuf[KEY_INPUT_N] == 1)
    {
        return 'N';
    }
    if(keyBuf[KEY_INPUT_O] == 1)
    {
        return 'O';
    }
    if(keyBuf[KEY_INPUT_P] == 1)
    {
        return 'P';
    }
    if(keyBuf[KEY_INPUT_Q] == 1)
    {
        return 'Q';
    }
    if(keyBuf[KEY_INPUT_R] == 1)
    {
        return 'R';
    }
    if(keyBuf[KEY_INPUT_S] == 1)
    {
        return 'S';
    }
    if(keyBuf[KEY_INPUT_T] == 1)
    {
        return 'T';
    }
    if(keyBuf[KEY_INPUT_U] == 1)
    {
        return 'U';
    }
    if(keyBuf[KEY_INPUT_V] == 1)
    {
        return 'V';
    }
    if(keyBuf[KEY_INPUT_W] == 1)
    {
        return 'W';
    }
    if(keyBuf[KEY_INPUT_X] == 1)
    {
        return 'X';
    }
    if(keyBuf[KEY_INPUT_Y] == 1)
    {
        return 'Y';
    }
    if(keyBuf[KEY_INPUT_Z] == 1)
    {
        return 'Z';
    }
    if(keyBuf[KEY_INPUT_PERIOD] == 1)
    {
        return '.';
    }
    return '\0';
}
