#pragma once

#include <string>
#include <unordered_map>

struct Variable
{
    std::string value;
    bool isConst;
};

class Interpreter
{
public:
    void executeFile(const std::string& path);

private:
    std::unordered_map<std::string, Variable> variables;

    void parseBubble(const std::string& line, bool isConst);
    std::string interpolate(const std::string& input);
};