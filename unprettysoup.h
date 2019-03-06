
#ifndef UNPRETTYSOUP_H
#define UNPRETTYSOUP_H

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <functional>
#include <vector>
#include <set>
#include <map>


namespace us3
{
    class Char
    {
    protected:
        unsigned int value;
    public:
        // Converters
        void from_string(std::string, int&);
        std::string to_string(void) const;
        // Initializers
        Char(void);
        Char(char);
        Char(unsigned int);
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
        String lstrip(void) const;
        String lstrip(const Char&) const;
        String lstrip(const String&) const;
        String lstrip(const std::set<Char>&) const;
        String replace(const String&, const String&, int) const;
        String repr(void) const;
        String reversed(void) const;
        String rjust(int, const Char&) const;
        String rstrip(void) const;
        String rstrip(const Char&) const;
        String rstrip(const String&) const;
        String rstrip(const std::set<Char>&) const;
        std::vector<String> split(const String&) const;
        bool startswith(const String&) const;
        String strip(void) const;
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
        CorruptedTag,  // This is not to be parsed
        NavigableString,  // ...
        Comment,  // <!--...-->
    };

    class Element
    {
    protected:
    public:
        // Data
        std::map<String, String> p_attrs;  // Element attributes [Tag]
        // Relations
        Element* p_parent;
        std::vector<Element*> p_children;
    public:
        ElementType type;  // Element type
        String name;  // Element name [Tag]
        String content;  // String content [Doctype, NavigableString, Comment]
        // Initializers
        Element(void);
        // Data access functions
        // String& operator [] (const String&) const;
        // bool attrs_has(const String&);
        // String attrs_get(const String&) const;
        // void attrs_set(const String&, const String&);
        // Traversal functions
        std::vector<Element*> contents(bool);
        std::vector<Element*> children(bool);
        std::vector<Element*> descendants(bool);
        Element* string(void);
        std::vector<Element*> strings(void);
        std::vector<String> stripped_strings(void);
        Element* parent(void);
        std::vector<Element*> parents(int);
        Element* next_sibling(void);
        Element* previous_sibling(void);
        std::vector<Element*> next_siblings(int);
        std::vector<Element*> previous_siblings(int);
        // Element query functions
        // std::vector<Element*> find_all(bool (*)(Element*),
        //         std::map<String, String>, bool, int);
        // String query functions
        std::vector<Element*> find_all_s(std::function<bool(const String&)>,
                                         bool, int);
        std::vector<Element*> find_all_s(const std::set<String>&, bool, int);
        std::vector<Element*> find_all_s(const std::vector<String>&, bool,
                                         int);
        std::vector<Element*> find_all_s(const String&, bool, int);
        std::vector<Element*> find_all_s(bool, bool, int);
        // Element modification functions
        // Friends
        friend class ElementParser;
    };

    class ElementParser
    {
    protected:
        us3::String page, page_lower;
        bool get_string(int&, String&);
        bool get_element(int&, Element*&);
        bool get_doctype(int&, Element*&);
        bool get_tag(int&, Element*&);
        bool get_tag_open(int&, Element*&, bool&);
        bool get_tag_close(int&, Element*&);
        bool get_tag_raw(int&, Element*&);  // W.I.P.
        bool get_corrupted_tag(int&);
        bool get_comment(int&, Element*&);
        Element* parse(const String&);
        friend Element* UnprettySoup(const String&);
    };  // You should not use this

    Element* UnprettySoup(const String&);
    Element* UnprettySoup(std::istream&);
} // us3

#endif
