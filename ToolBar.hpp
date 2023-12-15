#pragma once
#include "12_1_0\DxLib.h"

enum class ToolType
{
    Save,
    Load,
    Delete,
};

class ToolBar
{
public:
    ToolBar();
    ~ToolBar();

    void Render();
    void AcceptInput();

    // プラスボタンが押され、ダイアログが閉じられたときに呼び出す。プラスボタンが押された状態を解除する。
    void turnOffAllMenus();

 
    bool isSaveButtonClicked();
    bool isSaveGraphButtonClicked();
    bool isOpenButtonClicked();
private:

    bool is_save_button_clicked = false;
    bool is_save_graph_button_clicked = false;
    bool is_open_button_clicked = false;

};