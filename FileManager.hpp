#pragma once
#include <string>
#include <memory>
#include "BlockEditor.hpp"
#include "BlockMenu.hpp"
class FileManager
{
    public:

    FileManager();
    ~FileManager();

    void saveText(std::string fileName, std::shared_ptr<BlockEditor> block_editor);
    void saveGraph(std::string fileName, std::shared_ptr<BlockEditor> block_editor);
    std::shared_ptr<BlockEditor> openText(std::string fileName, std::shared_ptr<BlockMenu> block_menu);
};