#pragma once

#include <hangul-1.0/hangul.h>
#include <string>

namespace ht
{
    class HangulManager
    {
    private:
        HangulInputContext *hic;

    public:
        HangulManager(const std::string &layout);
        ~HangulManager();
        bool process(int ascii);
        bool backspace();
        bool empty();
        std::wstring get_preedit();
        std::wstring get_commit();
        std::wstring flush();
        void reset();
    };
}