
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

std::vector<us3::String> us3::String::split(const us3::String& sep)
{
    std::vector<us3::String> result;
    // TODO: Not yet implemented
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
    us3::String a = "abc", b = "def";
    us3::String c = a + b;
    vector<us3::String> vec;
    for (int i = 0; i < 5; i++)
        vec.push_back(c);
    cout << us3::String(" ").join(vec) << endl;
}
