#pragma once
#include <string>
#include <vector>
namespace util
{
    struct PointColor
    {
        int x;
        int y;
        int color;
    };

    std::vector<std::string> split(std::string str, char del);
};