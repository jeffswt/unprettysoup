
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
    return this->islower() || this->isupper();
}

bool us3::Char::isdecimal(void) const
{
    return this->value >= '0' && this->value <= '9';
}

bool us3::Char::isdigit(void) const
{
    return this->isdecimal();
}

bool us3::Char::islower(void) const
{
    return this->value >= 'a' && this->value <= 'z';
}

bool us3::Char::isnumeric(void) const
{
    return this->isdecimal();
}

bool us3::Char::isspace(void) const
{
    // This method is Unicode safe.
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
    return this->value >= 'A' && this->value <= 'Z';
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
    String a = "abcd\tdef\nabcdef\tgh", b = "a";
    cout << a.expandtabs() << endl;
    return 0;
}
