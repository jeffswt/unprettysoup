
#include "unprettysoup.h"


us3::String::String(void)
{
    this->contents = std::string();
    return ;
}

us3::String::String(std::string str)
{
    this->contents = str;
    return ;
}

us3::String::String(char* str)
{
    this->contents = "";
    this->contents.assign(str, strlen(str));
    return ;
}

us3::String::String(const char* str)
{
    this->contents = std::string(str);
    return ;
}

int us3::String::length(void)
{
    return this->contents.length();
}

us3::String us3::String::operator + (const us3::String& str)
{
    us3::String ret;
    ret.contents = this->contents + str.contents;
    return ret;
}

us3::String& us3::String::operator += (const us3::String& str)
{
    *this = *this + str;
    return *this;
}

us3::String us3::String::operator * (const int& combo)
{
    us3::String ret;
    for (int i = 0; i < combo; i++)
        ret += *this;
    return ret;
}

us3::String& us3::String::operator *= (const int& combo)
{
    *this = *this * combo;
    return *this;
}

std::istream& us3::operator >> (std::istream& stream, us3::String& str)
{
    stream >> str.contents;
    return stream;
}

std::ostream& us3::operator << (std::ostream& stream, const us3::String& str)
{
    stream << str.contents;
    return stream;
}
