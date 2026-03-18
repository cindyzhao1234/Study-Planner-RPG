#include "TaskManager.h"
#include <iostream>
#include <sstream>



void TaskManager::InitTaskPanel(){
    panelX = 40;
    panelY = 40;
    panelWidth = 300;
    panelHeight = 300;
    headerHeight = 60;
    padding = 10; 

    checkboxWidth = 20;
    checkboxHeight = 20;

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
    DrawText("To Do List:", panelX + 20, panelY + 20, 20, BLACK);
    DrawRectangleLines((float)panelX, (float)panelY, (float)panelWidth, (float)headerHeight, MAROON);

    taskAreaX = panelX + padding;
    taskAreaY = panelY + headerHeight + padding;
    taskAreaWidth = panelWidth - 2 * padding;
    taskAreaHeight = panelHeight - headerHeight - 2 *padding;

    Rectangle taskArea = {taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight};
    DrawRectangleLines(taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight, BLUE);
}

void TaskManager::DrawTasks() {
    BeginScissorMode((int)taskAreaX, (int)taskAreaY, (int)taskAreaWidth, (int)taskAreaHeight);

    float currentY = taskAreaY - scrollOffset;

    for(int i = 0; i < taskList.size(); i++){
        int fontSize = 20;
        int maxWidth = (int)taskAreaWidth - 40;   // leave space for checkbox + gap
        int lineHeight = fontSize + 4;

        std::vector<std::string> wrappedText = WrapText(taskList[i].taskDescription, maxWidth, fontSize);

        // work out task height based on number of wrapped lines
        float textHeight = wrappedText.size() * lineHeight;
        float taskHeight = std::max(textHeight + 20.0f, checkboxHeight + 20.0f);

        if(currentY + taskHeight > taskAreaY + taskAreaHeight){
            break;
        }

        DrawRectangleLines((int)taskAreaX, (int)currentY, (int)taskAreaWidth, (int)taskHeight, GREEN);

        Rectangle checkbox = {taskAreaX, currentY + 10, checkboxWidth, checkboxHeight};
        DrawRectangleLines((int)checkbox.x, (int)checkbox.y, (int)checkbox.width, (int)checkbox.height, PURPLE);

        if(taskList[i].completed){
            DrawText("X", (int)checkbox.x + 4, (int)checkbox.y - 2, 20, BLACK);
        }

        int textX = (int)(taskAreaX + 30);
        int textY = (int)(currentY + 10);

        for(int j = 0; j < wrappedText.size(); j++){
            DrawText(wrappedText[j].c_str(), textX, textY + j * lineHeight, fontSize, BLACK);
        }

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

void TaskManager::UpdateTaskToggle(){
    float currentY = taskAreaY - scrollOffset;
    
    for (int i = 0; i < taskList.size(); i++) {
        
        float taskHeight = taskList[i].taskHeight;

        if (currentY + taskHeight > taskAreaY + taskAreaHeight) {
            break;
        }

        Rectangle checkbox = {taskAreaX, currentY + 10, checkboxWidth, checkboxHeight};

        if(CheckCollisionPointRec(GetMousePosition(), checkbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            taskList[i].completed = !taskList[i].completed;
            std::cout << "Task checkbox clicked";
    
        }

        currentY += taskHeight + padding;
    }
}

std::vector<std::string> TaskManager::WrapText(const std::string& text, int maxWidth, int fontSize){
    //split text into words
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;
    
    while (std::getline(ss, word, ' ')) {
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    std::vector<std::string> finishedLines;
    std::string currentLine = "";
    
    for(int i = 0; i < words.size(); i++){
        std::string testLine;
        if(currentLine.empty()){
            testLine = words[i];
        } else{
            testLine = currentLine + " " + words[i];
        }
        
        if(MeasureText(testLine.c_str(), fontSize) > maxWidth){
            if(!currentLine.empty()){
                finishedLines.push_back(currentLine);
            }
            currentLine = words[i];
        } else{
            currentLine = testLine;
        }
        
    }
    //if at the end current line still stores smth, push into finishedLines
    if(currentLine != ""){
        finishedLines.push_back(currentLine);
    }

    return finishedLines;
}