
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

bool us3::Char::isalnum(void) const
{
    return this->isalpha() || this->isnumeric();
}

bool us3::Char::isalpha(void) const
{
    // WARNING: THIS METHOD IS NOT UNICODE SAFE
    return this->islower() || this->isupper();
}

bool us3::Char::isdecimal(void) const
{
    #define rn(_x, _y) (this->value >= (_x) && this->value <= (_y))
    return (rn(0x00, 0xff) && rn(0x30, 0x39)) || (rn(0x0100, 0x10ffff) && (
           rn(0x0660, 0x0669) || rn(0x06f0, 0x06f9) ||
           rn(0x07c0, 0x07c9) || rn(0x0966, 0x096f) || rn(0x09e6, 0x09ef) ||
           rn(0x0a66, 0x0a6f) || rn(0x0ae6, 0x0aef) || rn(0x0b66, 0x0b6f) ||
           rn(0x0be6, 0x0bef) || rn(0x0c66, 0x0c6f) || rn(0x0ce6, 0x0cef) ||
           rn(0x0d66, 0x0d6f) || rn(0x0de6, 0x0def) || rn(0x0e50, 0x0e59) ||
           rn(0x0ed0, 0x0ed9) || rn(0x0f20, 0x0f29) || rn(0x1040, 0x1049) ||
           rn(0x1090, 0x1099) || rn(0x17e0, 0x17e9) || rn(0x1810, 0x1819) ||
           rn(0x1946, 0x194f) || rn(0x19d0, 0x19d9) || rn(0x1a80, 0x1a89) ||
           rn(0x1a90, 0x1a99) || rn(0x1b50, 0x1b59) || rn(0x1bb0, 0x1bb9) ||
           rn(0x1c40, 0x1c49) || rn(0x1c50, 0x1c59) || rn(0xa620, 0xa629) ||
           rn(0xa8d0, 0xa8d9) || rn(0xa900, 0xa909) || rn(0xa9d0, 0xa9d9) ||
           rn(0xa9f0, 0xa9f9) || rn(0xaa50, 0xaa59) || rn(0xabf0, 0xabf9) ||
           rn(0xff10, 0xff19) || rn(0x0104a0, 0x0104a9) ||
           rn(0x011066, 0x01106f) || rn(0x0110f0, 0x0110f9) ||
           rn(0x011136, 0x01113f) || rn(0x0111d0, 0x0111d9) ||
           rn(0x0112f0, 0x0112f9) || rn(0x0114d0, 0x0114d9) ||
           rn(0x011650, 0x011659) || rn(0x0116c0, 0x0116c9) ||
           rn(0x011730, 0x011739) || rn(0x0118e0, 0x0118e9) ||
           rn(0x016a60, 0x016a69) || rn(0x016b50, 0x016b59) ||
           rn(0x01d7ce, 0x01d7ff)));
    #undef rn
}

bool us3::Char::isdigit(void) const
{
    #define rn(_x, _y) (this->value >= (_x) && this->value <= (_y))
    return (rn(0x00, 0xff) && (rn(0x30, 0x39) || rn(0xb2, 0xb3) ||
           rn(0xb9, 0xb9))) || (rn(0x0100, 0x10ffff) && (
           rn(0x0660, 0x0669) || rn(0x06f0, 0x06f9) || rn(0x07c0, 0x07c9) ||
           rn(0x0966, 0x096f) || rn(0x09e6, 0x09ef) || rn(0x0a66, 0x0a6f) ||
           rn(0x0ae6, 0x0aef) || rn(0x0b66, 0x0b6f) || rn(0x0be6, 0x0bef) ||
           rn(0x0c66, 0x0c6f) || rn(0x0ce6, 0x0cef) || rn(0x0d66, 0x0d6f) ||
           rn(0x0de6, 0x0def) || rn(0x0e50, 0x0e59) || rn(0x0ed0, 0x0ed9) ||
           rn(0x0f20, 0x0f29) || rn(0x1040, 0x1049) || rn(0x1090, 0x1099) ||
           rn(0x1369, 0x1371) || rn(0x17e0, 0x17e9) || rn(0x1810, 0x1819) ||
           rn(0x1946, 0x194f) || rn(0x19d0, 0x19da) || rn(0x1a80, 0x1a89) ||
           rn(0x1a90, 0x1a99) || rn(0x1b50, 0x1b59) || rn(0x1bb0, 0x1bb9) ||
           rn(0x1c40, 0x1c49) || rn(0x1c50, 0x1c59) || rn(0x2070, 0x2070) ||
           rn(0x2074, 0x2079) || rn(0x2080, 0x2089) || rn(0x2460, 0x2468) ||
           rn(0x2474, 0x247c) || rn(0x2488, 0x2490) || rn(0x24ea, 0x24ea) ||
           rn(0x24f5, 0x24fd) || rn(0x24ff, 0x24ff) || rn(0x2776, 0x277e) ||
           rn(0x2780, 0x2788) || rn(0x278a, 0x2792) || rn(0xa620, 0xa629) ||
           rn(0xa8d0, 0xa8d9) || rn(0xa900, 0xa909) || rn(0xa9d0, 0xa9d9) ||
           rn(0xa9f0, 0xa9f9) || rn(0xaa50, 0xaa59) || rn(0xabf0, 0xabf9) ||
           rn(0xff10, 0xff19) || rn(0x0104a0, 0x0104a9) ||
           rn(0x010a40, 0x010a43) || rn(0x010e60, 0x010e68) ||
           rn(0x011052, 0x01105a) || rn(0x011066, 0x01106f) ||
           rn(0x0110f0, 0x0110f9) || rn(0x011136, 0x01113f) ||
           rn(0x0111d0, 0x0111d9) || rn(0x0112f0, 0x0112f9) ||
           rn(0x0114d0, 0x0114d9) || rn(0x011650, 0x011659) ||
           rn(0x0116c0, 0x0116c9) || rn(0x011730, 0x011739) ||
           rn(0x0118e0, 0x0118e9) || rn(0x016a60, 0x016a69) ||
           rn(0x016b50, 0x016b59) || rn(0x01d7ce, 0x01d7ff) ||
           rn(0x01f100, 0x01f10a)));
    #undef rn
}

