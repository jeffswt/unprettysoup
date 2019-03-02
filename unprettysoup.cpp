
#include "unprettysoup.h"


void us3::Char::from_string(std::string bstr, int& pos)
{
    this->value = 0;
    if (pos > bstr.length() - 1)
        return ;
    int ch1 = bstr[pos++] & 0xff, ch2, ch3, ch4;
    if ((ch1 >> 7) == 0x00) {
        this->value += ch1 & 0x7f;  // 0xxxxxxx
    } else if ((ch1 >> 5) == 0x06) {
        if (pos > bstr.length() - 1)
            return ;
        ch2 = bstr[pos++] & 0xff;
        this->value += ch1 & 0x1f;  // 110xxxxx
        this->value <<= 6;
        this->value += ch2 & 0x3f;  // 10xxxxxx
    } else if ((ch1 >> 4) == 0x0e) {
        if (pos > bstr.length() - 2)
            return ;
        ch2 = bstr[pos++] & 0xff;
        ch3 = bstr[pos++] & 0xff;
        this->value += ch1 & 0x0f;  // 1110xxxx
        this->value <<= 6;
        this->value += ch2 & 0x3f;  // 10xxxxxx
        this->value <<= 6;
        this->value += ch3 & 0x3f;  // 10xxxxxx
    } else if ((ch1 >> 3) == 0x1e) {
        if (pos > bstr.length() - 3)
            return ;
        ch2 = bstr[pos++] & 0xff;
        ch3 = bstr[pos++] & 0xff;
        ch4 = bstr[pos++] & 0xff;
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

std::string us3::Char::to_string(void) const
{
    unsigned long long value = this->value;
    std::string output = "";
    if (value >= 0x0000 && value <= 0x007f) {
        output += char((value & 0x7f) ^ 0x00);
    } else if (value >= 0x0080 && value <= 0x07ff) {
        output += char(((value >> 6) & 0x1f) ^ 0xc0);
        output += char((value & 0x3f) ^ 0x80);
    } else if (value >= 0x0800 && value <= 0xffff) {
        output += char(((value >> 12) & 0x0f) ^ 0xe0);
        output += char(((value >> 6) & 0x3f) ^ 0x80);
        output += char((value & 0x3f) ^ 0x80);
    } else if (value >= 0x10000 && value <= 0x10ffff) {
        output += char(((value >> 18) & 0x07) ^ 0xf0);
        output += char(((value >> 12) & 0x3f) ^ 0x80);
        output += char(((value >> 6) & 0x3f) ^ 0x80);
        output += char((value & 0x3f) ^ 0x80);
    }
    return output;
}

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
    char _tmp;
    int tmp;
    unsigned long long result = 0;
    int await = 0;
    stream >> _tmp;
    tmp = int(_tmp) & 0xff;
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
        stream >> _tmp;
        tmp = int(_tmp) & 0xff;
        if ((tmp >> 6) != 0x03)
            return stream;
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

void us3::String::from_string(std::string str)
{
    this->contents.clear();
    int pos = 0;
    while (pos < str.length()) {
        us3::Char chr(str, pos);
        this->contents.push_back(chr);
    }
    return ;
}

std::string us3::String::to_string(void) const
{
    std::string output;
    for (int i = 0; i < this->contents.length(); i++)
        output += this->contents[i].to_string();
    return output;
}

us3::String::String(void)
{
    this->contents.clear();
    return ;
}

us3::String::String(std::string str)
{
    this->from_string(str);
    return ;
}

us3::String::String(char* str)
{
    std::string tmp;
    tmp.assign(str, strlen(str));
    this->from_string(tmp);
    return ;
}

us3::String::String(const char* str)
{
    this->from_string(std::string(str));
    return ;
}

us3::String::String(us3::Char chr)
{
    this->contents.clear();
    this->contents.push_back(chr);
    return ;
}

size_t us3::String::length(void) const
{
    return this->contents.length();
}
 
us3::Char us3::String::operator [] (int pos) const
{
    if (pos < 0 || pos >= this->length())
        return us3::Char();
    return this->contents[pos];
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

us3::String& us3::String::operator += (const us3::Char& chr)
{
    this->contents.push_back(chr);
    return *this;
}

us3::String& us3::String::operator += (const us3::String& str)
{
    this->contents += str.contents;
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
        result += chr;
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

us3::String us3::String::substr(int begin, int end)
{
    begin = std::max(std::min(begin, int(this->length()) - 1), 0);
    end = std::max(std::min(end, int(this->length()) - 1), 0);
    if (this->length() == 0 || end < begin)
        return us3::String();
    us3::String result;
    result.contents = this->contents.substr(begin, end - begin + 1);
    return result;
}

us3::String us3::String::upper(void)
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->operator[](i);
        if (chr >= us3::Char('a') && chr <= us3::Char('z'))
            chr = chr - us3::Char('a') + us3::Char('A');
        result += chr;
    }
    return result;
}

std::istream& us3::operator >> (std::istream& stream, us3::String& str)
{
    std::string tmp;
    stream >> tmp;
    str.from_string(tmp);
    return stream;
}

std::ostream& us3::operator << (std::ostream& stream, const us3::String& str)
{
    stream << str.to_string();
    return stream;
}

int main()
{
    using namespace std;
    std::string a = "abc测试", b = "这是一个字符串~";
    us3::String au = a, bu = b;
    cout << "std::string: " << a << " [length=" << a.length() << "]; us3::String: " <<
        au << " [length=" << au.length() << "];\n";
    cout << "std::string: " << b << " [length=" << b.length() << "]; us3::String: " <<
        bu << " [length=" << bu.length() << "];\n";
    us3::String c = au.upper();
    c *= 5;
    cout << c.substr(2, 3) << endl;
    return 0;
}
