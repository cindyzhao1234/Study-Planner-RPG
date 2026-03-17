#include <raylib.h>
#include "./src/Task.h"
#include <vector>
#include "./src/TaskManager.h"
#include <iostream>

int main(){
    TaskManager taskManager;
    taskManager.AddTask({"Study for quiz", false});
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

    taskManager.InitTaskPanel();


    // std::vector<Rectangle> checkboxes;
   
    while(!WindowShouldClose()){

        

        BeginDrawing();


        ClearBackground(RAYWHITE);
        // int posX = 100;
        // int posY = 100;
        // for(int i = 0; i < tasks.size(); i++){
        //     DrawText(tasks[i].taskDescription.c_str(), posX, posY, 12, tasks[i].color);
        //     Rectangle box = {(float)posX - 50, (float)posY, 20, 20};
        //     DrawRectangleLines((int)box.x, (int)box.y, (int)box.width, (int)box.height, BLACK);


        //     if(CheckCollisionPointRec(GetMousePosition(), box)){
        //         if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        //             tasks[i].completed = !tasks[i].completed;
                    
        //         }
        //     }

        //     if (tasks[i].completed) {
        //         DrawText("X", (int)box.x + 4, (int)box.y, 20, BLACK);
        //         int textWidth = MeasureText(tasks[i].taskDescription.c_str(), tasks[i].fontSize);
        //         int lineY = posY + tasks[i].fontSize / 2;

        //         DrawLine(posX, lineY, posX + textWidth, lineY, BLACK);
        //     }
        //     posY += 50;
        // }

        taskManager.DrawTaskPanel();
        taskManager.DrawTasks();

        taskManager.UpdateScroll();


        // float wheel = GetMouseWheelMove();
        // if (wheel != 0) {
        //     std::cout << wheel << "\n";
        // }


        EndDrawing();
    }

    CloseWindow();
    // =======================

    return 0;
}