bool us3::Char::islower(void) const
{
    #define eq(_x) (this->value == (_x))
    #define rn(_x, _y) (this->value >= (_x) && this->value <= (_y))
    #define rnd(_x, _y, _z) (this->value >= (_x) && this->value <= (_y) &&\
        (this->value - (_x)) % (_z) == 0)
    return (rn(0x00, 0xff) && (rn(0x61, 0x7a) || eq(0xaa) ||
           rnd(0xb5, 0xba, 5) || rn(0xdf, 0xf6) || rn(0xf8, 0xff))) ||
           (rn(0x0100, 0x10ffff) && (rnd(0x0101, 0x0137, 2) ||
           rnd(0x0138, 0x0148, 2) || rnd(0x0149, 0x0177, 2) ||
           rnd(0x017a, 0x017e, 2) || rn(0x017f, 0x0180) ||
           rnd(0x0183, 0x0185, 2) || rnd(0x0188, 0x018c, 4) ||
           rnd(0x018d, 0x0192, 5) || rnd(0x0195, 0x0199, 4) ||
           rn(0x019a, 0x019b) || rnd(0x019e, 0x01a1, 3) ||
           rnd(0x01a3, 0x01a5, 2) || rnd(0x01a8, 0x01aa, 2) ||
           rnd(0x01ab, 0x01ad, 2) || rnd(0x01b0, 0x01b4, 4) ||
           rnd(0x01b6, 0x01b9, 3) || rnd(0x01ba, 0x01bd, 3) ||
           rn(0x01be, 0x01bf) || rnd(0x01c6, 0x01cc, 3) ||
           rnd(0x01ce, 0x01dc, 2) || rnd(0x01dd, 0x01ef, 2) ||
           rnd(0x01f0, 0x01f3, 3) || rnd(0x01f5, 0x01f9, 4) ||
           rnd(0x01fb, 0x0233, 2) || rn(0x0234, 0x0239) ||
           rnd(0x023c, 0x023f, 3) || rnd(0x0240, 0x0242, 2) ||
           rnd(0x0247, 0x024f, 2) || rn(0x0250, 0x0293) ||
           rn(0x0295, 0x02b8) || rn(0x02c0, 0x02c1) || rn(0x02e0, 0x02e4) ||
           eq(0x0345) || rnd(0x0371, 0x0373, 2) || rnd(0x0377, 0x037a, 3) ||
           rn(0x037b, 0x037d) || eq(0x0390) || rn(0x03ac, 0x03ce) ||
           rn(0x03d0, 0x03d1) || rn(0x03d5, 0x03d7) ||
           rnd(0x03d9, 0x03ef, 2) || rn(0x03f0, 0x03f3) ||
           rnd(0x03f5, 0x03fb, 3) || eq(0x03fc) || rn(0x0430, 0x045f) ||
           rnd(0x0461, 0x0481, 2) || rnd(0x048b, 0x04bf, 2) ||
           rnd(0x04c2, 0x04ce, 2) || rnd(0x04cf, 0x052f, 2) ||
           rn(0x0561, 0x0587) || rn(0x13f8, 0x13fd) || rn(0x1d00, 0x1dbf) ||
           rnd(0x1e01, 0x1e95, 2) || rn(0x1e96, 0x1e9d) ||
           rnd(0x1e9f, 0x1eff, 2) || rn(0x1f00, 0x1f07) ||
           rn(0x1f10, 0x1f15) || rn(0x1f20, 0x1f27) || rn(0x1f30, 0x1f37) ||
           rn(0x1f40, 0x1f45) || rn(0x1f50, 0x1f57) || rn(0x1f60, 0x1f67) ||
           rn(0x1f70, 0x1f7d) || rn(0x1f80, 0x1f87) || rn(0x1f90, 0x1f97) ||
           rn(0x1fa0, 0x1fa7) || rn(0x1fb0, 0x1fb4) || rn(0x1fb6, 0x1fb7) ||
           rnd(0x1fbe, 0x1fc2, 4) || rn(0x1fc3, 0x1fc4) ||
           rn(0x1fc6, 0x1fc7) || rn(0x1fd0, 0x1fd3) || rn(0x1fd6, 0x1fd7) ||
           rn(0x1fe0, 0x1fe7) || rn(0x1ff2, 0x1ff4) || rn(0x1ff6, 0x1ff7) ||
           eq(0x2071) || eq(0x207f) || rn(0x2090, 0x209c) ||
           rnd(0x210a, 0x210e, 4) || rnd(0x210f, 0x2113, 4) ||
           rnd(0x212f, 0x2139, 5) || rn(0x213c, 0x213d) ||
           rn(0x2146, 0x2149) || eq(0x214e) || rn(0x2170, 0x217f) ||
           eq(0x2184) || rn(0x24d0, 0x24e9) || rn(0x2c30, 0x2c5e) ||
           rnd(0x2c61, 0x2c65, 4) || rnd(0x2c66, 0x2c6c, 2) ||
           rnd(0x2c71, 0x2c73, 2) || rnd(0x2c74, 0x2c76, 2) ||
           rn(0x2c77, 0x2c7d) || rnd(0x2c81, 0x2ce3, 2) ||
           rnd(0x2ce4, 0x2cec, 8) || rnd(0x2cee, 0x2cf3, 5) ||
           rn(0x2d00, 0x2d25) || rnd(0x2d27, 0x2d2d, 6) ||
           rnd(0xa641, 0xa66d, 2) || rnd(0xa681, 0xa69b, 2) ||
           rn(0xa69c, 0xa69d) || rnd(0xa723, 0xa72f, 2) ||
           rn(0xa730, 0xa731) || rnd(0xa733, 0xa76f, 2) ||
           rn(0xa770, 0xa778) || rnd(0xa77a, 0xa77c, 2) ||
           rnd(0xa77f, 0xa787, 2) || rnd(0xa78c, 0xa78e, 2) ||
           rnd(0xa791, 0xa793, 2) || rn(0xa794, 0xa795) ||
           rnd(0xa797, 0xa7a9, 2) || rnd(0xa7b5, 0xa7b7, 2) ||
           rn(0xa7f8, 0xa7fa) || rn(0xab30, 0xab5a) ||
           rn(0xab5c, 0xab65) || rn(0xab70, 0xabbf) ||
           rn(0xfb00, 0xfb06) || rn(0xfb13, 0xfb17) ||
           rn(0xff41, 0xff5a) || rn(0x010428, 0x01044f) ||
           rn(0x010cc0, 0x010cf2) || rn(0x0118c0, 0x0118df) ||
           rn(0x01d41a, 0x01d433) || rn(0x01d44e, 0x01d454) ||
           rn(0x01d456, 0x01d467) || rn(0x01d482, 0x01d49b) ||
           rn(0x01d4b6, 0x01d4b9) || rnd(0x01d4bb, 0x01d4bd, 2) ||
           rn(0x01d4be, 0x01d4c3) || rn(0x01d4c5, 0x01d4cf) ||
           rn(0x01d4ea, 0x01d503) || rn(0x01d51e, 0x01d537) ||
           rn(0x01d552, 0x01d56b) || rn(0x01d586, 0x01d59f) ||
           rn(0x01d5ba, 0x01d5d3) || rn(0x01d5ee, 0x01d607) ||
           rn(0x01d622, 0x01d63b) || rn(0x01d656, 0x01d66f) ||
           rn(0x01d68a, 0x01d6a5) || rn(0x01d6c2, 0x01d6da) ||
           rn(0x01d6dc, 0x01d6e1) || rn(0x01d6fc, 0x01d714) ||
           rn(0x01d716, 0x01d71b) || rn(0x01d736, 0x01d74e) ||
           rn(0x01d750, 0x01d755) || rn(0x01d770, 0x01d788) ||
           rn(0x01d78a, 0x01d78f) || rn(0x01d7aa, 0x01d7c2) ||
           rn(0x01d7c4, 0x01d7c9) || eq(0x01d7cb)));
    #undef eq
    #undef rn
    #undef rnd
}

