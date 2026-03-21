#include "TaskManager.h"
#include <sstream>
#include <algorithm>
#include <iostream>

namespace {
    constexpr int HEADER_FONT_SIZE = 20;
    constexpr int INPUT_FONT_SIZE = 16;
    constexpr int INPUT_LINE_SPACING = 4;
    constexpr int TASK_LINE_SPACING = 4;
    constexpr float INPUT_BOX_HEIGHT = 60.0f;
    constexpr float ADD_BUTTON_SIZE = 20.0f;
    constexpr float SCROLL_SPEED = 20.0f;
    constexpr float TEXT_LEFT_OFFSET = 30.0f;
    constexpr float INNER_TOP_PADDING = 10.0f;
    constexpr float DELETE_BUTTON_EXTRA_OFFSET = 40.0f;
}

float TaskManager::GetTaskHeight(const Task& task){
    int fontSize = task.fontSize;
    int lineHeight = fontSize + TASK_LINE_SPACING;
    int maxWidth = (int)taskAreaWidth - 80;

    std::vector<std::string> wrappedText = WrapText(task.taskDescription, maxWidth, fontSize);
    float textHeight = wrappedText.size() * lineHeight;

    return std::max(textHeight + 20.0f, checkboxHeight + 20.0f);
}

Rectangle TaskManager::GetTaskCheckboxRect(float currentY){
    return Rectangle{taskAreaX, currentY + INNER_TOP_PADDING, checkboxWidth, checkboxHeight};
}

Rectangle TaskManager::GetTaskDeleteRect(float currentY, int maxWidth){
    return Rectangle{
        taskAreaX + maxWidth + DELETE_BUTTON_EXTRA_OFFSET,
        currentY + INNER_TOP_PADDING,
        checkboxWidth,
        checkboxHeight
    };
}

int TaskManager::GetCoinCount(User& user){
    return user.CoinCount;
}

// ---------- Setup ----------

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
    scrollEnabled = false;
    isTypingTask = false;
    currentInput = "";
}

// ---------- Panel / layout ----------

void TaskManager::DrawTaskPanel(){
    float heightNeeded = HeightNeeded();
    scrollEnabled = (heightNeeded > panelHeight);

    if(scrollEnabled){
        heightNeeded = panelHeight;
    }

    Rectangle box = {(float)panelX, (float)panelY, (float)panelWidth, (float)heightNeeded};
    DrawRectangleLines((int)box.x, (int)box.y, (int)box.width, (int)box.height, BLACK);

    Rectangle header = {(float)panelX, (float)panelY, (float)panelWidth, (float)headerHeight};
    DrawRectangleLines((int)header.x, (int)header.y, (int)header.width, (int)header.height, MAROON);
    DrawText("To Do List:", panelX + 20, panelY + 20, HEADER_FONT_SIZE, BLACK);

    float panelRight = (float)panelX + (float)panelWidth;
    addButton = {panelRight - 50, panelY + 20, ADD_BUTTON_SIZE, ADD_BUTTON_SIZE};
    DrawRectangleLines((int)addButton.x, (int)addButton.y, (int)addButton.width, (int)addButton.height, RED);
    DrawText("+", (int)addButton.x + 5, (int)addButton.y, HEADER_FONT_SIZE, BLACK);

    float contentStartY = panelY + headerHeight + padding;
    float inputAreaHeight = isTypingTask ? INPUT_BOX_HEIGHT : 0.0f;

    if(isTypingTask){
        float inputAreaX = panelX + padding;
        float inputAreaY = contentStartY;
        float inputAreaWidth = panelWidth - 2 * padding;


        Rectangle inputArea = {inputAreaX, inputAreaY, inputAreaWidth, inputAreaHeight};
        DrawRectangleLines((int)inputArea.x, (int)inputArea.y, (int)inputArea.width, (int)inputArea.height, GREEN);

        std::vector<std::string> wrappedText = WrapText(currentInput, (int)inputArea.width - 20, INPUT_FONT_SIZE);
        int lineHeight = INPUT_FONT_SIZE + INPUT_LINE_SPACING;

        for(int i = 0; i < (int)wrappedText.size(); i++){
            DrawText(
                wrappedText[i].c_str(),
                (int)inputAreaX + 10,
                (int)inputAreaY + 10 + i * lineHeight,
                INPUT_FONT_SIZE,
                BLACK
            );
        }
    }

    taskAreaX = panelX + padding;
    taskAreaY = contentStartY + inputAreaHeight + (isTypingTask ? padding : 0);
    taskAreaWidth = panelWidth - 2 * padding;
    taskAreaHeight = heightNeeded - headerHeight - 2 * padding - inputAreaHeight - (isTypingTask ? padding : 0);

    if(taskAreaHeight < 0){
        taskAreaHeight = 0;
    }

    Rectangle taskArea = {taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight};
    DrawRectangleLines((int)taskArea.x, (int)taskArea.y, (int)taskArea.width, (int)taskArea.height, BLUE);
}

// ---------- Drawing tasks ----------

