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

Here’s an HTML document I’ll be using as an example throughout this document.

```HTML
<html><head><title>The Juruo's story</title></head>
<body>
<p class="title"><b>The Juruo's story</b></p>

<p class="story">Once upon a time there were three little juruos; and there names were
<a href="http://example.com/jeffswt" class="juruo" id="link1">jeffswt</a>,
<a href="http://example.com/swt" class="juruo" id="link2">swt</a> and
<a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>; and they always fail exams.</p>

<p class="story">...</p>
</body></html>
```

## Installing Unpretty Soup

## Making the soup

## Kinds of objects

### Char

### String

### Element

## Navigating the tree

### Going down

### Going up

Continuing the “family tree” analogy, every tag and every string has a *parent*: the tag that contains it.

#### .parent()

You can access an element’s parent with the `.parent()` method. In the example “three sisters" document, the `<head>` tag is the parent of the `<title>` tag:

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

You can iterate over all of an element’s parents with `.parents()`. This example uses `.parents()` to travel from an `<a>` tag buried deep within the document, to the very top of the document:

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

The `<b>` tag and the `<c>` tag are at the same level: they’re both direct children of the same tag. We call them *siblings*. When a document is pretty-printed, siblings show up at the same indentation level. You can also use this relationship in the code you write.

#### .next_sibling() and .previous_sibling()

You can use `.next_sibling()` and `.previous_sibling()` to navigate between page elements that are on the same level of the parse tree:

```C++
sibling_soup->find("b")->next_sibling();
// <c>text2</c>
sibling_soup->find("c")->previous_sibling();
// <b>text1</b>
```

The `<b>` tag has a `.next_sibling()`, but no `.previous_sibling()`, because there’s nothing before the `<b>` tag on the same level of the tree. For the same reason, the `<c>` tag has a `.previous_sibling()` but no `.next_sibling()`:

```C++
sibling_soup->find("b")->previous_sibling();
// nullptr
sibling_soup->find("c")->next_sibling();
// nullptr
```

The strings “text1” and “text2” are not siblings, because they don’t have the same parent:

```C++
sibling_soup->find("b")->find("[string]");
// text1
sibling_soup->find("b")->find("[string]")->next_sibling();
// nullptr, not text2
```

In real documents, the `.next_sibling` or `.previous_sibling` of a tag will usually be a string containing whitespace. Going back to the “three sisters” document:

```html
<a href="http://example.com/jeffswt" class="juruo" id="link1">jeffswt</a>
<a href="http://example.com/swt" class="juruo" id="link2">swt</a>
<a href="http://example.com/juruoswt" class="juruo" id="link3">juruoswt</a>
```

You might think that the `.next_sibling()` of the first `<a>` tag would be the second `<a>` tag. But actually, it’s a string: the comma and newline that separate the first `<a>` tag from the second:

```C++
auto link = soup->find("a");
// <a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>
link->next_sibling();
// ",\n"
```

The second `<a>` tag is actually the `.next_sibling()` of the comma:

```C++
link->next_sibling()->next_sibling();
// <a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>
```

#### .next_siblings() and .previous_siblings()

You can iterate over a tag’s siblings with `.next_siblings()` or `.previous_siblings()`:

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

...

## Modifying the tree

...

## Output

## Encodings

You should preferrably and only use UTF-8 as your encoding.

If your document is not, convert it to UTF-8 before you use.

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