bool us3::Char::isnumeric(void) const
{
    #define rn(_x, _y) (this->value >= (_x) && this->value <= (_y))
    return (rn(0x00, 0xff) && (rn(0x30, 0x39) || rn(0xb2, 0xb3) ||
           rn(0xb9, 0xb9) || rn(0xbc, 0xbe))) || (rn(0x0100, 0x10ffff) && (
           rn(0x0660, 0x0669) || rn(0x06f0, 0x06f9) ||
           rn(0x07c0, 0x07c9) || rn(0x0966, 0x096f) || rn(0x09e6, 0x09ef) ||
           rn(0x09f4, 0x09f9) || rn(0x0a66, 0x0a6f) || rn(0x0ae6, 0x0aef) ||
           rn(0x0b66, 0x0b6f) || rn(0x0b72, 0x0b77) || rn(0x0be6, 0x0bf2) ||
           rn(0x0c66, 0x0c6f) || rn(0x0c78, 0x0c7e) || rn(0x0ce6, 0x0cef) ||
           rn(0x0d66, 0x0d75) || rn(0x0de6, 0x0def) || rn(0x0e50, 0x0e59) ||
           rn(0x0ed0, 0x0ed9) || rn(0x0f20, 0x0f33) || rn(0x1040, 0x1049) ||
           rn(0x1090, 0x1099) || rn(0x1369, 0x137c) || rn(0x16ee, 0x16f0) ||
           rn(0x17e0, 0x17e9) || rn(0x17f0, 0x17f9) || rn(0x1810, 0x1819) ||
           rn(0x1946, 0x194f) || rn(0x19d0, 0x19da) || rn(0x1a80, 0x1a89) ||
           rn(0x1a90, 0x1a99) || rn(0x1b50, 0x1b59) || rn(0x1bb0, 0x1bb9) ||
           rn(0x1c40, 0x1c49) || rn(0x1c50, 0x1c59) || rn(0x2070, 0x2070) ||
           rn(0x2074, 0x2079) || rn(0x2080, 0x2089) || rn(0x2150, 0x2182) ||
           rn(0x2185, 0x2189) || rn(0x2460, 0x249b) || rn(0x24ea, 0x24ff) ||
           rn(0x2776, 0x2793) || rn(0x2cfd, 0x2cfd) || rn(0x3007, 0x3007) ||
           rn(0x3021, 0x3029) || rn(0x3038, 0x303a) || rn(0x3192, 0x3195) ||
           rn(0x3220, 0x3229) || rn(0x3248, 0x324f) || rn(0x3251, 0x325f) ||
           rn(0x3280, 0x3289) || rn(0x32b1, 0x32bf) || rn(0x3405, 0x3405) ||
           rn(0x3483, 0x3483) || rn(0x382a, 0x382a) || rn(0x3b4d, 0x3b4d) ||
           rn(0x4e00, 0x4e00) || rn(0x4e03, 0x4e03) || rn(0x4e07, 0x4e07) ||
           rn(0x4e09, 0x4e09) || rn(0x4e5d, 0x4e5d) || rn(0x4e8c, 0x4e8c) ||
           rn(0x4e94, 0x4e94) || rn(0x4e96, 0x4e96) || rn(0x4ebf, 0x4ec0) ||
           rn(0x4edf, 0x4edf) || rn(0x4ee8, 0x4ee8) || rn(0x4f0d, 0x4f0d) ||
           rn(0x4f70, 0x4f70) || rn(0x5104, 0x5104) || rn(0x5146, 0x5146) ||
           rn(0x5169, 0x5169) || rn(0x516b, 0x516b) || rn(0x516d, 0x516d) ||
           rn(0x5341, 0x5341) || rn(0x5343, 0x5345) || rn(0x534c, 0x534c) ||
           rn(0x53c1, 0x53c4) || rn(0x56db, 0x56db) || rn(0x58f1, 0x58f1) ||
           rn(0x58f9, 0x58f9) || rn(0x5e7a, 0x5e7a) || rn(0x5efe, 0x5eff) ||
           rn(0x5f0c, 0x5f0e) || rn(0x5f10, 0x5f10) || rn(0x62fe, 0x62fe) ||
           rn(0x634c, 0x634c) || rn(0x67d2, 0x67d2) || rn(0x6f06, 0x6f06) ||
           rn(0x7396, 0x7396) || rn(0x767e, 0x767e) || rn(0x8086, 0x8086) ||
           rn(0x842c, 0x842c) || rn(0x8cae, 0x8cae) || rn(0x8cb3, 0x8cb3) ||
           rn(0x8d30, 0x8d30) || rn(0x9621, 0x9621) || rn(0x9646, 0x9646) ||
           rn(0x964c, 0x964c) || rn(0x9678, 0x9678) || rn(0x96f6, 0x96f6) ||
           rn(0xa620, 0xa629) || rn(0xa6e6, 0xa6ef) || rn(0xa830, 0xa835) ||
           rn(0xa8d0, 0xa8d9) || rn(0xa900, 0xa909) || rn(0xa9d0, 0xa9d9) ||
           rn(0xa9f0, 0xa9f9) || rn(0xaa50, 0xaa59) || rn(0xabf0, 0xabf9) ||
           rn(0xf96b, 0xf96b) || rn(0xf973, 0xf973) || rn(0xf978, 0xf978) ||
           rn(0xf9b2, 0xf9b2) || rn(0xf9d1, 0xf9d1) || rn(0xf9d3, 0xf9d3) ||
           rn(0xf9fd, 0xf9fd) || rn(0xff10, 0xff19) ||
           rn(0x010107, 0x010133) || rn(0x010140, 0x010178) ||
           rn(0x01018a, 0x01018b) || rn(0x0102e1, 0x0102fb) ||
           rn(0x010320, 0x010323) || rn(0x010341, 0x010341) ||
           rn(0x01034a, 0x01034a) || rn(0x0103d1, 0x0103d5) ||
           rn(0x0104a0, 0x0104a9) || rn(0x010858, 0x01085f) ||
           rn(0x010879, 0x01087f) || rn(0x0108a7, 0x0108af) ||
           rn(0x0108fb, 0x0108ff) || rn(0x010916, 0x01091b) ||
           rn(0x0109bc, 0x0109bd) || rn(0x0109c0, 0x0109cf) ||
           rn(0x0109d2, 0x0109ff) || rn(0x010a40, 0x010a47) ||
           rn(0x010a7d, 0x010a7e) || rn(0x010a9d, 0x010a9f) ||
           rn(0x010aeb, 0x010aef) || rn(0x010b58, 0x010b5f) ||
           rn(0x010b78, 0x010b7f) || rn(0x010ba9, 0x010baf) ||
           rn(0x010cfa, 0x010cff) || rn(0x010e60, 0x010e7e) ||
           rn(0x011052, 0x01106f) || rn(0x0110f0, 0x0110f9) ||
           rn(0x011136, 0x01113f) || rn(0x0111d0, 0x0111d9) ||
           rn(0x0111e1, 0x0111f4) || rn(0x0112f0, 0x0112f9) ||
           rn(0x0114d0, 0x0114d9) || rn(0x011650, 0x011659) ||
           rn(0x0116c0, 0x0116c9) || rn(0x011730, 0x01173b) ||
           rn(0x0118e0, 0x0118f2) || rn(0x012400, 0x01246e) ||
           rn(0x016a60, 0x016a69) || rn(0x016b50, 0x016b59) ||
           rn(0x016b5b, 0x016b61) || rn(0x01d360, 0x01d371) ||
           rn(0x01d7ce, 0x01d7ff) || rn(0x01e8c7, 0x01e8cf) ||
           rn(0x01f100, 0x01f10c) || rn(0x020001, 0x020001) ||
           rn(0x020064, 0x020064) || rn(0x0200e2, 0x0200e2) ||
           rn(0x020121, 0x020121) || rn(0x02092a, 0x02092a) ||
           rn(0x020983, 0x020983) || rn(0x02098c, 0x02098c) ||
           rn(0x02099c, 0x02099c) || rn(0x020aea, 0x020aea) ||
           rn(0x020afd, 0x020afd) || rn(0x020b19, 0x020b19) ||
           rn(0x022390, 0x022390) || rn(0x022998, 0x022998) ||
           rn(0x023b1b, 0x023b1b) || rn(0x02626d, 0x02626d) ||
           rn(0x02f890, 0x02f890)));
    #undef rn
}

