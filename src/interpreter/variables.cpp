#include "interpreter.h"

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// parseBubble
//
// Handles:
//   bubble name = "Jay"
//   const bubble name = "Jay"
// ---------------------------------------------------------------------------

void Interpreter::parseBubble(const std::string& line, bool isConst)
{
    // strip keyword prefix
    // isConst → skip "const bubble ", else skip "bubble "
    std::string rest = line.substr(isConst ? 13 : 7); // "const bubble " = 13, "bubble " = 7

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

    // extract value (trim leading space and quotes)
    std::string value = rest.substr(eq + 1);
    while (!value.empty() && value.front() == ' ')
        value.erase(value.begin());

    if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
        value = value.substr(1, value.size() - 2);

    // guard: const cannot be reassigned
    if (variables.count(name))
    {
        if (variables[name].isConst)
        {
            std::cerr << "Error: cannot reassign const '" << name << "'\n";
            return;
        }
    }

    variables[name] = { value, isConst };
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
            // no closing brace — treat as literal
            out += input[i];
            continue;
        }

        std::string varName = input.substr(i + 1, close - i - 1);

        if (variables.count(varName))
            out += variables[varName].value;
        else
            out += input.substr(i, close - i + 1); // keep {unknown} as-is

        i = close; // jump past '}'
    }

    return out;
}