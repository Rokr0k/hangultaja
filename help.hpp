#pragma once

#include <config.h>

#define HELP_MSG(argv0) "Word practice\n"                                                                         \
                        " $ " +                                                                                   \
                            std::string(argv0) + " word $COUNT $LAYOUT\n"                                         \
                                                 " COUNT: Number of words to practice. (Default to 50)\n"         \
                                                 " LAYOUT: Layout of the keyboard.\n"                             \
                                                 "Sentences practice\n"                                           \
                                                 " $ " +                                                          \
                            std::string(argv0) + " short $COUNT $LAYOUT\n"                                        \
                                                 " COUNT: Number of sentences to practice. (Default to 50)\n"     \
                                                 " LAYOUT: Layout of the keyboard.\n"                             \
                                                 "Document practice\n"                                            \
                                                 " $ " +                                                          \
                            std::string(argv0) + " long $DOCUMENT $LAYOUT\n"                                      \
                                                 " DOCUMENT: Document to practice. ({*} from res/long/{*}.txt)\n" \
                                                 " LAYOUT: Layout of the keyboard.\n"                             \
                                                 "\n"                                                             \
                                                 "Layouts\n"                                                      \
                                                 " 2, 2y, 3f, 39, 3s, 3y, 32, ro\n"
