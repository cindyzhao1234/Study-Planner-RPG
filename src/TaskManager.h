#pragma once
#include "Task.h"
#include <vector>
#include <string>

class TaskManager{
    public:
        void InitTaskPanel(); //create the task manager window
        void DrawTaskPanel();
        void DrawTasks();
        void AddTask(const Task& task);
        // void addTask(std::string taskDescription); //create the task
        // void toggleComplete(Task& task); //ticks the checkbox
        // void drawCheckbox(Task& task);
        // void draw();
        float HeightNeeded();
        float TotalTaskHeight();

        void UpdateScroll();

        std::vector<Task> getTaskList();

    private:
        std::vector<Task> taskList;

        float panelX, panelY;
        float panelWidth, panelHeight;
        float headerHeight;
        float taskAreaWidth, taskAreaHeight;
        float taskAreaX, taskAreaY;
        float padding;

        bool scrollEnabled = false;
        float scrollOffset;
};