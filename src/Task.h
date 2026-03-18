#pragma once
#include <string>
#include <raylib.h>

struct Task{
    const std::string taskDescription;
    bool completed = false;
    Color color = BLACK;
    int fontSize = 20;
    int taskHeight = 60;
};