bool us3::Char::isspace(void) const
{
    #define eq(_x) (this->value == (_x))
    return eq(0x0009) || eq(0x000a) || eq(0x000b) || eq(0x000c) ||
           eq(0x000d) || eq(0x0020) || eq(0x0085) || eq(0x00a0) ||
           eq(0x1680) || (this->value >= 0x2000 && this->value <= 0x200d) ||
           eq(0x2028) || eq(0x2029) || eq(0x202f) || eq(0x205f) ||
           eq(0x3000) || eq(0x180e) || eq(0x2060) || eq(0xfeff);
    #undef eq
}

bool us3::Char::isupper(void) const
{
    #define eq(_x) (this->value == (_x))
    #define rn(_x, _y) (this->value >= (_x) && this->value <= (_y))
    #define rnd(_x, _y, _z) (this->value >= (_x) && this->value <= (_y) &&\
        (this->value - (_x)) % (_z) == 0)
    return (rn(0x00, 0xff) && (rn(0x41, 0x5a) || rn(0xc0, 0xd6) ||
           rn(0xd8, 0xde))) || (rn(0x0100, 0x10ffff) && (
           rnd(0x0100, 0x0136, 2) || rnd(0x0139, 0x0147, 2) ||
           rnd(0x014a, 0x0178, 2) || rnd(0x0179, 0x017d, 2) ||
           rn(0x0181, 0x0182) || rnd(0x0184, 0x0186, 2) ||
           rnd(0x0187, 0x0189, 2) || rn(0x018a, 0x018b) ||
           rn(0x018e, 0x0191) || rn(0x0193, 0x0194) || rn(0x0196, 0x0198) ||
           rn(0x019c, 0x019d) || rn(0x019f, 0x01a0) ||
           rnd(0x01a2, 0x01a6, 2) || rnd(0x01a7, 0x01a9, 2) ||
           rnd(0x01ac, 0x01ae, 2) || rnd(0x01af, 0x01b1, 2) ||
           rn(0x01b2, 0x01b3) || rnd(0x01b5, 0x01b7, 2) ||
           rnd(0x01b8, 0x01bc, 4) || rnd(0x01c4, 0x01cd, 3) ||
           rnd(0x01cf, 0x01db, 2) || rnd(0x01de, 0x01ee, 2) ||
           rnd(0x01f1, 0x01f4, 3) || rn(0x01f6, 0x01f8) ||
           rnd(0x01fa, 0x0232, 2) || rn(0x023a, 0x023b) ||
           rn(0x023d, 0x023e) || rnd(0x0241, 0x0243, 2) ||
           rn(0x0244, 0x0246) || rnd(0x0248, 0x024e, 2) ||
           rnd(0x0370, 0x0372, 2) || eq(0x0376) || rnd(0x037f, 0x0386, 7) ||
           rn(0x0388, 0x038a) || rnd(0x038c, 0x038e, 2) ||
           rnd(0x038f, 0x0391, 2) || rn(0x0392, 0x03a1) ||
           rn(0x03a3, 0x03ab) || rnd(0x03cf, 0x03d2, 3) ||
           rn(0x03d3, 0x03d4) || rnd(0x03d8, 0x03ee, 2) ||
           rnd(0x03f4, 0x03f7, 3) || rn(0x03f9, 0x03fa) ||
           rn(0x03fd, 0x042f) || rnd(0x0460, 0x0480, 2) ||
           rnd(0x048a, 0x04c0, 2) || rnd(0x04c1, 0x04cd, 2) ||
           rnd(0x04d0, 0x052e, 2) || rn(0x0531, 0x0556) ||
           rn(0x10a0, 0x10c5) || rnd(0x10c7, 0x10cd, 6) ||
           rn(0x13a0, 0x13f5) || rnd(0x1e00, 0x1e94, 2) ||
           rnd(0x1e9e, 0x1efe, 2) || rn(0x1f08, 0x1f0f) ||
           rn(0x1f18, 0x1f1d) || rn(0x1f28, 0x1f2f) || rn(0x1f38, 0x1f3f) ||
           rn(0x1f48, 0x1f4d) || rnd(0x1f59, 0x1f5f, 2) ||
           rn(0x1f68, 0x1f6f) || rn(0x1fb8, 0x1fbb) || rn(0x1fc8, 0x1fcb) ||
           rn(0x1fd8, 0x1fdb) || rn(0x1fe8, 0x1fec) || rn(0x1ff8, 0x1ffb) ||
           rnd(0x2102, 0x2107, 5) || rn(0x210b, 0x210d) ||
           rn(0x2110, 0x2112) || rnd(0x2115, 0x2119, 4) ||
           rn(0x211a, 0x211d) || rnd(0x2124, 0x212a, 2) ||
           rn(0x212b, 0x212d) || rn(0x2130, 0x2133) || rn(0x213e, 0x213f) ||
           eq(0x2145) || rn(0x2160, 0x216f) || eq(0x2183) ||
           rn(0x24b6, 0x24cf) || rn(0x2c00, 0x2c2e) ||
           rnd(0x2c60, 0x2c62, 2) || rn(0x2c63, 0x2c64) ||
           rnd(0x2c67, 0x2c6d, 2) || rn(0x2c6e, 0x2c70) ||
           rnd(0x2c72, 0x2c75, 3) || rn(0x2c7e, 0x2c80) ||
           rnd(0x2c82, 0x2ce2, 2) || rnd(0x2ceb, 0x2ced, 2) || eq(0x2cf2) ||
           rnd(0xa640, 0xa66c, 2) || rnd(0xa680, 0xa69a, 2) ||
           rnd(0xa722, 0xa72e, 2) || rnd(0xa732, 0xa76e, 2) ||
           rnd(0xa779, 0xa77d, 2) || rnd(0xa77e, 0xa786, 2) ||
           rnd(0xa78b, 0xa78d, 2) || rnd(0xa790, 0xa792, 2) ||
           rnd(0xa796, 0xa7aa, 2) || rn(0xa7ab, 0xa7ad) ||
           rn(0xa7b0, 0xa7b4) || eq(0xa7b6) || rn(0xff21, 0xff3a) ||
           rn(0x010400, 0x010427) || rn(0x010c80, 0x010cb2) ||
           rn(0x0118a0, 0x0118bf) || rn(0x01d400, 0x01d419) ||
           rn(0x01d434, 0x01d44d) || rn(0x01d468, 0x01d481) ||
           rnd(0x01d49c, 0x01d49e, 2) || rnd(0x01d49f, 0x01d4a5, 3) ||
           rnd(0x01d4a6, 0x01d4a9, 3) || rn(0x01d4aa, 0x01d4ac) ||
           rn(0x01d4ae, 0x01d4b5) || rn(0x01d4d0, 0x01d4e9) ||
           rn(0x01d504, 0x01d505) || rn(0x01d507, 0x01d50a) ||
           rn(0x01d50d, 0x01d514) || rn(0x01d516, 0x01d51c) ||
           rn(0x01d538, 0x01d539) || rn(0x01d53b, 0x01d53e) ||
           rn(0x01d540, 0x01d544) || rnd(0x01d546, 0x01d54a, 4) ||
           rn(0x01d54b, 0x01d550) || rn(0x01d56c, 0x01d585) ||
           rn(0x01d5a0, 0x01d5b9) || rn(0x01d5d4, 0x01d5ed) ||
           rn(0x01d608, 0x01d621) || rn(0x01d63c, 0x01d655) ||
           rn(0x01d670, 0x01d689) || rn(0x01d6a8, 0x01d6c0) ||
           rn(0x01d6e2, 0x01d6fa) || rn(0x01d71c, 0x01d734) ||
           rn(0x01d756, 0x01d76e) || rn(0x01d790, 0x01d7a8) || eq(0x01d7ca) ||
           rn(0x01f130, 0x01f149) || rn(0x01f150, 0x01f169) ||
           rn(0x01f170, 0x01f189)));
    #undef eq
    #undef rn
    #undef rnd
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
        await -= 1;
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
        if (this->contents[i] != str.contents[i])
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
        if (this->contents[i] > str.contents[i])
            return false;
        if (this->contents[i] < str.contents[i])
            return true;
    }
    return this->length() < str.length();
}

