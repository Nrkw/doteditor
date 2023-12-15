#include "BlockEditor.hpp"
#include "utils.hpp"
#include "Const.hpp"
#include <vector>
#include <map>

BlockEditor::BlockEditor()
{

}
BlockEditor::~BlockEditor()
{

}

void BlockEditor::Render()
{
    //方眼紙のような背景を描画
    for(int i = 0; i < 1920; i += drawing_block_size)
    {
        for(int j = 0; j < 1080; j += drawing_block_size)
        {
            DrawLine(i, j, i, j + 64, GetColor(0, 0, 0), 1);
            DrawLine(i, j, i + 64, j, GetColor(0, 0, 0), 1);
        }
    }
    //ブロックを描画
    for(auto block : block_info)
    {
        int x = block.x * drawing_block_size;
        int y = block.y * drawing_block_size;
        DrawBox(x, y, x + drawing_block_size, y + drawing_block_size, block.color, TRUE);
    }
}
void BlockEditor::AcceptInput(int currentColor)
{
    //pos_x, pos_yはマウスの座標
    int pos_x;
    int pos_y;
    GetMousePoint(&pos_x, &pos_y);

    //pos_x, pos_yをブロックの座標に変換
    int x = pos_x / drawing_block_size;
    int y = pos_y / drawing_block_size;
    //マウスの左ボタンが押されたら、ブロックを追加する(ただし、メニューの中でクリックされたら、ブロックを追加しない)
    if(GetMouseInput() & MOUSE_INPUT_LEFT && pos_y < Const::MENU_Y1)
    {
        isDrawing = true;
        isGoingback = false;
        addPoint(x, y, currentColor);
    }else if(GetMouseInput() & MOUSE_INPUT_RIGHT)
    {
        isDrawing = true;
        //マウスの右ボタンが押されたら、ブロックを削除する
        deletePoint(x, y);
    }else if(isDrawing)
    {
        //ブロックを追加するわけでもなく、削除するわけでもないなら、マウスのボタンが離されたということなので
        //isDrawingをfalseにする
        isDrawing = false;

        //履歴に保存する
        previous_block_info.push_back(block_info);
    }

    //マウスのホイールが回されたら、ブロックのサイズを変更する
    //ただし、ブロックのサイズは最小で10にする
    if(drawing_block_size >= 10)
    {
        drawing_block_size += GetMouseWheelRotVol();
    }else
    {
        drawing_block_size = 10;
    }
}

void BlockEditor::addPoint(int x, int y, int color)
{
    //ブロックの座標をキーにして、色を格納する
    // block_info.push_back(std::map<util::Point, int>{{x, y}, color});
    
    //クリックされた座標にすでに色がついたブロックが格納されていたら、色を上書きする
    for(int i = 0; i < block_info.size(); i++)
    {
        if(block_info[i].x == x && block_info[i].y == y)
        {
            if(block_info[i].color == color)
            {
                //同じ色で上書きしようとしたら、何もしない
                return;
            }
            
            //違う色で上書きしようとしたら、そのブロックを削除して、新しいブロックを追加する
            block_info.erase(block_info.begin() + i);
            // printfDx((const TCHAR *)"erase");
            return;
        }
    }
    block_info.push_back(util::PointColor{x, y, color});
}

void BlockEditor::deletePoint(int x, int y)
{
    for(int i = 0; i < block_info.size(); i++)
    {
        if(block_info[i].x == x && block_info[i].y == y)
        {
            block_info.erase(block_info.begin() + i);
            return;
        }
    }
}


std::vector<util::PointColor> BlockEditor::getBlockInfo()
{
    return block_info;
}

int BlockEditor::getColorSize()
{
    return block_info.size();
}
int BlockEditor::getDrawingBlockSize()
{
    return drawing_block_size;
}

void BlockEditor::restoreBlockInfo()
{

    if(previous_block_info.size() >= 2)
    {
        printfDx((const TCHAR *)"restore");
        //一つ前の状態に戻す
        /*
        if(!isGoingback)
        {
            previous_block_info.pop_back();
            isGoingback = true;
        }*/


        block_info = previous_block_info[previous_block_info.size() - 2];
        // block_info = previous_block_info.back();
        //一つ前の状態を履歴から削除する
        previous_block_info.pop_back();
    }
    //履歴がないなら、block_infoをクリアする
    else if(previous_block_info.size() <= 1)
    {
        block_info.clear();
        previous_block_info.clear();
        return;
    }
}