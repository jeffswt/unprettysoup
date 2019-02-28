
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>


namespace us3
{
    typedef char Char;
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
        String(Char);
        // Property operators
        int length(void);
        Char operator [] (const int&);
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
        // Advanced methods (Python)
        String casefold(void);
        // String count(int, int, int);
        // String endswith(const String&);
        // String expandtabs(int);
        // bool isalnum(void);
        // bool isalpha(void);
        // bool isdecimal(void);
        // bool isdigit(void);
        // bool islower(void);
        // bool isnumeric(void);
        // bool isspace(void);
        // bool isupper(void);
        String join(const std::vector<String>&);
        // String ljust(int, const String&);
        String lower(void);
        // String lstrip(const String&);
        // String lstrip(const std::vector<String>&);
        // String rjust(int, const String&);
        // String rstrip(const String&);
        // String rstrip(const std::vector<String>&);
        // bool startswith(const String&);
        // String strip(const String&);
        // String strip(const std::vector<String>&);
        // String swapcase(void);
        String upper(void);
        // std::vector<String> split(const String&);
        // Input and output
        friend std::istream& operator >> (std::istream&, String&);
        friend std::ostream& operator << (std::ostream&, const String&);
    };

    std::istream& operator >> (std::istream&, String&);
    std::ostream& operator << (std::ostream&, const String&);
} // us3

#endif
