#include <raylib.h>
#include "./src/Task.h"
#include <vector>
#include "./src/TaskManager.h"
#include <iostream>

int main(){
    TaskManager taskManager;
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

    taskManager.InitTaskPanel();


    // std::vector<Rectangle> checkboxes;
   
    while(!WindowShouldClose()){

        

        BeginDrawing();


        ClearBackground(RAYWHITE);

        taskManager.DrawTaskPanel();
        taskManager.DrawTasks();

        taskManager.UpdateScroll();
        taskManager.UpdateTaskToggle();


        EndDrawing();
    }

    CloseWindow();
    // =======================

    return 0;
}