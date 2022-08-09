#include "StageClear.h"
#include "CursorManager.h"
#include "InputManager.h"
#include "SceneManager.h"

StageClear::StageClear()
{
}

StageClear::~StageClear()
{
}

void StageClear::Initialize()
{  
    Text[0] = (char*)"       d888888o. 8888888 8888888888   .8.           ,o888888o.    8 888888888888";
    Text[1] = (char*)"     .`8888:' `88.     8 8888        .888.         8888     `88.  8 8888        ";
    Text[2] = (char*)"     8.`8888.   Y8     8 8888       :88888.     ,8 8888       `8. 8 8888        ";
    Text[3] = (char*)"     `8.`8888.         8 8888      . `88888.    88 8888           8 8888        ";
    Text[4] = (char*)"      `8.`8888.        8 8888     .8. `88888.   88 8888           8 888888888888";
    Text[5] = (char*)"       `8.`8888.       8 8888    .8`8. `88888.  88 8888           8 8888        ";
    Text[6] = (char*)"        `8.`8888.      8 8888   .8' `8. `88888. 88 8888   8888888 8 8888        ";
    Text[7] = (char*)"    8b   `8.`8888.     8 8888  .8'   `8. `88888.`8 8888       .8' 8 8888        ";
    Text[8] = (char*)"    `8b.  ;8.`8888     8 8888 .888888888. `88888.  8888     ,88'  8 8888        ";
    Text[9] = (char*)"     `Y8888P ,88P'     8 8888.8'       `8. `88888.  `8888888P'    8 888888888888";
    Text[10] = (char*)"                                                                                     "; 
    Text[11] = (char*)"    ,o888888o.    8 8888         8 8888888888            .8.          8 888888888o.  "; 
    Text[12] = (char*)"   8888     `88.  8 8888         8 8888                 .888.         8 8888    `88. "; 
    Text[13] = (char*)",8 8888       `8. 8 8888         8 8888                :88888.        8 8888     `88 "; 
    Text[14] = (char*)"88 8888           8 8888         8 8888               . `88888.       8 8888     ,88 "; 
    Text[15] = (char*)"88 8888           8 8888         8 888888888888      .8. `88888.      8 8888.   ,88' "; 
    Text[16] = (char*)"88 8888           8 8888         8 8888             .8`8. `88888.     8 888888888P'  "; 
    Text[17] = (char*)"88 8888           8 8888         8 8888            .8' `8. `88888.    8 8888`8b      "; 
    Text[18] = (char*)"`8 8888       .8' 8 8888         8 8888           .8'   `8. `88888.   8 8888 `8b.    "; 
    Text[19] = (char*)"   8888     ,88'  8 8888         8 8888          .888888888. `88888.  8 8888   `8b.  "; 
    Text[20] = (char*)"    `8888888P'    8 888888888888 8 888888888888 .8'       `8. `88888. 8 8888     `88."; 
}

void StageClear::Update()
{
    DWORD dwKey = InputManager::GetInstance()->GetKey();

    if (dwKey & KEY_ENTER)
        SceneManager::GetInstance()->SetScene(MENU);
}

void StageClear::Render()
{
    for (int i = 0; i < 21; ++i)
        CursorManager::GetInstance()->WriteBuffer(49.0f, 13.0f + i, Text[i]);
}

void StageClear::Release()
{
}
