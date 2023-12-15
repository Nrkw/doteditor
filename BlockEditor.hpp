#pragma once
#include "12_1_0\DxLib.h"
#include "utils.hpp"
#include <vector>
#include <map>
class BlockEditor
{
    public:
        BlockEditor();
        ~BlockEditor();

        void Render();
        void AcceptInput(int currentColor);

        int getColorSize();
        int getDrawingBlockSize();
        std::vector<util::PointColor> getBlockInfo();
        void addPoint(int x, int y, int color);

        //Ctrl + Zで、一つ前の状態に戻す
        void restoreBlockInfo();
    private:
    //{x, y} -> colorが一組になったmapを持つvector
    // std::vector<std::map<util::Point, int>> block_info;
    // std::vector<std::pair<std::map<util::Point, int>, int>> block_info;
    std::vector<util::PointColor> block_info;

    std::vector<std::vector<util::PointColor>> previous_block_info;
   
    //マウスが押された状態かどうか、押されたらtrue、離されたらfalse
    //このフラグを使って、履歴を保存する
    bool isDrawing = false;

    //Ctrl + Zを何回も押している状態か
    bool isGoingback = false;

    int drawing_block_size = 64;
    void deletePoint(int x, int y);
};
