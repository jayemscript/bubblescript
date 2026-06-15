#include "interpreter.h"

#include <fstream>
#include <iostream>
#include <string>

void Interpreter::executeFile(const std::string& path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << path << std::endl;
        return;
    }

    std::string line;

    while (std::getline(file, line))
    {
        // trim leading spaces
        while (!line.empty() && line[0] == ' ')
            line.erase(0, 1);

        if (line.rfind("say ", 0) != 0)
            continue;

        std::string text = line.substr(4);

        // -----------------------------
        // SINGLE LINE CASE
        // -----------------------------
        if (!text.empty() &&
            text.front() == '"' &&
            text.back() == '"')
        {
            text = text.substr(1, text.size() - 2);
            std::cout << text << std::endl;
            continue;
        }

        // -----------------------------
        // MULTI-LINE CASE
        // -----------------------------
        if (!text.empty() && text.front() == '"')
        {
            std::string buffer = text.substr(1); // remove first quote
            buffer += "\n";

            while (std::getline(file, line))
            {
                buffer += line + "\n";

                // check if this line ends the string
                if (!line.empty() && line.find('"') != std::string::npos)
                {
                    // remove trailing quote safely
                    if (!buffer.empty() && buffer.back() == '\n')
                        buffer.pop_back();

                    size_t endQuote = buffer.find_last_of('"');
                    if (endQuote != std::string::npos)
                        buffer = buffer.substr(0, endQuote);

                    std::cout << buffer << std::endl;
                    break;
                }
            }
        }
    }
}