bool us3::String::operator > (const us3::String& str) const
{
    int len = std::min(this->length(), str.length());
    for (int i = 0; i < len; i++) {
        if (this->contents[i] < str.contents[i])
            return false;
        if (this->contents[i] > str.contents[i])
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

us3::String us3::String::casefold(void) const
{
    return this->lower();
}

void us3::String::clear(void)
{
    this->contents.clear();
    return ;
}

int us3::String::count(const us3::String& pattern, int begin = 0,
                       int end = -1) const
{
    int length = this->length(), plen = pattern.length();
    if (plen == 0)
        return length + 1;  // This is a special case
    if (end == -1 || end >= length)
        end = length - 1;
    if (begin >= length || end < 0 || begin > end)
        return 0;
    int *next = pattern.find_kmp_get_next();
    int pos = 0, res = 0;
    while (pos <= end) {
        pos = this->find(pattern, next, pos);
        if (pos == -1 || pos + plen - 1 > end)
            break;
        res += 1;
        pos += plen;
    }
    delete next;
    return res;
}

bool us3::String::endswith(const us3::String& str) const
{
    int length = this->length(), slen = str.length();
    return slen <= length && this->substr(length - slen, length - 1) == str;
}

us3::String us3::String::expandtabs(int tabsize = 4) const
{
    us3::String result;
    int wpos = 0;
    for (us3::Char chr : this->contents) {
        if (chr == us3::Char('\r') || chr == us3::Char('\n')) {
            wpos = 0;
            result += chr;
        } else if (chr == us3::Char('\t')) {
            int dist = tabsize - wpos % tabsize;
            wpos += dist;
            result += us3::String(" ") * dist;
        } else {
            wpos += 1;
            result += chr;
        }
    }
    return result;
}

int* us3::String::find_kmp_get_next(void) const
{
    // This function requires destruction of array!
    int len = this->length();
    int *next = new int[len];
    next[0] = -1;
    for (int i = 1; i < len; i++) {
        for (int j = next[i - 1]; ; j = next[j]) {
            if (this->contents[j + 1] == this->contents[i]) {
                next[i] = j + 1;
                break;
            } else if (j == -1) {
                next[i] = -1;
                break;
            }
        }
    }
    return next;
}

int us3::String::find(const us3::String& pattern, int* next, int begin) const
{
    // Returns -1 if not found
    int len_main = this->length(), len_patt = pattern.length();
    int i = begin, j = 0;
    for (; i < len_main && j < len_patt; ) {
        if (this->contents[i] == pattern.contents[j]) {
            i += 1;
            j += 1;
        } else if (j == 0) {
            i += 1;
        } else {
            j = next[j - 1] + 1;
        }
    }
    if (j == len_patt)
        return i - len_patt;
    return -1;
}

int us3::String::find(const us3::String& pattern, int begin = 0) const
{
    // Returns -1 if not found
    if (begin + pattern.length() > this->length())
        return -1;
    int *next = pattern.find_kmp_get_next();
    int res = this->find(pattern, next, begin);
    delete next;
    return res;
}

int us3::String::find_first_of(const us3::Char& chr, int begin = 0) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->find_first_of(st, begin);
}

int us3::String::find_first_of(const us3::String& list, int begin = 0) const
{
    std::set<us3::Char> st;
    for (auto chr : list.contents)
        st.insert(chr);
    return this->find_first_of(st, begin);
}

int us3::String::find_first_of(const std::set<us3::Char>& list,
                               int begin = 0) const
{
    for (int i = std::max(begin, 0); i < this->length(); i++)
        if (list.find(this->contents[i]) != list.end())
            return i;
    return -1;
}

int us3::String::find_last_of(const us3::Char& chr, int end = -1) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->find_last_of(st, end);
}

