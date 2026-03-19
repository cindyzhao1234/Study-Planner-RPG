#include <raylib.h>
#include "./src/Task.h"
#include <vector>
#include "./src/TaskManager.h"
#include <iostream>
#include "./src/Assets.h"
#include "./src/Inventory.h"

int main(){
    TaskManager taskManager;
    Inventory inventory;
    User user;
    CharacterRenderer characterRenderer;

    inventory.AddAccessory({"Blue Hat", "hat"});
    inventory.AddAccessory({"Blue Dress", "top"});
    inventory.AddAccessory({"Black Pants", "bottom"});

    Assets assets;
    taskManager.AddTask({"Study for quiz and clean room and watch lec", false});
    taskManager.AddTask({"Study for quiz1", false});
    taskManager.AddTask({"Study for quiz2", false});
    taskManager.AddTask({"Study for quiz3", false});
    // taskList.push_back({"Study for quiz", false});
    // taskList.push_back({"Finish assignment", false});
    // taskList.push_back({"Apply for internship", false});
    //===== CREATE WINDOW =====
    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Study Plan!");

    SetTargetFPS(60);

    assets.Load();
    taskManager.InitTaskPanel();


    // std::vector<Rectangle> checkboxes;
   
    while(!WindowShouldClose()){

        taskManager.UpdateScroll();
        taskManager.UpdateTaskToggle();
        taskManager.UpdateAddButton();
        taskManager.UpdateTaskInput();
        taskManager.DeleteTask();

        BeginDrawing();


        ClearBackground(RAYWHITE);
        Rectangle dest = {
            (float)screenWidth / 2 - 224,
            (float)screenHeight / 2 - 100,
            assets.characterTexture.width * 7.0f,
            assets.characterTexture.height * 7.0f
        };
        
        characterRenderer.DrawCharacter(user, assets, dest);

        taskManager.DrawTaskPanel();
        taskManager.DrawTasks();
        DrawTextureEx(assets.coinTexture, Vector2{1000, 20}, 0.0f, 1.0f, WHITE);
        DrawText(TextFormat("%d", taskManager.GetCoinCount()), 1040, 27, 20, BLACK);

        inventory.DrawButton();
        inventory.UpdateButton();
        inventory.UpdatePopup(user);
        inventory.DrawPopup(user, assets, characterRenderer);

        EndDrawing();
    }
    assets.Unload();
    CloseWindow();
    // =======================

    return 0;
}