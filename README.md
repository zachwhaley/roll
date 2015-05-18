# Roll

Dice rolling programs written in various languages

## C

```
$ gcc -std=c11 roll.c -o roll
$ ./roll 1d6
.---.
| 2 |
'---'

2
```

## Go

```
$ go build roll.go
$ ./roll 2d4
  .
 / \
/ 2 \
`---'
  .
 / \
/ 1 \
`---'

3
```

## Python

```
$ ./roll.py 1d10 1d12
  .
,' ',
\ 7 /
 `,'
  ..
,'  ',
\ 11 /
 `--'

18
```