int us3::String::find_last_of(const us3::String& list, int end = -1) const
{
    std::set<us3::Char> st;
    for (auto chr : list.contents)
        st.insert(chr);
    return this->find_last_of(st, end);
}

int us3::String::find_last_of(const std::set<us3::Char>& list,
                               int end = -1) const
{
    if (end == -1 || end >= this->length())
        end = this->length() - 1;
    for (int i = end; i >= 0; i--)
        if (list.find(this->contents[i]) != list.end())
            return i;
    return -1;
}

int us3::String::find_first_not_of(const us3::Char& chr, int begin = 0) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->find_first_not_of(st, begin);
}

int us3::String::find_first_not_of(const us3::String& list, int begin = 0) const
{
    std::set<us3::Char> st;
    for (auto chr : list.contents)
        st.insert(chr);
    return this->find_first_not_of(st, begin);
}

int us3::String::find_first_not_of(const std::set<us3::Char>& list,
                               int begin = 0) const
{
    for (int i = std::max(begin, 0); i < this->length(); i++)
        if (list.find(this->contents[i]) == list.end())
            return i;
    return -1;
}

int us3::String::find_last_not_of(const us3::Char& chr, int end = -1) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->find_last_not_of(st, end);
}

int us3::String::find_last_not_of(const us3::String& list, int end = -1) const
{
    std::set<us3::Char> st;
    for (auto chr : list.contents)
        st.insert(chr);
    return this->find_last_not_of(st, end);
}

