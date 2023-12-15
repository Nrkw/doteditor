#pragma once
#include "BlockKinds.hpp"
#include "12_1_0\DxLib.h"
#include <memory>


constexpr int BLOCK_SIZE = 64;
constexpr int BLOCK_PADDING_Y = 50;
constexpr int BLOCK_PADDING_X = 50;
class BlockMenu
{
public:
    BlockMenu();
    ~BlockMenu();

    void Init();
    void Render();
    void AcceptInput();
    bool isPlusButtonClicked();

    // プラスボタンが押され、ダイアログが閉じられたときに呼び出す。プラスボタンが押された状態を解除する。
    void turnOffPlusButtonClicked();

    int getCurrentBlockColor();
    void addColor(int color);

    //既に色が存在するかどうか、存在するならtrueを返す
    bool isColorExists(int color);
    int getColor(int index);
    void setColor(int color);
    int getColorSize();
    private:
    std::unique_ptr<BlockKinds> block_kinds = std::make_unique<BlockKinds>();

    bool is_plus_button_clicked = false;
    int current_block_color = GetColor(0, 0, 0);
};