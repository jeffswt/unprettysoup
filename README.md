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

Here's an HTML document I'll be using as an example throughout this document.

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

## Installing Unpretty Soup

## Making the soup

## Kinds of objects

### Char

### String

### Element

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

If you need to get all the `<a>` tags, or anything more complicated than the first tag with a certain name, you'll need to use one of the methods described in [Searching the tree](), such as `.find_all()`:

```C++
soup->find_all("a");
// [<a class="sister" href="http://example.com/elsie" id="link1">Elsie</a>,
//  <a class="sister" href="http://example.com/lacie" id="link2">Lacie</a>,
//  <a class="sister" href="http://example.com/tillie" id="link3">Tillie</a>]
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

If a tag's only child is another tag, and that tag has a `.string()`, then the parent tag is considered to have the same `.string` as its child:

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

You can access an element's parent with the `.parent()` method. In the example "three sisters" document, the `<head>` tag is the parent of the `<title>` tag:

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

