#include "interpreter.h"

#include <fstream>
#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

static std::string parseEscapes(const std::string& input)
{
    std::string out;
    out.reserve(input.size());

    for (size_t i = 0; i < input.size(); ++i)
    {
        if (input[i] != '\\' || i + 1 >= input.size())
        {
            out += input[i];
            continue;
        }

        switch (input[++i])
        {
            case 'n':  out += '\n'; break;
            case 't':  out += '\t'; break;
            case '\\': out += '\\'; break;
            case '"':  out += '"';  break;
            default:   out += input[i]; break;
        }
    }

    return out;
}

static std::string trimLeft(const std::string& s)
{
    size_t start = s.find_first_not_of(' ');
    return (start == std::string::npos) ? "" : s.substr(start);
}

static bool isBlankOrComment(const std::string& line)
{
    return line.empty() || line.rfind("//", 0) == 0;
}

// ---------------------------------------------------------------------------
// Interpreter
// ---------------------------------------------------------------------------

void Interpreter::executeFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << path << "\n";
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        line = trimLeft(line);

        if (isBlankOrComment(line))
            continue;

        // -----------------------------------------------------------------
        // const bubble name = "value" // immutable
        // -----------------------------------------------------------------
        if (line.rfind("const bubble ", 0) == 0)
        {
            parseBubble(line, true);
            continue;
        }

        // -----------------------------------------------------------------
        // bubble name = "value"
        // -----------------------------------------------------------------
        if (line.rfind("bubble ", 0) == 0)
        {
            parseBubble(line, false);
            continue;
        }

        // -----------------------------------------------------------------
        // say "..."
        // -----------------------------------------------------------------
        if (line.rfind("say ", 0) != 0)
            continue;

        std::string text = line.substr(4);

        // Single-line string
        if (text.size() >= 2 && text.front() == '"' && text.back() == '"')
        {
            std::string content = text.substr(1, text.size() - 2);
            std::cout << parseEscapes(interpolate(content)) << "\n";
            continue;
        }

        // Multi-line string
        if (!text.empty() && text.front() == '"')
        {
            std::string buffer = text.substr(1);

            while (std::getline(file, line))
            {
                if (!line.empty() && line.back() == '"')
                {
                    buffer += "\n" + line.substr(0, line.size() - 1);
                    break;
                }

                buffer += "\n" + line;
            }

            std::cout << parseEscapes(interpolate(buffer)) << "\n";
        }
    }
}