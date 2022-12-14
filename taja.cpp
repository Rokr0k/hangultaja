#include "taja.hpp"
#include "hangul.hpp"
#include <iostream>
#include <random>
#include <ncurses.h>

static void init()
{
    printf("\033[?1049h");
    fflush(stdout);
    initscr();
    savetty();
    keypad(stdscr, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_BLUE);
}

static void end()
{
    curs_set(1);
    resetty();
    endwin();
    printf("\033[?1049l");
    fflush(stdout);
}

void ht::startword(const std::vector<std::wstring> &words, int count, const std::string &layout)
{
    init();
    HangulManager m(layout);
    std::wstring prevline;
    std::wstring line;
    size_t lineCount;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, words.size() - 1);
    size_t lineIndex[3] = {words.size(), dis(gen), dis(gen)};
    bool quit = false;
    while (lineCount < count && !quit)
    {
        erase();
        if (lineIndex[0] < words.size())
        {
            attron(COLOR_PAIR(1));
            mvaddwstr(0, 0, words[lineIndex[0]].c_str());
            attroff(COLOR_PAIR(1));
            move(1, 0);
            for (size_t i = 0; i < std::max(prevline.length(), words[lineIndex[0]].length()); i++)
            {
                int pair;
                if (i < prevline.length() && i < words[lineIndex[0]].length() && prevline[i] == words[lineIndex[0]][i])
                {
                    pair = 2;
                }
                else
                {
                    pair = 3;
                }
                attron(COLOR_PAIR(pair));
                if (i < prevline.length())
                {
                    addwstr(prevline.substr(i, 1).c_str());
                }
                else
                {
                    addwstr(L" ");
                }
                attroff(COLOR_PAIR(pair));
            }
        }
        attron(COLOR_PAIR(1));
        mvaddwstr(2, 0, words[lineIndex[1]].c_str());
        attroff(COLOR_PAIR(1));
        move(3, 0);
        for (size_t i = 0; i < line.length(); i++)
        {
            int pair;
            if (line[i] == words[lineIndex[1]][i])
            {
                pair = 2;
            }
            else
            {
                pair = 3;
            }
            attron(COLOR_PAIR(pair));
            addwstr(line.substr(i, 1).c_str());
            attroff(COLOR_PAIR(pair));
        }
        attron(COLOR_PAIR(4));
        if (m.empty())
        {
            addwstr(L" ");
        }
        else
        {
            addwstr(m.get_preedit().c_str());
        }
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(1));
        mvaddwstr(4, 0, words[lineIndex[2]].c_str());
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
        mvaddstr(5, 0, (std::to_string(lineCount + 1) + "/" + std::to_string(count)).c_str());
        attroff(COLOR_PAIR(2));
        refresh();
        int ch = getch();
        switch (ch)
        {
        case KEY_END:
            quit = true;
            break;
        case KEY_BACKSPACE:
            if (!m.backspace() && !line.empty())
            {
                line.erase(line.end() - 1);
            }
            break;
        case KEY_ENTER:
        case '\n':
        case ' ':
            prevline = line + m.flush();
            line.clear();
            m.reset();
            lineIndex[0] = lineIndex[1];
            lineIndex[1] = lineIndex[2];
            if (++lineCount + 1 < count)
            {
                lineIndex[2] = dis(gen);
            }
            else
            {
                lineIndex[2] = words.size();
            }
            break;
        default:
            if (m.process(ch))
            {
                std::wstring commit = m.get_commit();
                if (!commit.empty())
                {
                    line += commit;
                }
            }
            break;
        }
    }
    end();
}

