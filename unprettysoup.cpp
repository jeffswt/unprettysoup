
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

us3::String::String(char chr)
{
    this->contents = std::string();
    this->contents += chr;
    return ;
}

int us3::String::length(void) const
{
    return this->contents.length();
}
 
us3::Char us3::String::operator [] (int pos) const
{
    if (pos < 0 || pos > this->length())
        return Char(char(0));
    return Char(this->contents[pos]);
}

bool us3::String::operator == (const us3::String& str) const
{
    if (this->length() != str.length())
        return false;
    for (int i = 0; i < this->length(); i++)
        if (this->operator[](i) != str[i])
            return false;
    return true;
}

bool us3::String::operator != (const us3::String& str) const
{
    return !(*this == str);
}

bool us3::String::operator < (const us3::String& str) const
{
    int len = std::min(this->length(), str.length());
    for (int i = 0; i < len; i++) {
        if (this->operator[](i) > str[i])
            return false;
        if (this->operator[](i) < str[i])
            return true;
    }
    return this->length() < str.length();
}

bool us3::String::operator > (const us3::String& str) const
{
    int len = std::min(this->length(), str.length());
    for (int i = 0; i < len; i++) {
        if (this->operator[](i) < str[i])
            return false;
        if (this->operator[](i) > str[i])
            return true;
    }
    return this->length() > str.length();
}

bool us3::String::operator <= (const us3::String& str) const
{
    return !(*this > str);
}

bool us3::String::operator >= (const us3::String& str) const
{
    return !(*this < str);
}

us3::String us3::String::operator + (const us3::String& str)
{
    us3::String ret;
    ret.contents = this->contents + str.contents;
    return ret;
}

us3::String& us3::String::operator += (const us3::String& str)
{
    *this += str;
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

us3::String us3::String::casefold(void)
{
    return this->lower();
}

us3::String us3::String::lower(void)
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->operator[](i);
        if (chr >= Char('A') && chr <= Char('Z'))
            chr = chr - Char('A') + Char('a');
        result += us3::String(chr);
    }
    return result;
}

us3::String us3::String::join(const std::vector<us3::String>& list)
{
    us3::String result;
    bool first = true;
    for (auto str : list) {
        if (!first)
            result += *this;
        else
            first = false;
        result += str;
    }
    return result;
}

// std::vector<us3::String> us3::String::split(const us3::String& sep)
// {
//     std::vector<us3::String> result;
//     // TODO: Not yet implemented
//     return result;
// }

us3::String us3::String::upper(void)
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->operator[](i);
        if (chr >= Char('a') && chr <= Char('z'))
            chr = chr - Char('a') + Char('A');
        result += us3::String(chr);
    }
    return result;
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

int main()
{
    using namespace std;
    us3::String a = "abc", b = "卧槽";
    us3::String c = a + b;
    for (int i = 0; i < b.length(); i++)
        printf("%.2x\n", short(b[i]));
    vector<us3::String> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(c);
    return 0;
}
