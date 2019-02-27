
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
        String(char);
        // Property operators
        int length(void);
        String operator [] (const int&);
        // Comparison operators
        bool operator == (const String&);
        bool operator != (const String&);
        bool operator < (const String&);
        bool operator > (const String&);
        bool operator <= (const String&);
        bool operator >= (const String&);
        // Manipulative operators
        String operator + (const String&);
        String& operator += (const String&);
        String operator * (const int&);  // Python
        String& operator *= (const int&);  // Python
        // Advanced methods
        String join(const std::vector<String>&);  // Python
        std::vector<String> split(const String&);  // Python
        // Input and output
        friend std::istream& operator >> (std::istream&, String&);
        friend std::ostream& operator << (std::ostream&, const String&);
    };

    std::istream& operator >> (std::istream&, String&);
    std::ostream& operator << (std::ostream&, const String&);
} // us3

#endif
