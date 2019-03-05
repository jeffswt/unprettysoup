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

## Installing Unpretty Soup

## Making the soup

## Kinds of objects

### Char

### String

### Element

## Navigating the tree

### Going down

### Going up

### Going sideways

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

