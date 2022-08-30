#include <iostream>
#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include <string.h>
#include "taja.hpp"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    if (argc > 1)
    {
        if (strcmp(argv[1], "short") == 0)
        {
            std::ifstream file("res/short.txt");
            if (file.good())
            {
                std::vector<std::wstring> lines;
                std::string line;
                while (std::getline(file, line))
                {
                    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char a)
                                                          { return !std::isspace(a); }));
                    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char a)
                                            { return !std::isspace(a); })
                                   .base(),
                               line.end());
                    if (!line.empty())
                    {
                        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
                        lines.push_back(conv.from_bytes(line));
                    }
                }
                if (!lines.empty())
                {
                    if (argc > 2)
                    {
                        ht::startshort(lines, argv[2]);
                    }
                    else
                    {
                        ht::startshort(lines, "2");
                    }
                }
                else
                {
                    std::cerr << "No sentences in file: " << argv[2] << "." << std::endl;
                }
            }
            else
            {
                std::cerr << "File not found: " << argv[2] << "." << std::endl;
            }
        }
        else if (strcmp(argv[1], "long") == 0)
        {
            if (argc > 2)
            {
                std::ifstream file("res/long/" + std::string(argv[2]) + ".txt");
                if (file.good())
                {
                    std::vector<std::wstring> lines;
                    std::string line;
                    while (std::getline(file, line))
                    {
                        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char a)
                                                              { return !std::isspace(a); }));
                        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char a)
                                                { return !std::isspace(a); })
                                       .base(),
                                   line.end());
                        if (!line.empty())
                        {
                            std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
                            lines.push_back(conv.from_bytes(line));
                        }
                    }
                    if (!lines.empty())
                    {
                        if (argc > 3)
                        {
                            ht::startlong(lines, argv[3]);
                        }
                        else
                        {
                            ht::startlong(lines, "2");
                        }
                    }
                    else
                    {
                        std::cerr << "No sentences in file: " << argv[2] << "." << std::endl;
                    }
                }
                else
                {
                    std::cerr << "Essay not found: " << argv[2] << "." << std::endl;
                }
            }
            else
            {
                std::cerr << "Essay not specified." << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid game mode: " << argv[1] << "." << std::endl;
        }
    }
    else
    {
        std::cerr << "Game mode not specified." << std::endl;
    }
    return 0;
}