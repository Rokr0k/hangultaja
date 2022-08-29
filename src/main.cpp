#include <fstream>
#include <locale>
#include <codecvt>
#include <algorithm>
#include "taja.hpp"

int main(int argc, char **argv)
{
    setlocale(LC_ALL, "");
    if (argc > 1)
    {
        std::ifstream file(argv[1]);
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
                    ht::startgame(lines, argv[2]);
                }
                else
                {
                    ht::startgame(lines, "2");
                }
            }
        }
    }
    return 0;
}