int us3::String::find_last_not_of(const std::set<us3::Char>& list,
                               int end = -1) const
{
    if (end == -1 || end >= this->length())
        end = this->length() - 1;
    for (int i = end; i >= 0; i--)
        if (list.find(this->contents[i]) == list.end())
            return i;
    return -1;
}

us3::String us3::String::ljust(int len,
                               const us3::Char& chr = us3::Char(' ')) const
{
    int alen = this->length();
    if (len <= alen)
        return *this;
    return *this + us3::String(chr) * (len - alen);
}

us3::String us3::String::lower(void) const
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->contents[i];
        if (chr >= us3::Char('A') && chr <= us3::Char('Z'))
            chr = chr - us3::Char('A') + us3::Char('a');
        result += chr;
    }
    return result;
}

us3::String us3::String::lstrip(const us3::Char& chr) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->lstrip(st);
}

us3::String us3::String::lstrip(const us3::String& list) const
{
    std::set<us3::Char> st;
    for (auto i : list.contents)
        st.insert(i);
    return this->lstrip(st);
}

us3::String us3::String::lstrip(const std::set<us3::Char>& list) const
{
    int left = 0, right = this->length() - 1;
    while (left <= right) {
        if (list.find(this->contents[left]) == list.end())
            break;
        left += 1;
    }
    return this->substr(left, right);
}

