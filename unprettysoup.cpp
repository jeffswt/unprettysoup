
#include "unprettysoup.h"


us3::Char::Char(void)
{
    this->value = 0;
    return ;
}

us3::Char::Char(char value)
{
    this->value = value;
    return ;
}

us3::Char::Char(unsigned long long value)
{
    this->value = value;
    return ;
}

void us3::Char::from_string(std::string bstr, int& pos)
{
    this->value = 0;
    if (pos > bstr.length() - 1)
        return ;
    char ch1 = bstr[pos++], ch2, ch3, ch4;
    if ((ch1 >> 7) == 0x00) {
        this->value += ch1 & 0x7f;  // 0xxxxxxx
    } else if ((ch1 >> 5) == 0x06) {
        if (pos > bstr.length() - 1)
            return ;
        ch2 = bstr[pos++];
        this->value += ch1 & 0x1f;  // 110xxxxx
        this->value <<= 6;
        this->value += ch2 & 0x3f;  // 10xxxxxx
    } else if ((ch1 >> 4) == 0x0e) {
        if (pos > bstr.length() - 2)
            return ;
        ch2 = bstr[pos++];
        ch3 = bstr[pos++];
        this->value += ch1 & 0x0f;  // 1110xxxx
        this->value <<= 6;
        this->value += ch2 & 0x3f;  // 10xxxxxx
        this->value <<= 6;
        this->value += ch3 & 0x3f;  // 10xxxxxx
    } else if ((ch1 >> 3) == 0x1e) {
        if (pos > bstr.length() - 3)
            return ;
        ch2 = bstr[pos++];
        ch3 = bstr[pos++];
        ch4 = bstr[pos++];
        this->value += ch1 & 0x07;  // 11110xxx
        this->value <<= 6;
        this->value += ch2 & 0x3f;  // 10xxxxxx
        this->value <<= 6;
        this->value += ch3 & 0x3f;  // 10xxxxxx
        this->value <<= 6;
        this->value += ch4 & 0x3f;  // 10xxxxxx
    }
    return ;
}

us3::Char::Char(std::string bstr)
{
    int pos = 0;
    this->from_string(bstr, pos);
    return ; 
}

us3::Char::Char(std::string bstr, int& pos)
{
    this->from_string(bstr, pos);
    return ;
}

bool us3::Char::operator == (const us3::Char& chr) const
{
    return this->value == chr.value;
}

bool us3::Char::operator != (const us3::Char& chr) const
{
    return this->value != chr.value;
}

bool us3::Char::operator < (const us3::Char& chr) const
{
    return this->value < chr.value;
}

bool us3::Char::operator > (const us3::Char& chr) const
{
    return this->value > chr.value;
}

bool us3::Char::operator <= (const us3::Char& chr) const
{
    return this->value <= chr.value;
}

bool us3::Char::operator >= (const us3::Char& chr) const
{
    return this->value >= chr.value;
}

us3::Char us3::Char::operator + (const us3::Char& chr) const
{
    return us3::Char(this->value + chr.value);
}

us3::Char& us3::Char::operator += (const us3::Char& chr)
{
    this->value += chr.value;
    return *this;
}

us3::Char us3::Char::operator - (const us3::Char& chr) const
{
    return us3::Char(this->value - chr.value);
}

us3::Char& us3::Char::operator -= (const us3::Char& chr)
{
    this->value -= chr.value;
    return *this;
}

std::istream& us3::operator >> (std::istream& stream, us3::Char& chr)
{
    char tmp;
    unsigned long long result = 0;
    int await = 0;
    stream >> tmp;
    if ((tmp >> 7) == 0x00) {
        await = 0;
        result = tmp & 0x7f;  // 0xxxxxxx
    } else if ((tmp >> 5) == 0x06) {
        await = 1;
        result = tmp & 0x1f;  // 110xxxxx
    } else if ((tmp >> 4) == 0x0e) {
        await = 2;
        result = tmp & 0x0f;  // 1110xxxx
    } else if ((tmp >> 3) == 0x1e) {
        await = 3;
        result = tmp & 0x07;  // 11110xxx
    }
    while (await > 0) {
        stream >> tmp;
        result <<= 6;
        result += tmp & 0x3f;  // 10xxxxxx
        await--;
    }
    chr.value = result;
    return stream;
}

std::ostream& us3::operator << (std::ostream& stream, const us3::Char& chr)
{
    stream << chr.to_string();
    return stream;
}

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

us3::String::String(us3::Char chr)
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
        return us3::Char(char(0));
    return us3::Char(this->contents[pos]);
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

us3::String us3::String::operator + (const us3::String& str) const
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

us3::String us3::String::operator * (const int& combo) const
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
        if (chr >= us3::Char('A') && chr <= us3::Char('Z'))
            chr = chr - us3::Char('A') + us3::Char('a');
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
        if (chr >= us3::Char('a') && chr <= us3::Char('z'))
            chr = chr - us3::Char('a') + us3::Char('A');
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
    cout << c << endl;
    return 0;
}
