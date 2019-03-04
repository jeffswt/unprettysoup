
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <vector>
#include <set>
#include <map>


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
        // Determination methods
        bool isalnum(void) const;
        bool isalpha(void) const;
        bool isdecimal(void) const;
        bool isdigit(void) const;
        bool islower(void) const;
        bool isnumeric(void) const;
        bool isspace(void) const;
        bool isupper(void) const;
        // Input and output
        friend std::istream& operator >> (std::istream&, Char&);
        friend std::ostream& operator << (std::ostream&, const Char&);
    };

    class String
    {
    private:
    protected:
        std::basic_string<Char> contents;
    public:
        // Converters
        void from_string(std::string);
        std::string to_string(void) const;
        // Initializers
        String(void);
        String(std::string);
        String(char*);
        String(const char*);
        String(Char);
        // Property operators
        size_t length(void) const;
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
        String& operator += (const Char&);
        String& operator += (const String&);
        String operator * (const int&) const;
        String& operator *= (const int&);
        // Advanced methods (Python)
        String casefold(void) const;  // No Unicode support
        void clear(void);
        int count(const String&, int, int) const;
        bool endswith(const String&) const;
        String expandtabs(int) const;
        int* find_kmp_get_next(void) const;
        int find(const String&, int*, int) const;
        int find(const String&, int) const;
        int find_first_of(const Char&, int) const;
        int find_first_of(const String&, int) const;
        int find_first_of(const std::set<Char>&, int) const;
        int find_last_of(const Char&, int) const;
        int find_last_of(const String&, int) const;
        int find_last_of(const std::set<Char>&, int) const;
        int find_first_not_of(const Char&, int) const;
        int find_first_not_of(const String&, int) const;
        int find_first_not_of(const std::set<Char>&, int) const;
        int find_last_not_of(const Char&, int) const;
        int find_last_not_of(const String&, int) const;
        int find_last_not_of(const std::set<Char>&, int) const;
        bool isalnum(void) const;
        bool isalpha(void) const;
        bool isdecimal(void) const;
        bool isdigit(void) const;
        bool islower(void) const;
        bool isnumeric(void) const;
        bool isspace(void) const;
        bool isupper(void) const;
        String join(const std::vector<String>&) const;
        String ljust(int, const Char&) const;
        String lower(void) const;  // No Unicode support
        String lstrip(const Char&) const;
        String lstrip(const String&) const;
        String lstrip(const std::set<Char>&) const;
        String replace(const String&, const String&, int) const;
        String reversed(void) const;
        String rjust(int, const Char&) const;
        String rstrip(const Char&) const;
        String rstrip(const String&) const;
        String rstrip(const std::set<Char>&) const;
        std::vector<String> split(const String&) const;
        bool startswith(const String&) const;
        String strip(const Char&) const;
        String strip(const String&) const;
        String strip(const std::set<Char>&) const;
        String substr(int, int) const;
        String swapcase(void) const;  // No Unicode support
        String upper(void) const;  // No Unicode support
        // Input and output
        friend std::istream& operator >> (std::istream&, String&);
        friend std::ostream& operator << (std::ostream&, const String&);
    };

    std::istream& operator >> (std::istream&, Char&);
    std::ostream& operator << (std::ostream&, const Char&);
    std::istream& operator >> (std::istream&, String&);
    std::ostream& operator << (std::ostream&, const String&);

    enum ElementType
    {
        Doctype,  // <!DOCTYPE html>
        Tag,  // <tag>...</tag>
        NavigableString,  // ...
        Comment,  // <!--...-->
    };

    class Element
    {
    protected:
        // Data
        ElementType p_type;  // Element type
        String p_content;  // Contents [Doctype, NavigableString, Comment]
        std::map<String, String> p_attrs;  // Element attributes [Tag]
        // Relations
        Element* p_parent;
        std::vector<Element> p_descendants;
    public:
        String name;  // Element name [Tag]
        // Initializers
        Element(void);
        // Data access functions
        // String& operator [] (const String&) const;
        // bool attrs_has(const String&);
        // String attrs_get(const String&) const;
        // void attrs_set(const String&, const String&);
        // Element query functions
        // Element modification functions
        // Friends
        friend class ElementParser;
    };

    class ElementParser
    {
    protected:
        friend Element UnprettySoup(const String&);
    };  // You should not use this

    Element UnprettySoup(const String&);
} // us3

#endif
