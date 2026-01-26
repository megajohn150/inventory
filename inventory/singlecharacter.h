#ifndef SINGLECHARACTER_H
#define SINGLECHARACTER_H

char getSingleChar();

#ifdef _WIN32
#define CLEAR "cls"
#elif __APPLE__
#define CLEAR "clear"
#else
#define CLEAR "clear"
#endif

#endif
