#pragma once

#include <string>
#include <vector>

namespace ht
{
    void startword(const std::vector<std::wstring>& lines, int count, const std::string &layout);
    void startshort(const std::vector<std::wstring>& lines, int count, const std::string &layout);
    void startlong(const std::vector<std::wstring>& lines, const std::string &layout);
}