#define us3_String_isfunc(__name__)    \
bool us3::String::__name__(void) const \
{                                      \
    if (this->length() == 0)           \
        return false;                  \
    for (auto chr : this->contents)    \
        if (!chr.__name__())           \
            return false;              \
    return true;                       \
}

us3_String_isfunc(isalnum);

us3_String_isfunc(isalpha);

us3_String_isfunc(isdecimal);

us3_String_isfunc(isdigit);

bool us3::String::islower(void) const
{
    int lo_cnt = 0, up_cnt = 0;
    for (auto chr : this->contents)
        if (chr.islower())
            lo_cnt += 1;
        else if (chr.isupper())
            up_cnt += 1;
    return lo_cnt >= 1 && up_cnt == 0;
}

us3_String_isfunc(isnumeric);

us3_String_isfunc(isspace);

bool us3::String::isupper(void) const
{
    int lo_cnt = 0, up_cnt = 0;
    for (auto chr : this->contents)
        if (chr.islower())
            lo_cnt += 1;
        else if (chr.isupper())
            up_cnt += 1;
    return up_cnt >= 1 && lo_cnt == 0;
}

#undef us3_String_isfunc

us3::String us3::String::join(const std::vector<us3::String>& list) const
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

us3::String us3::String::replace(const us3::String& pattern,
                                 const us3::String& replace,
                                 int count = 0) const
{
    // Leave count <= 0 to replace all occurences, elsewise replace the first
    // (count) occurences.
    std::vector<us3::String> parts = this->split(pattern);
    us3::String result = parts[0];
    for (int i = 1; i < parts.size(); i++) {
        if (count <= 0 || i <= count)
            result += replace + parts[i];
        else
            result += pattern + parts[i];
    }
    return result;
}

us3::String us3::String::reversed(void) const
{
    us3::String result;
    for (int i = this->length(); i >= 0; i--)
        result += this->contents[i];
    return result;
}

us3::String us3::String::rjust(int len,
                               const us3::Char& chr = us3::Char(' ')) const
{
    int alen = this->length();
    if (len <= alen)
        return *this;
    return us3::String(chr) * (len - alen) + *this;
}

us3::String us3::String::rstrip(const us3::Char& chr) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->rstrip(st);
}

us3::String us3::String::rstrip(const us3::String& list) const
{
    std::set<us3::Char> st;
    for (auto i : list.contents)
        st.insert(i);
    return this->rstrip(st);
}

us3::String us3::String::rstrip(const std::set<us3::Char>& list) const
{
    int left = 0, right = this->length() - 1;
    while (right >= left) {
        if (list.find(this->contents[right]) == list.end())
            break;
        right -= 1;
    }
    return this->substr(left, right);
}

std::vector<us3::String> us3::String::split(const us3::String& pattern) const
{
    std::vector<us3::String> result;
    int length = this->length(), plen = pattern.length();
    if (plen == 0)
        return result;  // In Python this should throw an exception instead
    int *next = pattern.find_kmp_get_next();
    int pos = 0, last_pos = 0;
    while (pos < length) {
        pos = this->find(pattern, next, pos);
        if (pos == -1)
            break;
        result.push_back(this->substr(last_pos, pos - 1));
        pos += plen;
        last_pos = pos;
    }
    result.push_back(this->substr(last_pos, length - 1));
    delete next;
    return result;
}

bool us3::String::startswith(const us3::String& str) const
{
    int length = this->length(), slen = str.length();
    return slen <= length && this->substr(0, slen - 1) == str;
}

us3::String us3::String::strip(const us3::Char& chr) const
{
    std::set<us3::Char> st;
    st.insert(chr);
    return this->strip(st);
}

us3::String us3::String::strip(const us3::String& list) const
{
    std::set<us3::Char> st;
    for (auto i : list.contents)
        st.insert(i);
    return this->strip(st);
}

us3::String us3::String::strip(const std::set<us3::Char>& list) const
{
    int left = 0, right = this->length() - 1;
    while (left <= right) {
        if (list.find(this->contents[left]) == list.end())
            break;
        left += 1;
    }
    while (right >= left) {
        if (list.find(this->contents[right]) == list.end())
            break;
        right -= 1;
    }
    return this->substr(left, right);
}

us3::String us3::String::substr(int begin, int end) const
{
    if (this->length() == 0 || end < begin)
        return us3::String();
    begin = std::max(std::min(begin, int(this->length()) - 1), 0);
    end = std::max(std::min(end, int(this->length()) - 1), 0);
    us3::String result;
    result.contents = this->contents.substr(begin, end - begin + 1);
    return result;
}

us3::String us3::String::swapcase(void) const
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->contents[i];
        if (chr >= us3::Char('a') && chr <= us3::Char('z'))
            chr = chr - us3::Char('a') + us3::Char('A');
        else if (chr >= us3::Char('A') && chr <= us3::Char('Z'))
            chr = chr - us3::Char('A') + us3::Char('a');
        result += chr;
    }
    return result;
}

us3::String us3::String::upper(void) const
{
    us3::String result;
    for (int i = 0; i < this->length(); i++) {
        us3::Char chr = this->contents[i];
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
    using namespace us3;
    cout << String("Ab1.").isalnum() << endl;
    return 0;
}
