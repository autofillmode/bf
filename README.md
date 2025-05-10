# bf - A Brainfuck Interpreter

This is an interpreter for the Brainfuck language, written in pure ansi C. 

[Brainfuck](https://en.wikipedia.org/wiki/Brainfuck) is an esoteric programming language that works by giving the user 30 kilobytes in the form of an array consisting of single bytes, in which the user can move left or right, print, increment, and decrement values, or read stdin in one-byte chunks. There are loops too. In short, it's turing complete. 

## Usage

Compile it with whatever c compiler:

`cc bc.c -o interpreter`

And enjoy interpreting!

`./interpreter <source file>`
