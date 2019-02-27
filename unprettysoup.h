
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>


namespace us3
{
    class String
    {
    private:
    protected:
        std::string contents;
    public:
        // Initializers
        String(void);
        String(std::string);
        String(char*);
        String(const char*);
        // Operators mimic std::string
        int length(void);
        String operator + (const String&);
        String& operator += (const String&);
        String operator * (const int&);
        String& operator *= (const int&);
        friend std::istream& operator >> (std::istream&, String&);
        friend std::ostream& operator << (std::ostream&, const String&);
    };

    std::istream& operator >> (std::istream&, String&);
    std::ostream& operator << (std::ostream&, const String&);
} // us3

#endif
