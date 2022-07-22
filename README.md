# <span style="color:#87ceeb">CSHELL</span>

A small unix shell written in C.
This project is still heavily in development, so don't bother trying
to use the shell.

It currently supports:
+ passing parameters to commands,
+ it has some builtin functions like: cd, exit, help,
+ it supports the `&&` operator,
+ it support piping with the `|` operator,
+ passing commands as an argument (```./cshell -c "echo Hello"```).

I will add support for:
+ interactivity,
+ ...