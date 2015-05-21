# Roll

Dice rolling programs written in various languages

## Want to make your own?

Start with a simple program that takes in an argument like `1d4` and prints a random number between 1 and 4

```
$ ./roll 1d4
3
```

Take multiple arguments while allowing input like `2d6` and `d8`; print the sum as well.

```
$ ./roll 1d4 2d6 d8
2
5
3
8

18
```

Add some ASCII art

```
   .    /'\          .__.    __     .
  / \  /___\  ./\.  /\__/\  /__\  .´ `.
 / 4 \ \ 8 / //10\\ \/12\/ /\20/\ \100/
 `---´  \./  ``--´´  `--´  \_\/_/  `-´
```

```
$ ./roll 2d4
  .
 / \
/ 2 \
`---´

  .
 / \
/ 1 \
`---´

3
```

Modify your code to use modifiers ;)

```
$ ./roll 2d4 +1
  .
 / \
/ 3 \
`---´

  .
 / \
/ 1 \
`---´

Total modifiers: 1

5
```

Handle errors

```
$ ./roll
No dice

$ ./roll 1d3
d3 is not a valid dice

$./roll bleh
Bad argument: bleh
```

Print the dice horizontally

```
$ ./roll.py d10 d12
        .__.
 ./\.  /\__/\
//07\\ \/11\/
``--´´  `--´

18
```

And so on :)
