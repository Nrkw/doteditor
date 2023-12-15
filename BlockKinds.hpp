#pragma once
#include "12_1_0\DxLib.h"
#include <vector>

class BlockKinds
{
    public:

    std::vector<unsigned int> block_colors =
    {
        //レンガブロックの色
        GetColor(255, 255, 255),

        //空白ブロックの色
        GetColor(0, 0, 0),

        //クエスチョンブロックの色
        GetColor(255, 0, 0),

        GetColor(0, 255, 0)
    };
};