# Unpretty Soup

Unpretty Soup is a C++ library for pulling data out of HTML files. It works individually with its **own Unicode (UTF-8) solution** and its **own parser**, to provide simple ways of navigating, searching, <del>and modifying</del> the parsed DOM tree. It commonly saves CS students and programmers days or weeks of work.

These instructions illustrate all major (used) features of Unpretty Soup 3, with examples. We will show you what the library is good for, how to use it, how to make it do what you want, and how to keep using it when it violates your expectations.

The examples in this documentation should work the same way in C++11.

You might be looking for the documentation for [Beautiful Soup 4](https://www.crummy.com/software/BeautifulSoup/bs4/doc/). If so, you should know that Unpretty Soup is not always being developed, and that using Python for crawler / analysis projects is recommended. In fact, Unpretty Soup is designed in a way that resembles Beautiful Soup 4 as much as possible. *If you insist on using C++ for your crawler projects, you may consider consulting a doctor for probable masochism tendencies.*

This documentation has **not** been translated into other languages by Unpretty Soup users:

* 这篇文档当然没有中文版。
* このページは日本語で利用できません。

### Getting help

If you have questions about Unpretty Soup, or run into problems, consider the [Issues](https://github.com/jeffswt/unprettysoup/issues) section. If your problem involves parsing an HTML document, be sure to check if your HTML is right. We've done everything to parse as much as we can, unless your document is too badly-formed.

## Quick Start

Here's an HTML document I'll be using as an example throughout this document. It's part of a story telling how ruo jeffswt is.

```HTML
<html><head><title>The Juruo's story</title></head>
<body>
<p class="title"><b>The Juruo's story</b></p>

<p class="story">Once upon a time there were three little juruos; and their names were
<a href="http://example.com/jeffswt" class="juruo" id="link1">jeffswt</a>,
<a href="http://example.com/swt" class="juruo" id="link2">swt</a> and
<a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>;
and they always fail exams.</p>

<p class="story">...</p>
</body></html>
```

Running the "three juruos" document through Unpretty Soup gives us a `Element*` pointer / object, which represents the document as a nested data structure.

```C++
#include <unprettysoup.h>
auto soup = UnprettySoup(html_doc);
```

Here are some simple ways to navigate that data structure:

```C++
soup->find("title");
// <title> The Juruo's story</title>

soup->find("title")->name;
// title

soup->find("title")->string()->content;
// The Juruo's story

soup-->find("title")->parent()->name;
// head

soup->find("p");
// <p class="title"><b>The Juruo's story</b></p>

soup->find("p")->attrs["class"];
// title

soup->find("a");
// <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>

soup->find_all("a");
// [<a href="http://example.com/jeffswt" class="juruo" id="link1">jeffswt</a>,
//  <a href="http://example.com/swt" class="juruo" id="link2">swt</a>,
//  <a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>]

map<String, String> mp;
mp["id"] = "link3";
soup->find(mp);
// <a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>
```

One common task is extracting all the URLs found within a page's `<a>` tags:

```C++
for (auto link : soup->find_all("a"))
    cout << link->get_attr("href") << endl;
// http://exammple.com/jeffswt
// http://exammple.com/swt
// http://exammple.com/juruoswt
```

## Installing Unpretty Soup

Unpretty Soup is designed to use as fewer dependencies as possible, so it relies only on a C++11 compiler, and no other dependencies (except for STL, though).

Copy `unprettysoup.cpp` and `unprettysoup.h` to your project directory or project include directory. Include the header and compile the source codes separately, then you have a pretty soup.

```bash
g++ my_code.cpp -c -o my_code.o
g++ unprettysoup.cpp -c -o unprettysoup.o
g++ my_code.o unprettysoup.o -o my_code.out
./my_code.out
```

Note that you may want to ignore the `us3` namespace like this:

```C++
#include <unprettysoup.h>
using namespace std;
using namespace us3;
```

## Making the soup

To parse a document, pass it into the `UnprettySoup` function. You can pass in a string or an open input stream:

```C++
ifstream fin("index.html");
auto soup = UnprettySoup(fin);
fin.close();
delete soup;
soup = UnprettySoup("<html>data</html>");
```

## Kinds of objects

To ensure proper Unicode support under C++ (which doesn't have a lite solution for Unicode support, and doesn't have native support either), Unpretty Soup defined a series of convenient types to handle Unicode data in an easier way, and functions similarly to Python.

### Char

A `Char` is effectively an alias of `unsigned int`, and takes the same amount of memory. It consumes 4 times more memory than a typical single-width `char`, which only has 8 bits (and `Char` consumes 32 bits).

#### Converting between Unicode and raw

You can convert a STL string into a Char object, and acknowledge how many bytes have been parsed, like this:

```C++
std::string unicode_str = "苟利...";
cout << unicode_str.length() << endl;  // 9
int pos = 0;
us3::Char chr(unicode_str, pos);
cout << "Consumed " << pos - 0 << " bytes\n";  // Consumed 3 bytes
```

Which is equivalent to:

```C++
chr.from_string(unicode_str, pos);
```

And you can have multiple ways to display it or convert it back to raw data:

```C++
std::string chr_raw = chr.to_string();
cout << chr_raw << endl;  // 苟
cout << chr << endl;  // 苟
```

C++ input streams are also supported:

```C++
cin >> chr;
```

#### Initialize from values

`Char` object also accepts initialization with values, namely `char` and `unsigned int`. Note that you should only pass values within `0x00` and `0x10ffff` in. It should write like this:

```C++
us3::Char c1 = '#',
          c2 = 97,  // 'a'
		 c3 = (unsigned int)(0x5229);  // '利'
```

#### Comparing and calculating

The `Char` object supports all 6 comparative operators (`<`, `>`, `<=`, `>=`, `==`, `!=`) and 4 manipulative operators (`+`, `+=`, `-`, `-=`).

#### Determining type

Please refer to the same section in `String` objects.

### String

A `String` is effectively an superset of `std::basic_string<us3::Char>`, which is yet another `std::string` with `us3::Char`s in it instead of `char`s. Most `std::string` functions are implemented, some in a more efficient manner, but you might want to look into some of the more convenient methods that are exclusively available in `us3::String`.

#### Converting between Unicode and raw

You can use `.from_string()`, `.to_string()` and stream operators like you can in `Char`. They look pretty much like this:

```C++
us3::String s1;
s1.to_string("国家");
us3::String s2 = "生";
cout << s1.to_string() << endl;  // 国家
cout << s2 << endl;  // 生
cin >> s2;
```

You can initialize a `String` object from one of the following types: `std::string`, `char*`, `const char*` and `Char`.

#### Comparing and examining

Like `std::string`, `String` also has the following operators or methods: `.length()`, `operator []`, `<`, `>`, `<=`, `>=`, `==`, `!=`, `+`, `+=`.

However, after comparing with Python we added two more operators, `*` and `*=`. They are to be processed in a way like this:

```C++
us3::String str = "蛤";
str *= 2;
cout << str * 2 << endl;  // "蛤蛤蛤蛤"
cout << str << endl;  // "蛤蛤"
```

#### Other functions

You can consult the C++ reference and Python help for detailed documentation. They will provide you with proper support. This section might be updated in the near future.

Now Unpretty Soup has a pretty decent Unicode support in C++, we can transform the HTML document into a tree of objects. Now you'll only ever have to deal with one kind of object: `Element`, which has four subtypes: `Tag`, `NavigableString`, `Comment` and `Doctype`.

### Tag

A `Tag` object corresponds to an HTML tag in the original document:

```C++
auto soup = UnprettySoup("<b class=\"boldest\">Extremely bold</b>");
auto tag = soup->find("b");
// <class 'us3::Element'>
```

Tags have a lot of attributes and methods, and I'll cover most of them in Navigating the tree and Searching the tree. For now, the most important features of a tag are its name and attributes.

#### Name

Every tag has a name, accessible by `.name`.

```C++
cout << tag->name << endl;
// "b"
```

If you change a tag's name, the change will be reflected in any HTML markup generated by Unpretty Soup.

```C++
tag->name = "blockquote";
cout << tag << endl;
// <blockquote class="boldest">Extremely bold</blockquote>
```

#### Attributes

A tag may have any number of attributes. The tag `<b id="boldest">` has an attribute "id" whose value is "boldest". You can access a tag's attributes by accessing the map as `.attrs`:

```C++
tag->attrs;
// {"id": "boldest"}
```

You can add, remove, get and modify a tag's attributes. You can directly access it, however an easier way is done by calling these methods:

```C++
tag->set_attr("id", "verybold");
tag->attrs["another-attribute"] = "1";
cout << tag << endl;
// <b another-attribute="1" id="verybold"></b>

tag->del_attr("id");
tag->attrs.erase("another-attribute");
cout << tag << endl;
// <b></b>

cout << tag->has_attr("id") << endl;
// false
cout << tag->get_attr("id") << endl;
// ""
```

#### NavigableString

A string corresponds to a bit of text within a tag. Unpretty Soup uses the `NavigableString` subtype to contain these text:

```C++
tag->string();
// "Extremely bold"
cout << tag->type == NavigableString << endl;
// true
```

A `NavigableString` is effectively a container of a `String`, except that it does not support some of the features `Tag` does (you can use them, though, it's just that they don't return anything useful). You can retrieve and modify its contents by accessing its `.contents`:

```C++
cout << tag->string()->content << endl;
// Extremely bold
tag->string()->content = "No longer bold";
cout << tag << endl;
// <blockquote>No longer bold</blockquote>
```

#### Top-level tag

The highest-level tag looks like every other tag, except its name is `[document]`.

#### Doctype

The access methods of a `Doctype` element works the way `NavigableString` does. You can access the data inside that tag with `.content`:

```C++
auto soup = UnprettySoup("<!DOCTYPE html PUBLIC><html></html>");
auto tag = soup->children()[0];
cout << tag->name << endl;
// [doctype]
cout << tag->content << endl;
// html PUBLIC
```

#### Comment

`Tag` and `NavigableString` cover almost everything you'll see in an HTML file, but there are a few leftover bits. The only one you'll probably ever need to worry about is the comment:

```C++
auto soup = UnprettySoup("<b><!-- Comments, comments --></b>");
auto comments = soup->find("b")->children[0];
cout << comments->type == Comment << endl;
// true
```

You can access / modify its contents like you can in `NavigableString`s:

```C++
cout << comments->content << endl;
// Comments, comments
```

## Navigating the tree

### Going down

Tags may contain strings and other tags. These elements are the tag's *children*. Unpretty Soup provides a lot of different methods for navigating and iterating over a tag's children.

Note that Unpretty Soup strings don't support any of these methods (though you can call them, you can't actually get anything useful), because a string can't have children.

#### Navigating using tag names

The simplest way to navigate the parse tree is to say the name of the tag you want. If you want the `<head>` tag, just say `soup->find("head")` (in fact we can't implement it the way Beautiful Soup does, due to the *static* nature of C++):

```C++
soup->find("head");
// <head><title>The Juruo's story</title></head>
soup->find("title");
// <title>The Juruo's story</title>
```

You can do use this trick again and again to zoom in on a certain part of the parse tree. This code gets the first `<b>` tag beneath the `<body>` tag:

```C++
soup->find("body")->find("b");
// <b>The Juruo's story</b>
```

Using the tag name with `.find()` will give you only the first tag by that name:

```C++
soup->find("a");
// <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>
```

If you need to get all the `<a>` tags, or anything more complicated than the first tag with a certain name, you'll need to use one of the methods described in Searching the tree, such as `.find_all()`:

```C++
soup->find_all("a");
// [<a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>,
//  <a class="juruo" href="http://example.com/swt" id="link2">swt</a>,
//  <a class="juruo" href="http://example.com/juruoswt" id="link3">juruoswt</a>]
```

#### .contents() and .children()

A tag's children are available in a vector called `.contents()`:

```C++
auto head_tag = soup->find("head");
// <head><title>The Juruo's story</title></head>

head_tag->contents();
// [<title>The Juruo's story</title>]

auto title_tag = head_tag->contents()[0];
// <title>The Juruo's story</title>
title_tag->contents();
// ["The Juruo's story"]
```

The highest-level tag itself has children. In this case, the `<!DOCTYPE>` tag and the `<html>` tag are children of that tag:

```C++
soup->contents();
// 1 or 2, depending if there's a <!DOCTYPE> or not, 1 in the example
soup->contents[0]->name;
// "html"
```

A string has empty `.contents()`, because it doesn't contain anything:

```C++
auto text = title_tag->contents()[0];
text->contents();
// []
```

The `.children()` method is an alias of `.contents()` (We didn't even try to implement a generator, though).

Under Unpretty Soup's implementation, any two adjacent `Tag`s have one and only one `NavigableString` in between. If that certain string is empty, it would not be considered visible by default. If you insisting on displaying that empty string, you may specify a parameter `show_empty_strings=true` like this:

```C++
for (auto child : head_tag->contents(true))
    cout << child->repr() << endl;
// ""
// <title>The Juruo's story</title>
// ""
```

#### .descendants()

The `.contents()` and `.children()` methods only consider a tag's *direct* children. For instance, the `<head>` tag has a single direct child - the `<title>` tag:

```C++
head_tag->contents();
// [<title>The Juruo's story</title>]
```

But the `<title>` tag itself has a child: the string "The Juruo's story". There's a sense in which that string is also a child of the `<head>` tag. The `.descendants()` method lets you iterate over all of a tag's children, recursively: its direct children, the children of its direct children, and so on:

```C++
for (auto child : head_tag->descendants())
    cout << child->repr() << endl;
// <title>The Juruo's story</title>
// "The Juruo's story"
```

The `<head>` tag has only one child, but it has two descendants: the `<title>` tag and the `<title>` tag's child. The highest-level tag only has one (or two?) direct child (-ren) (the `<html>` tag), but it has a whole lot of descendants:

```C++
soup->children().length();
// 1
soup->descendants().length();
// Something around 25
```

#### .string()

If a tag has only one child, and that child is a `NavigableString`, the child is made available as `.string()`:

```C++
title_tag->string();
// "The Juruo's story"
```

If a tag's only child is another tag, and that tag has a `.string()`, then the parent tag is considered to have the same `.string()` as its child:

```C++
head_tag->contents();
// [<title>The Juruo's story</title>]

head_tag->string();
// "The Juruo's story"
```

If a tag contains more than one thing, then it's not clear what `.string()` should refer to, so `.string()` is defined to be an empty string:

```C++
cout << soup->find("html")->string() << endl;
// ""
```

#### .strings() and .stripped_strings()

If there's more than one thing inside a tag, you can still look at just the strings. Use the `.strings()` method. The method yields a vector of `NavigableString`s, where you can edit them:

```C++
for (Element* str : soup->strings())
    cout << str->repr() << endl;
// "The Juruo's story"
// "\n\n"
// "The Juruo's story"
// "\n\n"
// "Once upon a time there were three little juruos; and their names were\n"
// "jeffswt"
// ",\n"
// "swt"
// " and\n"
// "juruoswt"
// ";\nand they always fail exams."
// "\n\n"
// "..."
// "\n"
```

Like `.children()`, you may specify `show_empty_strings=true` to display all hidden strings, like:

```C++
for (Element* str : soup->strings(true))
    cout << str->repr() << endl;
// Too many lines, didn't bother to enumerate
```

These strings tend to have a lot of extra whitespace, which you can remove by using the `.stripped_strings()` method instead (however this method returns a vector of strings, not of `NavigableString`s):

```C++
for (String str : soup->stripped_strings())
    cout << str << endl;
// "The Juruo's story"
// "The Juruo's story"
// "Once upon a time there were three little juruos; and their names were"
// "jeffswt"
// ","
// "swt"
// "and"
// "juruoswt"
// ";\nand they always fail exams."
// "..."
```

Here, strings consisting entirely of whitespace are ignored, and whitespace at the beginning and end of strings is removed.

### Going up

Continuing the "family tree" analogy, every tag and every string has a *parent*: the tag that contains it.

#### .parent()

You can access an element's parent with the `.parent()` method. In the example "three juruo" document, the `<head>` tag is the parent of the `<title>` tag:

```C++
auto title_tag = soup->find("title");
// <title>The Juruo's story</title>
title_tag->parent();
// <head><title>The Juruo's story</title></head>
```

The title string itself has a parent: the `<title>` tag that contains it:

```C++
title_tag->find("[string]")->parent();
// <title>The Juruo's story</title>
```

The parent of a top-level tag like `<html>` is the highest-level tag itself:

```C++
auto html_tag = soup->find("html");
html_tag->parent()->name;
// [document]
```

And the `.parent()` of the highest-level tag is defined as a null pointer:

```C++
soup->parent();
// nullptr
```

#### .parents()

You can iterate over all of an element's parents with `.parents()`. This example uses `.parents()` to travel from an `<a>` tag buried deep within the document, to the very top of the document:

```C++
auto link = soup->find("a");
// <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>
for (auto parent : link->parents()) {
    if (parent == nullptr)
        cout << "nullptr\n";
    else
        cout << parent->name << "\n";
}
// p
// body
// html
// [document]
// nullptr
```

### Going sideways

Consider a simple document like this:

```C++
auto sibling_soup = UnprettySoup("<a><b>text1</b><c>text2</c></b></a>")
cout << sibling_soup->prettify();
// <html>
//  <body>
//   <a>
//    <b>
//     text1
//    </b>
//    <c>
//     text2
//    </c>
//   </a>
//  </body>
// </html>
```

The `<b>` tag and the `<c>` tag are at the same level: they're both direct children of the same tag. We call them *siblings*. When a document is pretty-printed, siblings show up at the same indentation level. You can also use this relationship in the code you write.

#### .next_sibling() and .previous_sibling()

You can use `.next_sibling()` and `.previous_sibling()` to navigate between page elements that are on the same level of the parse tree:

```C++
sibling_soup->find("b")->next_sibling();
// <c>text2</c>
sibling_soup->find("c")->previous_sibling();
// <b>text1</b>
```

The `<b>` tag has a `.next_sibling()`, but no `.previous_sibling()`, because there's nothing before the `<b>` tag on the same level of the tree. For the same reason, the `<c>` tag has a `.previous_sibling()` but no `.next_sibling()`:

```C++
sibling_soup->find("b")->previous_sibling();
// nullptr
sibling_soup->find("c")->next_sibling();
// nullptr
```

The strings "text1" and "text2" are not siblings, because they don't have the same parent:

```C++
sibling_soup->find("b")->find("[string]");
// text1
sibling_soup->find("b")->find("[string]")->next_sibling();
// nullptr, not text2
```

In real documents, the `.next_sibling()` or `.previous_sibling()` of a tag will usually be a string containing whitespace. Going back to the "three juruos" document:

```html
<a href="http://example.com/jeffswt" class="juruo" id="link1">jeffswt</a>
<a href="http://example.com/swt" class="juruo" id="link2">swt</a>
<a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>
```

You might think that the `.next_sibling()` of the first `<a>` tag would be the second `<a>` tag. But actually, it's a string: the comma and newline that separate the first `<a>` tag from the second:

```C++
auto link = soup->find("a");
// <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>
link->next_sibling();
// ",\n"
```

The second `<a>` tag is actually the `.next_sibling()` of the comma:

```C++
link->next_sibling()->next_sibling();
// <a class="juruo" href="http://example.com/swt" id="link2">swt</a>
```

#### .next_siblings() and .previous_siblings()

You can iterate over a tag's siblings with `.next_siblings()` or `.previous_siblings()`:

```C++
for (auto sibling : soup->find("a")->next_siblings())
    cout << sibling->repr() << "\n";
// ",\n"
// <a class="juruo" href="http://example.com/swt" id="link2">swt</a>
// " and\n"
// <a class="juruo" href="http://example.com/juruoswt" id="link3">juruoswt</a>
// "; and they always fail exams."
// nullptr

// for (auto sibling : soup->find(id="link3")->previous_siblings())
//     cout << sibling->repr() << "\n";
// " and\n"
// <a class="juruo" href="http://example.com/swt" id="link2">swt</a>
// ",\n"
// <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>
// "Once upon a time there were three little juruos; and there names were\n"
// nullptr
```

## Searching the tree

Unpretty Soup defines a lot of methods for searching the parse tree, but they're all very similar. I'm going to spend a lot of time explaining the two most popular methods: `.find()`and `.find_all()`. The other methods (which are available in Beautiful Soup) take almost exactly the same arguments, but as they don't exist I won't cover them.

Once again, I'll be using the "three juruos" document as an example.

### Kinds of filters

Before talking in detail about `.find_all()` and similar methods, I want to show examples of different filters you can pass into these methods. These filters show up again and again, throughout the search API. You can use them to filter based on a tag's name, on its attributes, on the text of a string, or on some combination of these.

#### A string

The simplest filter is a string. Pass a string to a search method and Unpretty Soup will perform a match against that exact string. This code finds all the `<b>` tags in the document:

```C++
soup->find_all("b");
// [<b>The Juruo's story</b>]
```

#### A list

If you pass in a list, Unpretty Soup will allow a string match against any item in that list. This code finds all the `<a>` tags and all the `<b>` tags:

```C++
vector<String> vec;
vec.push_back("a");
vec.push_back("b");
soup->find_all(vec);
// [<b>The Juruo's story</b>,
//  <a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>,
//  <a class="juruo" href="http://example.com/swt" id="link2">swt</a>,
//  <a class="juruo" href="http://example.com/juruoswt" id="link3">juruoswt</a>]
```

#### A set

If you pass in a set, Unpretty Soup will allow a string match against any item in that set. This code functions the same as the previous example:

```C++
set<String> st;
st.insert("a");
st.insert("b");
soup->find_all(st);
// Result all the same as previous
```

#### True

Passing nothing into it matches everything it can. This code finds all the tags in the document, but none of the text strings:

```C++
for (auto tag : soup->find_all())
    cout << tag->name << endl;
// [document]
// html
// head
// title
// ...and many more
```

#### A function

If none of the other matches work for you, define a function that takes an element as its only argument. The function should return `true` if the argument matches, and `false`otherwise.

Here's a function that returns `true` if a tag defines the "class" attribute but doesn't define the "id" attribute:

```C++
#include <functional>
auto has_class_but_no_id = [](Element* tag) {
    return tag->has_attr("class") && !tag->has_attr("id");
};
```

Pass this function into `.find_all()` and you'll pick up all the `<p>` tags:

```C++
soup->find_all(has_class_but_no_id);
// [<p class="title"><b>The Juruo's story</b></p>,
//  <p class="story">Once upon a time there were...</p>,
//  <p class="story">...</p>]
```

This function only picks up the `<p>` tags. It doesn't pick up the `<a>` tags, because those tags define both "class" and "id". It doesn't pick up tags like `<html>` and `<title>`, because those tags don't define "class".

The function can be as complicated as you need it to be.

Now we're ready to look at the search methods in detail.

### Methods

#### .find_all()

Definition: find_all(name, attrs, recursive, limit)

The `.find_all()` method looks through a tag's descendants and retrieves all descendants that match your filters. I gave several examples in Kinds of filters, but here are a few more:

```C++
soup->find_all("title");
// [<title>The Juruo's story</title>]

map<String, String> mp;
mp["class"] = "title";
soup->find_all("p", mp);
// [<p class="title"><b>The Juruo's story</b></p>]

soup->find_all("a");
// [<a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>,
//  <a class="juruo" href="http://example.com/swt" id="link2">swt</a>,
//  <a class="juruo" href="http://example.com/juruoswt" id="link3">juruoswt</a>]

mp.clear();
mp["id"] = "link2";
soup->find_all(mp);
// [<a class="juruo" href="http://example.com/swt" id="link2">swt</a>]
```

Some of these should look familiar, but others are new. You may not understand all of them, so let's look at the arguments to `find_all()`.

##### The `name` argument

Pass in a value for `name` and you'll tell Unpretty Soup to only consider tags with certain names. Text strings will be ignored, as will tags whose names that don't match.

This is the simplest usage:

```C++
soup->find_all("title");
// [<title>The Juruo's story</title>]
```

Recall from Kinds of filters that the value to `name` can be a string, a list, a set, a function or nothing at all.

##### The `attrs` / keywords argument

You can filter tags by putting rules into a `map<String, String>` object. If you pass in a value for a rule describing limitations on `id`, Unpretty Soup will filter against each tag's 'id' attribute.

```C++
map<String, String> mp;
mp["id"] = "link2";
soup->find_all(mp);
// [<a class="juruo" href="http://example.com/swt" id="link2">swt</a>]
```

You can filter an attribute based on strings.

You can filter multiple attributes at once by passing in more than one keyword argument:

```C++
mp.clear();
mp["id"] = "link1";
mp["a"] = "http://example.com/jeffswt";
soup->find_all(mp);
// [<a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>]
```

Some attributes, like the `data-*` attributes in HTML 5, have names that can't be used as the names of keyword arguments. Unlike Beautiful Soup that can take in keyword arguments, Unpretty Soup takes only `map` objects, so that doesn't pose a problem.

```C++
auto data_soup = UnprettySoup("<div data-foo=\"value\">foo!</div>");
mp.clear();
mp["data-foo"] = "value";
data_soup->find_all(mp);
// [<div data-foo="value">foo!</div>]
```

##### Searching by CSS class

It's very useful to search for a tag that has a certain CSS class. You can search by CSS class using the keyword argument `class`, and pass it into the `attr` parameter:

```C++
map<String, String> mp;
mp["class"] = "juruo";
soup->find_all("a", mp);
// [<a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>,
//  <a class="juruo" href="http://example.com/swt" id="link2">swt</a>,
//  <a class="juruo" href="http://example.com/juruoswt" id="link3">juruoswt</a>]
```

Remember that a single tag can have multiple values for its "class" attribute. When you search for a tag that matches a certain CSS class, you're matching against any of its CSS classes:

```C++
auto css_soup = UnprettySoup("<p class=\"body strikeout\"></p>");
mp.clear();
mp["class"] = "strikeout";
css_soup->find_all("p", mp);
// [<p class="body strikeout"></p>]

mp["class"] = "body";
css_soup->find_all("p", mp);
// [<p class="body strikeout"></p>]
```

You can also search for the exact string value of the `class` attribute:

```C++
mp["class"] = "body strikeout";
css_soup->find_all("p", mp);
// [<p class="body strikeout"></p>]
```

Unlike Beautiful Soup (which returns `[]` in the following example), searching for variants of the string value will also work. Thus you can search for tags that match two or more CSS classes, without requirements of order:

```C++
mp["class"] = "strikeout body";
css_soup->find_all("p", mp);
// [<p class="body strikeout"></p>]
```

##### The `recursive` argument

If you call `mytag->find_all()`, Unpretty Soup will examine all the descendants of `mytag`: its children, its children's children, and so on. If you only want to consider direct children, you can pass in `recursive=False`. See the difference here:

```C++
soup->find("html")->find_all("title");
// [<title>The Juruo's story</title>]

soup->find("html")->find_all("title", false);
// []
```

Here's that part of the document:

```HTML
<html>
 <head>
  <title>
   The Juruo's story
  </title>
 </head>
...
```

The `<title>` tag is beneath the `<html>` tag, but it's not directly beneath the `<html>` tag: the `<head>` tag is in the way. Unpretty Soup finds the `<title>` tag when it's allowed to look at all descendants of the `<html>` tag, but when `recursive=False` restricts it to the `<html>` tag's immediate children, it finds nothing.

##### The `limit` argument

`.find_all()` returns all the tags and strings that match your filters. This can take a while if the document is large. If you don't need all the results, you can pass in a number for `limit`. This works just like the LIMIT keyword in SQL. It tells Unpretty Soup to stop gathering results after it's found a certain number.

There are three links in the "three juruos" document, but this code only finds the first two:

```C++
soup->find_all("a", map<String, String>(), true, 2);
// attrs = {}, recursive = true, limit = 2
// [<a class="juruo" href="http://example.com/jeffswt" id="link1">jeffswt</a>,
//  <a class="juruo" href="http://example.com/swt" id="link2">swt</a>]
```

#### .find()

Definition: find(name, attrs, recursive);

The `.find_all()` method scans the entire document looking for results, but sometimes you only want to find one result. If you know a document only has one `<body>` tag, it's a waste of time to scan the entire document looking for more. Rather than passing in `limit=1` every time you call `.find_all()`, you can use the `.find()` method. These two lines of code are nearly equivalent:

```C++
soup->find_all("title", map<String, String>(), true, 1);
// [<title>The Juruo's story</title>]

soup->find("title");
// <title>The Juruo's story</title>
```

The only difference is that `.find_all()` returns a list containing the single result, and `.find()` just returns the result.

If `.find_all()` can't find anything, it returns an empty list. If `.find()` can't find anything, it returns `nullptr`:

```C++
soup->find("nosuchtag");
// nullptr
```

#### .find_all_s()

Definition: find_all_s(pattern, recursive, limit)

The `.find_all()` method scans the entire document for tags, but sometimes you want to search for strings. It's a waste of time iterating the whole `.descendants()` just to find something, so there's a simple approach for this task.

Recall from Kinds of filters, and similar to it, the value to `pattern` can be a string, a list, a set or a function. Different from it, the `pattern` functions in a way that matches a substring of the current `NavigableString`, instead of comparing to it. That is, with a `pattern="a"`, the main string `"ab"` would be considered as a match.

You may pass a function into `.find_all_s()`, only with different parameters (It should still return `true` for strings that it wish to keep and vice versa):

```C++
#include <functional>
auto length_longer_than_zero = [](String str) {
    return str.length() > 0;
};
```

The other parameters (`recursive` and `limit`) functions the way as `.find_all()` does.

#### .find_s()

Definition: find_s(pattern, recursive)

The relationship between `.find_s()` and `.find_all_s()` is the same as that between `.find()` and `.find_all()`. Rather than passing in `limit=1` every time you call `.find_all_s()`, you can use the `.find_s()` method. These two lines of code are nearly equivalent:

```C++
soup->find_all_s("Juruo", true, 1);
// ["The Juruo's story"]

soup->find_s("Juruo");
// "The Juruo's story"
```

They differ in a similar manner to `.find()` and `.find_all()`. For details, consult the previous section.

## Modifying the tree

As this project is initially intended for crawling webpages, tree modification methods are not currently available.

## Output

...

## Encodings

You should preferrably and only use UTF-8 as your encoding.

If your document is not, convert it to UTF-8 before you use.

## Troubleshooting

You must know that Unpretty Soup is expected to parse as many tags and accept as many non-standard webpages as it could. Therefore, Unpretty Soup is not designed to be fully conforming to HTML 5.3 standard section 8.2. You must bear in mind that results may sometimes vary minorly yet trivial.

As for performance issues, you might consider switching to Beautiful Soup 4 on Python, lxml on Python or other parsing libraries for C++.

## Contribution

You can fork a new branch on GitHub and make pull requests. We are open to contributions and are welcome to new features.

## License

```
MIT License

Copyright (c) 2019 Geoffrey Tang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

