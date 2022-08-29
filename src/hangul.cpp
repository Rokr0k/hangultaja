#include "hangul.hpp"
#include <string.h>

using namespace ht;

static inline std::wstring to_wstring(const std::basic_string<ucschar> &str)
{
    std::wstring res(str.begin(), str.end());
    return res;
}

HangulManager::HangulManager(const std::string &layout)
{
    hic = hangul_ic_new(layout.c_str());
}

HangulManager::~HangulManager()
{
    hangul_ic_delete(hic);
}

bool HangulManager::process(int ascii)
{
    return hangul_ic_process(hic, ascii);
}

bool HangulManager::backspace()
{
    return hangul_ic_backspace(hic);
}

bool HangulManager::empty()
{
    return hangul_ic_is_empty(hic);
}

std::wstring HangulManager::get_preedit()
{
    return to_wstring(hangul_ic_get_preedit_string(hic));
}

std::wstring HangulManager::get_commit()
{
    return to_wstring(hangul_ic_get_commit_string(hic));
}

std::wstring HangulManager::flush()
{
    return to_wstring(hangul_ic_flush(hic));
}

void HangulManager::reset()
{
    hangul_ic_reset(hic);
}