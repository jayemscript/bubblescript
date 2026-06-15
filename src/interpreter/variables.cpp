#include "interpreter.h"

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static bool isNumber(const std::string& s)
{
    if (s.empty())
        return false;

    bool hasDot = false;
    size_t start = (s[0] == '-') ? 1 : 0; // allow negative numbers

    if (start == s.size())
        return false;

    for (size_t i = start; i < s.size(); ++i)
    {
        if (s[i] == '.')
        {
            if (hasDot) return false; // two dots → not a number
            hasDot = true;
        }
        else if (!std::isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

// ---------------------------------------------------------------------------
// parseBubble
//
// Handles:
//   bubble name = "Jay"
//   bubble age = 25
//   const bubble pi = 3.14
// ---------------------------------------------------------------------------

void Interpreter::parseBubble(const std::string& line, bool isConst)
{
    // strip keyword prefix
    // "const bubble " = 13, "bubble " = 7
    std::string rest = line.substr(isConst ? 13 : 7);

    // find '='
    size_t eq = rest.find('=');

    if (eq == std::string::npos)
    {
        std::cerr << "Syntax error: missing '=' in declaration: " << line << "\n";
        return;
    }

    // extract name (trim trailing space)
    std::string name = rest.substr(0, eq);
    while (!name.empty() && name.back() == ' ')
        name.pop_back();

    // extract value (trim leading space)
    std::string value = rest.substr(eq + 1);
    while (!value.empty() && value.front() == ' ')
        value.erase(value.begin());

    // detect type
    VarType type;

    if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
    {
        // string: strip quotes
        value = value.substr(1, value.size() - 2);
        type  = VarType::String;
    }
    else if (isNumber(value))
    {
        // number: keep value as-is (stored as string internally)
        type = VarType::Number;
    }
    else
    {
        std::cerr << "Type error: unknown value type for '" << name << "': " << value << "\n";
        return;
    }

    // guard: const cannot be reassigned
    if (variables.count(name))
    {
        if (variables[name].isConst)
        {
            std::cerr << "Error: cannot reassign const '" << name << "'\n";
            return;
        }

        // guard: type cannot change on reassignment
        if (variables[name].type != type)
        {
            std::cerr << "Type error: cannot assign "
                      << (type == VarType::String ? "string" : "number")
                      << " to "
                      << (variables[name].type == VarType::String ? "string" : "number")
                      << " variable '" << name << "'\n";
            return;
        }
    }

    variables[name] = { value, type, isConst };
}

// ---------------------------------------------------------------------------
// interpolate
//
// Replaces {name} in a string with the variable's value.
// Unknown variables are left as-is.
// ---------------------------------------------------------------------------

std::string Interpreter::interpolate(const std::string& input)
{
    std::string out;
    out.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (input[i] != '{')
        {
            out += input[i];
            continue;
        }

        size_t close = input.find('}', i + 1);

        if (close == std::string::npos)
        {
            out += input[i];
            continue;
        }

        std::string varName = input.substr(i + 1, close - i - 1);

        if (variables.count(varName))
            out += variables[varName].value;
        else
            out += input.substr(i, close - i + 1); // keep {unknown} as-is

        i = close;
    }

    return out;
}