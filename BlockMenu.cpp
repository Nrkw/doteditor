#include "BlockMenu.hpp"
#include "Const.hpp"
#include "12_1_0\DxLib.h"
BlockMenu::BlockMenu()
{

}
BlockMenu::~BlockMenu()
{

}
void BlockMenu::Init()
{
    
}
void BlockMenu::Render()
{
    // メニューを描画する上での基準座標
    const int DrawY = Const::MENU_Y1;
    const int DrawX = Const::MENU_X1;

    
    //メニューの背景を描画
    DrawBox(0, DrawY - (2 * BLOCK_PADDING_Y), 1920, 1080, GetColor(242, 242, 242), TRUE);
    // メニューとエディターを隔てる線を描画
    DrawLine(0, DrawY - (2 *BLOCK_PADDING_Y), 1920, DrawY - (2 *BLOCK_PADDING_Y), GetColor(0, 0, 0), 20);

    
    ///ブロックの色の数
    int colors_size = block_kinds->block_colors.size();
    for(int i = 0; i < colors_size + 1; i++)
    {
        int x1 = DrawX + BLOCK_PADDING_X * i + BLOCK_SIZE * i;
        int x2 = DrawX + BLOCK_PADDING_X * i + (BLOCK_SIZE * i) + BLOCK_SIZE;
        int y1 = DrawY;
        int y2 = DrawY + BLOCK_SIZE;

        // ブロックの枠を描画(選択されているブロックの枠は太くする)
        int borderThickness = 3;
        if(i <= colors_size - 1 && block_kinds->block_colors[i] == current_block_color)
        {
            borderThickness = 10;
        }
        DrawLine(x1, y1, x1, y2, GetColor(0, 0, 0), borderThickness);
        DrawLine(x1, y1, x2, y1, GetColor(0, 0, 0), borderThickness);
        DrawLine(x2, y1, x2, y2, GetColor(0, 0, 0), borderThickness);
        DrawLine(x1, y2, x2, y2, GetColor(0, 0, 0), borderThickness);
        
        if(i <= colors_size - 1)
        {
            // ブロックの色を描画
            DrawBox(x1, y1, x2, y2, block_kinds->block_colors[i], TRUE);
        }else
        {
            // 最後にプラスボタンを描画
            int vertical_line_x = DrawX + BLOCK_PADDING_X * i + BLOCK_SIZE * i + (BLOCK_SIZE / 2);
            int vertical_line_y = DrawY + (BLOCK_SIZE / 2);

            // プラスボタンの縦線を描画
            DrawLine(vertical_line_x, DrawY, vertical_line_x, DrawY + BLOCK_SIZE, GetColor(125, 125, 125), 5);

            // プラスボタンの横線を描画
            DrawLine(DrawX + BLOCK_PADDING_X * i + BLOCK_SIZE * i, vertical_line_y, DrawX + BLOCK_PADDING_X * i + (BLOCK_SIZE * i) + BLOCK_SIZE, vertical_line_y, GetColor(125, 125, 125), 5);

        }

    }
}

void BlockMenu::AcceptInput()
{
    // メニューを描画する上での基準座標
    const int DrawY = 900;
    const int DrawX = 100;
    
    int colors_size = block_kinds->block_colors.size();
    for(int i = 0; i < colors_size + 1; i++)
    {
        int x1 = DrawX + BLOCK_PADDING_X * i + BLOCK_SIZE * i;
        int x2 = DrawX + BLOCK_PADDING_X * i + (BLOCK_SIZE * i) + BLOCK_SIZE;
        int y1 = DrawY;
        int y2 = DrawY + BLOCK_SIZE;

        if(GetMouseInput() & (MOUSE_INPUT_LEFT != 0))
        {
            int mouse_x;
            int mouse_y;
            GetMousePoint(&mouse_x, &mouse_y);
            if(mouse_x >= x1 && mouse_x <= x2 && mouse_y >= y1 && mouse_y <= y2)
            {
                if(i <= colors_size - 1)
                {
                    current_block_color = block_kinds->block_colors[i];
                }else
                {
                    is_plus_button_clicked = true;
                }
            }
        }
    }
}

bool BlockMenu::isPlusButtonClicked()
{
    return is_plus_button_clicked;
}
int BlockMenu::getCurrentBlockColor()
{
    return current_block_color;
}
void BlockMenu::addColor(int color)
{
    block_kinds->block_colors.push_back(color);
}

void BlockMenu::turnOffPlusButtonClicked()
{
    is_plus_button_clicked = false;
}

void BlockMenu::setColor(int color)
{
    current_block_color = color;
}
int BlockMenu::getColorSize()
{
    return block_kinds->block_colors.size();
}

int BlockMenu::getColor(int index)
{
    return block_kinds->block_colors[index];
}

bool BlockMenu::isColorExists(int color)
{
    for(auto& block_color : block_kinds->block_colors)
    {
        if(block_color == color)
        {
            return true;
        }
    }
    return false;
}