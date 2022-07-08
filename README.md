# mini-csi
Mini C script interpreter

- support basic arithmetic calculation and decimal calculation.

## Basic structure of simple interpreter
```text
Lexical ———Token———> Parser ———AST———> Interpreter
```

## Example
```shell script
Hello, C script interpreter
>>1+2*3-4
tokenKind=1, value=1
tokenKind=2, value=+
tokenKind=1, value=2
tokenKind=4, value=*
tokenKind=1, value=3
tokenKind=3, value=-
tokenKind=1, value=4
3
```

## Compiler and Run
```bash
gcc main.c -o main

./main
```

## Refrence
- 《自制编程语言》 [日] 前桥和弥