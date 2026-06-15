#pragma once

#include <string>
#include <unordered_map>

enum class VarType { String, Number };

struct Variable
{
    std::string value;
    VarType type;
    bool isConst;
};

class Interpreter
{
public:
    void executeFile(const std::string& path);

private:
    std::unordered_map<std::string, Variable> variables;

    void        parseBubble(const std::string& line, bool isConst);
    std::string interpolate(const std::string& input);
};