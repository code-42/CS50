# This is CS50 - Week 2

Disclaimer: unashamedly converted to README.md from https://docs.cs50.net/problems/initials/more/initials.html

# Initials

## [tl;dr](#tl-dr)

Implement a program that, given a person's name, prints a person's initials, per the below.

```
$ ./initials
Regulus Arcturus Black
RAB
```

## [Specification](#specification)

Design and implement a program, `initials`, that, given a person's name, prints a person's initials.

* Implement your program in a file called `initials.c` in a directory called `initials`.
* Your program should prompt a user for their name using `get_string` to obtain their name as a `string`.
* You may assume that the user's input will contain only letters (uppercase and/or lowercase) plus spaces. You don't need to worry about names like `Joseph Gordon-Levitt`, `Conan O&#x2019;Brien`, or `David J. Malan`!
* But the user's input might be sloppy, in which case there might be one or more spaces at the start and/or end of the user's input or even multiple spaces in a row.
* Your program should print the user's initials (i.e., the first letter of each word in their name) with no spaces or periods, followed by a newline (`\n`).

## [Walkthrough](#walkthrough)

## [Usage](#usage)

Your program should behave per the examples below. Assumed that the underlined text is what some user has typed.

```
$ <span class="underline">./initials</span>
<span class="underline">Zamyla Chan</span>
ZC
```

```
$ <span class="underline">./initials</span>
<span class="underline">   robert   thomas bowden</span>
RTB
```

## [Testing](#testing)

### [`check50`](#code-check50-code)

```
check50 cs50/2017/x/initials/more
```

## [Staff's Solution](#staff-s-solution)

```
~cs50/hacker2/initials
```

## [FAQs](#faqs)

_None so far! Reload this page periodically to check if any arise!_

## [Changelog](#changelog)

* 2016-09-09
  - Initial release.