void ht::startshort(const std::vector<std::wstring> &lines, int count, const std::string &layout)
{
    init();
    HangulManager m(layout);
    std::wstring prevline;
    std::wstring line;
    size_t lineCount;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dis(0, lines.size() - 1);
    size_t lineIndex[3] = {lines.size(), dis(gen), dis(gen)};
    bool quit = false;
    while (lineCount < count && !quit)
    {
        erase();
        if (lineIndex[0] < lines.size())
        {
            attron(COLOR_PAIR(1));
            mvaddwstr(0, 0, lines[lineIndex[0]].c_str());
            attroff(COLOR_PAIR(1));
            move(1, 0);
            for (size_t i = 0; i < std::max(prevline.length(), lines[lineIndex[0]].length()); i++)
            {
                int pair;
                if (i < prevline.length() && i < lines[lineIndex[0]].length() && prevline[i] == lines[lineIndex[0]][i])
                {
                    pair = 2;
                }
                else
                {
                    pair = 3;
                }
                attron(COLOR_PAIR(pair));
                if (i < prevline.length())
                {
                    addwstr(prevline.substr(i, 1).c_str());
                }
                else
                {
                    addwstr(L" ");
                }
                attroff(COLOR_PAIR(pair));
            }
        }
        attron(COLOR_PAIR(1));
        mvaddwstr(2, 0, lines[lineIndex[1]].c_str());
        attroff(COLOR_PAIR(1));
        move(3, 0);
        for (size_t i = 0; i < line.length(); i++)
        {
            int pair;
            if (line[i] == lines[lineIndex[1]][i])
            {
                pair = 2;
            }
            else
            {
                pair = 3;
            }
            attron(COLOR_PAIR(pair));
            addwstr(line.substr(i, 1).c_str());
            attroff(COLOR_PAIR(pair));
        }
        attron(COLOR_PAIR(4));
        if (m.empty())
        {
            addwstr(L" ");
        }
        else
        {
            addwstr(m.get_preedit().c_str());
        }
        attroff(COLOR_PAIR(4));
        attron(COLOR_PAIR(1));
        mvaddwstr(4, 0, lines[lineIndex[2]].c_str());
        attroff(COLOR_PAIR(1));
        attron(COLOR_PAIR(2));
        mvaddstr(5, 0, (std::to_string(lineCount + 1) + "/" + std::to_string(count)).c_str());
        attroff(COLOR_PAIR(2));
        refresh();
        int ch = getch();
        switch (ch)
        {
        case KEY_END:
            quit = true;
            break;
        case KEY_BACKSPACE:
            if (!m.backspace() && !line.empty())
            {
                line.erase(line.end() - 1);
            }
            break;
        case KEY_ENTER:
        case '\n':
            prevline = line + m.flush();
            line.clear();
            m.reset();
            lineIndex[0] = lineIndex[1];
            lineIndex[1] = lineIndex[2];
            if (++lineCount + 1 < count)
            {
                lineIndex[2] = dis(gen);
            }
            else
            {
                lineIndex[2] = lines.size();
            }
            break;
        case ' ':
            line += m.flush() + L" ";
            break;
        default:
            if (m.process(ch))
            {
                std::wstring commit = m.get_commit();
                if (!commit.empty())
                {
                    line += commit;
                }
            }
            break;
        }
    }
    end();
}

void ht::startlong(const std::vector<std::wstring> &lines, const std::string &layout)
{
    init();
    HangulManager m(layout);
    std::wstring prevline;
    std::wstring line;
    size_t lineIndex = 0;
    bool quit = false;
    while (lineIndex < lines.size() && !quit)
    {
        erase();
        if (lineIndex > 0)
        {
            attron(COLOR_PAIR(1));
            mvaddwstr(0, 0, lines[lineIndex - 1].c_str());
            attroff(COLOR_PAIR(1));
            move(1, 0);
            for (size_t i = 0; i < std::max(prevline.length(), lines[lineIndex - 1].length()); i++)
            {
                int pair;
                if (i < prevline.length() && i < lines[lineIndex - 1].length() && prevline[i] == lines[lineIndex - 1][i])
                {
                    pair = 2;
                }
                else
                {
                    pair = 3;
                }
                attron(COLOR_PAIR(pair));
                if (i < prevline.length())
                {
                    addwstr(prevline.substr(i, 1).c_str());
                }
                else
                {
                    addwstr(L" ");
                }
                attroff(COLOR_PAIR(pair));
            }
        }
        attron(COLOR_PAIR(1));
        mvaddwstr(2, 0, lines[lineIndex].c_str());
        attroff(COLOR_PAIR(1));
        move(3, 0);
        for (size_t i = 0; i < line.length(); i++)
        {
            int pair;
            if (line[i] == lines[lineIndex][i])
            {
                pair = 2;
            }
            else
            {
                pair = 3;
            }
            attron(COLOR_PAIR(pair));
            addwstr(line.substr(i, 1).c_str());
            attroff(COLOR_PAIR(pair));
        }
        attron(COLOR_PAIR(4));
        if (m.empty())
        {
            addwstr(L" ");
        }
        else
        {
            addwstr(m.get_preedit().c_str());
        }
        attroff(COLOR_PAIR(4));
        if (lineIndex + 1 < lines.size())
        {
            attron(COLOR_PAIR(1));
            mvaddwstr(4, 0, lines[lineIndex + 1].c_str());
            attroff(COLOR_PAIR(1));
        }
        attron(COLOR_PAIR(2));
        mvaddstr(5, 0, (std::to_string(lineIndex + 1) + "/" + std::to_string(lines.size())).c_str());
        attroff(COLOR_PAIR(2));
        refresh();
        int ch = getch();
        switch (ch)
        {
        case KEY_END:
            quit = true;
            break;
        case KEY_BACKSPACE:
            if (!m.backspace() && !line.empty())
            {
                line.erase(line.end() - 1);
            }
            break;
        case KEY_ENTER:
        case '\n':
            prevline = line + m.flush();
            line.clear();
            m.reset();
            lineIndex++;
            break;
        case ' ':
            line += m.flush() + L" ";
            break;
        default:
            if (m.process(ch))
            {
                std::wstring commit = m.get_commit();
                if (!commit.empty())
                {
                    line += commit;
                }
            }
            break;
        }
    }
    end();
}