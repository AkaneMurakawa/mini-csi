# mini-csi
Mini C script interpreter

- support basic arithmetic calculation and decimal calculation.
- support negative numbers and parentheses

## Basic structure of simple interpreter
```text
Lexical ———Token———> Parser ———AST———> Interpreter
```

## Example
```shell script
Hello, C script interpreter
>> -1+2*3-(4+5)/3
tokenKind=3, value=-
tokenKind=1, value=1
tokenKind=2, value=+
tokenKind=1, value=2
tokenKind=4, value=*
tokenKind=1, value=3
tokenKind=3, value=-
tokenKind=6, value=(
tokenKind=1, value=4
tokenKind=2, value=+
tokenKind=1, value=5
tokenKind=7, value=)
tokenKind=5, value=/
tokenKind=1, value=3
2
```

## Compiler and Run
```bash
gcc main.c -o main

./main
```

## Refrence
- 《自制编程语言》 [日] 前桥和弥