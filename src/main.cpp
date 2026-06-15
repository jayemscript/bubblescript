//src/main.cpp
#include "interpreter/interpreter.h"

#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: bubblescript <file.bubble>" << std::endl;
        return 1;
    }

    Interpreter interpreter;

    interpreter.executeFile(argv[1]);

    return 0;
}