void TaskManager::DrawTasks(){
    BeginScissorMode((int)taskAreaX, (int)taskAreaY, (int)taskAreaWidth, (int)taskAreaHeight);

    float currentY = taskAreaY - scrollOffset;

    for(int i = 0; i < (int)taskList.size(); i++){
        int fontSize = taskList[i].fontSize;
        int maxWidth = (int)taskAreaWidth - 80;
        int lineHeight = fontSize + TASK_LINE_SPACING;

        std::vector<std::string> wrappedText = WrapText(taskList[i].taskDescription, maxWidth, fontSize);
        float taskHeight = GetTaskHeight(taskList[i]);

        if(currentY + taskHeight > taskAreaY + taskAreaHeight){
            break;
        }

        DrawRectangleLines((int)taskAreaX, (int)currentY, (int)taskAreaWidth, (int)taskHeight, GREEN);

        Rectangle checkbox = GetTaskCheckboxRect(currentY);
        DrawRectangleLines((int)checkbox.x, (int)checkbox.y, (int)checkbox.width, (int)checkbox.height, PURPLE);

        taskList[i].deleteTask = GetTaskDeleteRect(currentY, maxWidth);
        DrawRectangleLines(
            (int)taskList[i].deleteTask.x,
            (int)taskList[i].deleteTask.y,
            (int)taskList[i].deleteTask.width,
            (int)taskList[i].deleteTask.height,
            PURPLE
        );

        if(taskList[i].completed){
            DrawText("X", (int)checkbox.x + 4, (int)checkbox.y - 2, HEADER_FONT_SIZE, BLACK);
        }

        int textX = (int)(taskAreaX + TEXT_LEFT_OFFSET);
        int textY = (int)(currentY + INNER_TOP_PADDING);

        for(int j = 0; j < (int)wrappedText.size(); j++){
            DrawText(wrappedText[j].c_str(), textX, textY + j * lineHeight, fontSize, BLACK);

            if (taskList[i].completed) {
                int lineWidth = MeasureText(wrappedText[j].c_str(), fontSize);
                int strikeY = textY + j * lineHeight + fontSize / 2;
                DrawLine(textX, strikeY, textX + lineWidth, strikeY, BLACK);
            }
        }

        currentY += taskHeight + padding;
    }

    EndScissorMode();
}

// ---------- Buttons / input ----------

void TaskManager::UpdateAddButton(){
    if(CheckCollisionPointRec(GetMousePosition(), addButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isTypingTask = true;
        currentInput = "";
    }

    if(!CheckCollisionPointRec(GetMousePosition(), addButton) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        isTypingTask = false;
    }
}

void TaskManager::UpdateTaskInput(){
    if(!isTypingTask){
        return;
    }

    int key = GetCharPressed();
    while(key > 0){
        if(key >= 32 && key <= 125){
            currentInput += (char)key;
        }
        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE) && !currentInput.empty()){
        currentInput.pop_back();
    }

    if(IsKeyPressed(KEY_ENTER) && !currentInput.empty()){
        AddTask({currentInput, false});
        currentInput = "";
        isTypingTask = false;
    }
}

// ---------- Task data ----------

void TaskManager::AddTask(const Task& task){
    taskList.push_back(task);
}

float TaskManager::TotalTaskHeight(){
    float totalHeight = 0;

    for(int i = 0; i < (int)taskList.size(); i++){
        totalHeight += GetTaskHeight(taskList[i]) + padding;
    }

    return totalHeight;
}

float TaskManager::HeightNeeded(){
    float inputAreaHeight;

    if(isTypingTask){
        inputAreaHeight = INPUT_BOX_HEIGHT + padding;
    } else{
        inputAreaHeight = 0.0f;
    }

    return headerHeight + TotalTaskHeight() + padding + inputAreaHeight;
}

// ---------- Scrolling ----------

void TaskManager::UpdateScroll(){
    Rectangle taskArea = {taskAreaX, taskAreaY, taskAreaWidth, taskAreaHeight};

    if(CheckCollisionPointRec(GetMousePosition(), taskArea)){
        float wheel = GetMouseWheelMove();

        if(wheel != 0){
            scrollOffset -= wheel * SCROLL_SPEED;
        }

        if(scrollOffset < 0){
            scrollOffset = 0;
        }

        float maxScroll = TotalTaskHeight() - taskAreaHeight;
        if(maxScroll < 0){
            maxScroll = 0;
        }

        if(scrollOffset > maxScroll){
            scrollOffset = maxScroll;
        }
    }
}

// ---------- Checkbox toggle ----------

void TaskManager::UpdateTaskToggle(User& user){
    float currentY = taskAreaY - scrollOffset;

    for(int i = 0; i < (int)taskList.size(); i++){
        float taskHeight = GetTaskHeight(taskList[i]);

        if(currentY + taskHeight > taskAreaY + taskAreaHeight){
            break;
        }

        Rectangle checkbox = GetTaskCheckboxRect(currentY);

        if(CheckCollisionPointRec(GetMousePosition(), checkbox) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            taskList[i].completed = true;
            user.CoinCount ++;
            std::cout << "User Coin Coint: "<< user.CoinCount << "\n";
            std::cout << "Task checkbox clicked\n";
        }

        currentY += taskHeight + padding;
    }
}

// ---------- Text wrapping ----------

std::vector<std::string> TaskManager::WrapText(const std::string& text, int maxWidth, int fontSize){
    std::vector<std::string> words;
    std::stringstream ss(text);
    std::string word;

    while(std::getline(ss, word, ' ')){
        if(!word.empty()) {
            words.push_back(word);
        }
    }

    std::vector<std::string> finishedLines;
    std::string currentLine = "";

    for(int i = 0; i < (int)words.size(); i++){
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

    if(!currentLine.empty()){
        finishedLines.push_back(currentLine);
    }

    return finishedLines;
}

// ---------- Delete task ----------

void TaskManager::DeleteTask(){
    for(int i = 0; i < (int)taskList.size(); i++){
        if(taskList[i].completed == true){
            taskList.erase(taskList.begin() + i);
            break;
        }
        if (CheckCollisionPointRec(GetMousePosition(), taskList[i].deleteTask) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            taskList.erase(taskList.begin() + i);
            break; 
        }
    }
}
