
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>


namespace us3
{
    class Char
    {
    protected:
        unsigned long long value;
        // Initializers
        Char(void);
        Char(char);
        Char(std::string);
        Char(std::string, int&);
        // Comparison operators
        bool operator == (const Char&) const;
        bool operator != (const Char&) const;
        bool operator < (const Char&) const;
        bool operator > (const Char&) const;
        bool operator <= (const Char&) const;
        bool operator >= (const Char&) const;
        // Manipulative operators
        Char operator + (const Char&);
        Char& operator += (const Char&);
        Char operator - (const Char&);
        Char& operator -= (const Char&);
        // Input and output
        friend std::istream& operator >> (std::istream&, Char&);
        friend std::ostream& operator << (std::ostream&, const Char&);
    };

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
        int length(void) const;
        Char operator [] (int) const;
        // Comparison operators
        bool operator == (const String&) const;
        bool operator != (const String&) const;
        bool operator < (const String&) const;
        bool operator > (const String&) const;
        bool operator <= (const String&) const;
        bool operator >= (const String&) const;
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
        // std::vector<String> split(const String&);
        // bool startswith(const String&);
        // String strip(const String&);
        // String strip(const std::vector<String>&);
        // String swapcase(void);
        String upper(void);
        // Input and output
        friend std::istream& operator >> (std::istream&, String&);
        friend std::ostream& operator << (std::ostream&, const String&);
    };

    std::istream& operator >> (std::istream&, Char&);
    std::ostream& operator << (std::ostream&, const Char&);
    std::istream& operator >> (std::istream&, String&);
    std::ostream& operator << (std::ostream&, const String&);
} // us3

#endif
