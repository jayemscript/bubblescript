#include "interpreter.h"

#include <fstream>
#include <iostream>
#include <string>

// Helpers

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
            default:   out += input[i]; break; // unknown escape — keep as-is
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

// Interpreter

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

        if (line.rfind("say ", 0) != 0)
            continue;

        std::string text = line.substr(4); // text after "say "

        // Single-line string:  say "hello\nworld"
        if (text.size() >= 2 && text.front() == '"' && text.back() == '"')
        {
            std::string content = text.substr(1, text.size() - 2);
            std::cout << parseEscapes(content) << "\n";
            continue;
        }

        // Multi-line string:
        //   say "line one
        //   line two"
        if (!text.empty() && text.front() == '"')
        {
            std::string buffer = text.substr(1); // drop opening quote

            while (std::getline(file, line))
            {
                // A line ending with '"' closes the block
                if (!line.empty() && line.back() == '"')
                {
                    buffer += "\n" + line.substr(0, line.size() - 1); // drop closing quote
                    break;
                }

                buffer += "\n" + line;
            }

            std::cout << parseEscapes(buffer) << "\n";
        }
    }
}