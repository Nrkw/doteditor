#include "utils.hpp"
#include <string>

    std::vector<std::string> util::split(std::string str, char del)
    {
        std::vector<std::string> res;
        std::string tmp;
        for(int i = 0; i < str.size(); i++)
        {
            if(str[i] == del)
            {
                res.push_back(tmp);
                tmp = "";
            }else
            {
                tmp += str[i];
            }
        }
        res.push_back(tmp);
        return res;
    }