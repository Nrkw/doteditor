#pragma once
#include "BlockMenu.hpp"
#include "BlockEditor.hpp"
#include "ToolBar.hpp"
#include "FileManager.hpp"
#include <memory>
#include <string>
class Body
{

public:
    Body();
    ~Body();

    void Init();
    void Render();
    void AcceptInput();
    int getCurrentBlockColor();
private:

    void addColor(int color);

    // ダイアログの入力を受け付ける（どのダイアログでも共通する処理）、16進数のみ受け付ける
    char Dialogs_getKeyInput();

    // ダイアログの入力を受け付ける（どのダイアログでも共通する処理）、16進数以外も受け付ける　例：Enterキー,E
    char getKeyCharAll();
    void RenderAddDialogue();
    void RenderSaveDialogue();
    void RenderSaveGraphDialogue();
    void RenderOpenDialogue();

    std::string addDialogue_text = "";

    std::string saveDialogue_text = "";

    std::string openDialogue_text = "";

    std::shared_ptr<BlockMenu> block_menu = std::make_shared<BlockMenu>();
    // std::unique_ptr<BlockEditor> block_editor = std::make_unique<BlockEditor>();
    std::shared_ptr<BlockEditor> block_editor = std::make_shared<BlockEditor>();
    std::unique_ptr<ToolBar> tool_bar = std::make_unique<ToolBar>();
    
    std::unique_ptr<FileManager> file_manager = std::make_unique<FileManager>();
    

    int keyBuf[256] = { 0 };
    bool keyLock = false;

    //Ctrl + Zのコマンドを受け付けるときにtrueになる
    //コマンドをフレーム更新ごとに何回も受け付けないようにするため
    bool controlZLock = false;
};
