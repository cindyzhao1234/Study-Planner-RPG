#pragma once
#include "Task.h"
#include "raylib.h"
#include <vector>
#include <string>
#include "User.h"
#include "Assets.h"


class TaskManager {
public:
    void InitTaskPanel();
    void DrawTaskPanel(Assets assets);
    void DrawTasks(Assets assets);

    std::vector<std::string> WrapText(const std::string& text, int maxWidth, int fontSize);

    void AddTask(const Task& task);
    void UpdateAddButton();
    void UpdateTaskInput();
    void UpdateScroll();
    void UpdateTaskToggle(User& user);
    void DeleteTask();

    float HeightNeeded();
    float TotalTaskHeight();

    int GetCoinCount(User& user);

private:
    std::vector<Task> taskList;

    float panelX, panelY;
    float panelWidth, panelHeight;
    float headerHeight;

    float taskAreaWidth, taskAreaHeight;
    float taskAreaX, taskAreaY;

    float padding;
    float checkboxWidth, checkboxHeight;

    bool scrollEnabled = false;
    float scrollOffset = 0.0f;

    Rectangle addButton;
    bool isTypingTask = false;
    std::string currentInput;

    float GetTaskHeight(const Task& task);
    Rectangle GetTaskCheckboxRect(float currentY);
    Rectangle GetTaskDeleteRect(float currentY, int maxWidth);

    // User user;
};