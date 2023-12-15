#include "FileManager.hpp"
#include "BlockEditor.hpp"
#include "BlockMenu.hpp"
#include "utils.hpp"
#include <memory>

FileManager::FileManager()
{

}
FileManager::~FileManager()
{

}
void FileManager::saveText(std::string file_name, std::shared_ptr<BlockEditor> block_editor)
{
    //保存処理
    FILE *fp;
    fp = fopen(file_name.c_str(), "w");
    if(fp == NULL)
    {
        printfDx((const TCHAR *)"ファイルを開けませんでした");
    }else
    {
        int block_info_size = block_editor->getBlockInfo().size();
        for(int i = 0; i < block_info_size; i++)
        {
            util::PointColor point_color = block_editor->getBlockInfo()[i];
            std::string write_text = std::to_string(point_color.x) + "," + std::to_string(point_color.y) + "," + std::to_string(point_color.color) + "\n";
            fputs(write_text.c_str(), fp);
        }
        fclose(fp);
    }
}

void FileManager::saveGraph(std::string file_name, std::shared_ptr<BlockEditor> block_editor)
{

    //画像を保存する
    printfDx((const TCHAR *)"保存");

    int MapSizeX = 1920;
    int MapSizeY = 1080;

    int saveScreen = MakeScreen(MapSizeX, MapSizeY, true);

    SetDrawScreen(saveScreen);

    std::vector<util::PointColor> block_info = block_editor->getBlockInfo();
    int block_size = block_editor->getDrawingBlockSize();
    
    for(auto& point_color : block_info)
    {
        int x = point_color.x;
        int y = point_color.y;
        int color = point_color.color;
        DrawBox(x * block_size, y * block_size, x * block_size + block_size, y * block_size + block_size, color, TRUE);
    }

    file_name += ".jpg";
    SaveDrawScreenToJPEG(0, 0, MapSizeX, MapSizeY, (const TCHAR *)file_name.c_str(), 80);
    SetDrawScreen(DX_SCREEN_BACK);
    DeleteGraph(saveScreen);
    // SaveDrawScreen(0, 0, 1920, 1080, file_name.c_str());
}

std::shared_ptr<BlockEditor> FileManager::openText(std::string file_name, std::shared_ptr<BlockMenu> block_menu)
{
    std::shared_ptr<BlockEditor> block_editor = std::make_shared<BlockEditor>();
    //開く処理
    FILE *fp;
    fp = fopen(file_name.c_str(), "r");
    if(fp == NULL)
    {
        printfDx((const TCHAR *)"ファイルを開けませんでした");
    }else
    {
        //ファイルの中身を読み込む
        char str[256];
        while(fgets(str, 256, fp) != NULL)
        {
            // printfDx((const TCHAR *)str);
            std::string str_str = str;
            std::vector<std::string> split_str = util::split(str_str, ',');
            int x = std::stoi(split_str[0]);
            int y = std::stoi(split_str[1]);
            int color = std::stoi(split_str[2]);
            block_editor->addPoint(x, y, color);

            if(!block_menu->isColorExists(color))
            {
                block_menu->addColor(color);
            }
        }
        fclose(fp);
    }
    return block_editor;
}