#include <raylib.h>
#include "./src/Task.h"
#include <vector>
#include "./src/TaskManager.h"
#include <iostream>
#include "./src/Assets.h"
#include "./src/Inventory.h"
#include "./src/Shop.h"
#include "./src/ItemLoader.h"

int main(){
    TaskManager taskManager;
    Inventory inventory;
    User user;
    CharacterRenderer characterRenderer;
    Shop shop;

    std::vector<Accessories> allItems = LoadItems();
    std::cout << "allItems size = " << allItems.size() << "\n";

    Assets assets;
    taskManager.AddTask({"Study for quiz and clean room and watch lec", false});
    taskManager.AddTask({"Study for quiz1", false});
    taskManager.AddTask({"Study for quiz2", false});
    taskManager.AddTask({"Study for quiz3", false});

    int screenWidth = 1280;
    int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Study Plan!");

    SetTargetFPS(60);

    assets.Load();
    taskManager.InitTaskPanel();


    // std::vector<Rectangle> checkboxes;
   
    while(!WindowShouldClose()){

        taskManager.UpdateScroll();
        taskManager.UpdateTaskToggle(user);
        taskManager.UpdateAddButton();
        taskManager.UpdateTaskInput();
        taskManager.DeleteTask();

        BeginDrawing();


        ClearBackground(RAYWHITE);
        Rectangle homeDest = {
            (float)screenWidth / 2 - 224,
            (float)screenHeight / 2 - 100,
            assets.characterTexture.width * 7.0f,
            assets.characterTexture.height * 7.0f
        };
        
        characterRenderer.DrawCharacter(user, assets, homeDest);

        taskManager.DrawTaskPanel();
        taskManager.DrawTasks();
        DrawTextureEx(assets.coinTexture, Vector2{1000, 20}, 0.0f, 1.0f, WHITE);
        DrawText(TextFormat("%d", taskManager.GetCoinCount(user)), 1040, 27, 20, BLACK);

        inventory.DrawButton();
        inventory.UpdateButton();
        inventory.UpdatePopup(user, allItems);
        inventory.DrawPopup(user, assets, characterRenderer, allItems);
        
        shop.DrawButton();
        shop.UpdateButton();
        shop.DrawPopup(allItems);
        shop.UpdatePopup(allItems, user);

        EndDrawing();
    }
    assets.Unload();
    CloseWindow();
    // =======================

    return 0;
}