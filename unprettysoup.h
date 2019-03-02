
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>


#define bin(_x) (int(((_x) / 10000000 % 2) * 128 + ((_x) / 1000000 % 2) *\
    64 + ((_x) / 100000 % 2) * 32 + ((_x) / 10000 % 2) * 16 +\
    ((_x) / 1000 % 2) * 8 + ((_x) / 100 % 2) * 4 + ((_x) / 10 % 2) * 2 +\
    ((_x) / 1 % 2) * 1))

namespace us3
{
    class Char
    {
    protected:
        unsigned long long value;
    public:
        // Converters
        void from_string(std::string, int&);
        std::string to_string(void) const;
        // Initializers
        Char(void);
        Char(char);
        Char(unsigned long long);
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
        Char operator + (const Char&) const;
        Char& operator += (const Char&);
        Char operator - (const Char&) const;
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
        // Converters
        // void from_string(std::string);
        // std::string to_string(void);
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
        String operator + (const String&) const;
        String& operator += (const String&);
        String operator * (const int&) const;  // Python
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
