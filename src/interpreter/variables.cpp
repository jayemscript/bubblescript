#include "interpreter.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static bool isNumber(const std::string& s)
{
    if (s.empty())
        return false;

    bool hasDot = false;
    size_t start = (s[0] == '-') ? 1 : 0;

    if (start == s.size())
        return false;

    for (size_t i = start; i < s.size(); ++i)
    {
        if (s[i] == '.')
        {
            if (hasDot) return false;
            hasDot = true;
        }
        else if (!std::isdigit(s[i]))
        {
            return false;
        }
    }

    return true;
}

static bool isBoolean(const std::string& s)
{
    return s == "true" || s == "false";
}

static std::string trimSpace(const std::string& s)
{
    size_t start = s.find_first_not_of(' ');
    size_t end   = s.find_last_not_of(' ');
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// ---------------------------------------------------------------------------
// evaluate
//
// Parses and computes a simple arithmetic expression:
//   "9 + 3"   → "12"
//   "10 / 3"  → "3.33333"
//   "10 % 3"  → "1"    
// ---------------------------------------------------------------------------

static std::string evaluate(const std::string& expr)
{
    // find operator (scan left to right, skip leading minus for negative numbers)
    const std::string ops = "+-*/%";
    size_t opPos = std::string::npos;
    char   op    = 0;

    for (size_t i = 1; i < expr.size(); ++i)
    {
        if (ops.find(expr[i]) != std::string::npos)
        {
            // skip minus that belongs to a negative number (e.g. "5 + -3")
            if (expr[i] == '-' && i + 1 < expr.size() && std::isdigit(expr[i + 1]) && expr[i - 1] == ' ')
                continue;

            opPos = i;
            op    = expr[i];
            break;
        }
    }

    if (opPos == std::string::npos)
        return expr; // no operator found — return as-is

    std::string lhs = trimSpace(expr.substr(0, opPos));
    std::string rhs = trimSpace(expr.substr(opPos + 1));

    if (!isNumber(lhs) || !isNumber(rhs))
        return expr; // not a numeric expression — return as-is

    double l = std::stod(lhs);
    double r = std::stod(rhs);
    double result = 0;

    switch (op)
    {
        case '+': result = l + r; break;
        case '-': result = l - r; break;
        case '*': result = l * r; break;
        case '%': result = std::fmod(l, r); break;
        case '/':
            if (r == 0)
            {
                std::cerr << "Error: division by zero\n";
                return "0";
            }
            result = l / r;
            break;
    }

    // return integer string if result has no fractional part
    if (result == static_cast<long long>(result))
        return std::to_string(static_cast<long long>(result));

    // otherwise return float (trim trailing zeros)
    std::string s = std::to_string(result);
    s.erase(s.find_last_not_of('0') + 1);
    s.erase(s.find_last_not_of('.') + 1);
    return s;
}

// ---------------------------------------------------------------------------
// parseBubble
// ---------------------------------------------------------------------------

void Interpreter::parseBubble(const std::string& line, bool isConst)
{
    std::string rest = line.substr(isConst ? 13 : 7);

    size_t eq = rest.find('=');

    if (eq == std::string::npos)
    {
        std::cerr << "Syntax error: missing '=' in declaration: " << line << "\n";
        return;
    }

    std::string name = rest.substr(0, eq);
    while (!name.empty() && name.back() == ' ')
        name.pop_back();

    std::string value = rest.substr(eq + 1);
    while (!value.empty() && value.front() == ' ')
        value.erase(value.begin());

    // detect type
    VarType type;

    if (value.size() >= 2 && value.front() == '"' && value.back() == '"')
    {
        value = value.substr(1, value.size() - 2);
        type  = VarType::String;
    }
    else if (isBoolean(value))
    {
        type = VarType::Boolean;
    }
    else
    {
        // try evaluate as arithmetic expression first, then check if result is a number
        std::string evaluated = evaluate(value);

        if (isNumber(evaluated))
        {
            value = evaluated;
            type  = VarType::Number;
        }
        else
        {
            std::cerr << "Type error: unknown value type for '" << name << "': " << value << "\n";
            return;
        }
    }

    // guard: const cannot be reassigned
    if (variables.count(name))
    {
        if (variables[name].isConst)
        {
            std::cerr << "Error: cannot reassign const '" << name << "'\n";
            return;
        }

        if (variables[name].type != type)
        {
            std::cerr << "Type error: cannot assign "
                      << (type == VarType::String  ? "string"  :
                          type == VarType::Number  ? "number"  : "boolean")
                      << " to "
                      << (variables[name].type == VarType::String  ? "string"  :
                          variables[name].type == VarType::Number  ? "number"  : "boolean")
                      << " variable '" << name << "'\n";
            return;
        }
    }

    variables[name] = { value, type, isConst };
}

// ---------------------------------------------------------------------------
// interpolate
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
            out += input.substr(i, close - i + 1);

        i = close;
    }

    return out;
}