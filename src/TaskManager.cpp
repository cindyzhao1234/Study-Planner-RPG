#include "TaskManager.h"
#include <iostream>


void TaskManager::InitTaskPanel(){
    panelX = 40;
    panelY = 40;
    panelWidth = 300;
    panelHeight = 300;
    headerHeight = 60;
    padding = 10; 

    scrollOffset = 0;
}

void TaskManager::DrawTaskPanel(){
    float heightNeeded = HeightNeeded();
    if(heightNeeded > panelHeight){
        scrollEnabled = true;
        heightNeeded = panelHeight;

    }

    Rectangle box = {(float)panelX, (float)panelY, (float)panelWidth, (float)heightNeeded};
    DrawRectangleLines((float)panelX, (float)panelY, (float)panelWidth, (float)heightNeeded, BLACK);

    Rectangle header = {(float)panelX, (float)panelY, (float)panelWidth, (float)headerHeight};
    DrawRectangleLines((float)panelX, (float)panelY, (float)panelWidth, (float)headerHeight, MAROON);

    taskAreaX = panelX + padding;
    taskAreaY = panelY + headerHeight + padding;
    taskAreaWidth = panelWidth - 2 * padding;
    taskAreaHeight = panelHeight - headerHeight - 2 *padding;

    Rectangle taskArea = {taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight};
    DrawRectangleLines(taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight, BLUE);
}

void TaskManager::DrawTasks(){
    BeginScissorMode((int)taskAreaX, (int)taskAreaY, (int)taskAreaWidth, (int)taskAreaHeight);
    float currentY = taskAreaY - scrollOffset;
    // float spacing = 10;

    for (int i = 0; i < taskList.size(); i++) {
        float taskHeight = taskList[i].taskHeight;

        if (currentY + taskHeight > taskAreaY + taskAreaHeight) {
            break;
        }

        DrawRectangleLines((int)taskAreaX, (int)currentY, (int)taskAreaWidth, (int)taskHeight, GREEN);
        DrawText(taskList[i].taskDescription.c_str(), (int)(taskAreaX + 10), (int)(currentY + 10), 20, BLACK);

        currentY += taskHeight + padding;
    }
    EndScissorMode();
}

void TaskManager::AddTask(const Task& task) {
    taskList.push_back(task);
}

float TaskManager::HeightNeeded(){
    float heightNeeded = headerHeight + TotalTaskHeight() + padding;
    
    return heightNeeded;

}

float TaskManager::TotalTaskHeight(){
    float totalHeight = 0;
    for(int i = 0; i < taskList.size(); i++){
        totalHeight += taskList[i].taskHeight + padding;
    }
    return totalHeight;
}

void TaskManager::UpdateScroll() {
    Rectangle taskArea = {taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight};

    if (CheckCollisionPointRec(GetMousePosition(), taskArea)) {
        float wheel = GetMouseWheelMove();

        if (wheel != 0) {
            scrollOffset -= wheel * 20;
        }

        if (scrollOffset < 0) {
            scrollOffset = 0;
        }
        float maxScroll = TotalTaskHeight() - taskAreaHeight;
        if (maxScroll < 0) {
            maxScroll = 0;
        }

        if (scrollOffset > maxScroll) {
            scrollOffset = maxScroll;
        }
    }
}

