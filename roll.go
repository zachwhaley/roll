package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

func init() {
	rand.Seed(time.Now().UTC().UnixNano())
}

type printDice func(int)

//   .
//  / \
// / 4 \
// `---´
func printD4(d int) {
	fmt.Printf("\n  .\n / \\\n/ %d \\\n`---´\n", d)
}

// .---.
// | 6 |
// '---'
func printD6(d int) {
	fmt.Printf("\n.---.\n| %d |\n'---'\n", d)
}

//  /'\
// /___\
// \ 8 /
//  \./
func printD8(d int) {
	fmt.Printf("\n /'\\\n/___\\\n\\ %d /\n \\./\n", d)
}

//  ./\.
// //10\\
// ``--´´
func printD10(d int) {
	fmt.Printf("\n ./\\. \n//%02d\\\\\n``--´´\n", d)
}

//  .__.
// /\__/\
// \/12\/
//  `--´
func printD12(d int) {
	fmt.Printf("\n .__. \n/\\__/\\\n\\/%02d\\/\n `--´ \n", d)
}

//   __
//  /__\
// /\20/\
// \_\/_/
func printD20(d int) {
	fmt.Printf("\n  __  \n /__\\ \n/\\%02d/\\\n\\_\\/_/\n", d)
}

//   .
// .´ `.
// \100/
//  `-´
func printD100(d int) {
	fmt.Printf("\n  .\n.´ `.\n\\%03d/\n `-´\n", d)
}

func parseArg(arg string) (int, int, error) {
	n := strings.Index(arg, "d")
	if n == -1 {
		return -1, -1, fmt.Errorf("Bad argument: %s\n", arg)
	}

	// Since input like d6 is valid (equal to 1d6) we need to check if the index of "d" in arg
	// is greater than 0; if so, find the dice count, otherwise set the dice count to 1
	cnt := 1
	if n > 0 {
		cnt, _ = strconv.Atoi(arg[:n])
	}
	die, _ := strconv.Atoi(arg[n+1:])
	return cnt, die, nil
}

func processRoll(cnt, die int) (int, error) {
	var print_dice printDice

	switch die {
	case 4:
		print_dice = printD4
	case 6:
		print_dice = printD6
	case 8:
		print_dice = printD8
	case 10:
		print_dice = printD10
	case 12:
		print_dice = printD12
	case 20:
		print_dice = printD20
	case 100:
		print_dice = printD100
	default:
		return -1, fmt.Errorf("d%d is not a valid dice\n", die)
	}

	var sum int
	for i := 0; i < cnt; i++ {
		roll := rand.Intn(die) + 1
		print_dice(roll)
		sum += roll
	}
	return sum, nil
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "No dice\n")
		os.Exit(1)
	}

	var sum int
	for i := 1; i < len(os.Args); i++ {
		cnt, die, err := parseArg(os.Args[i])
		if err != nil {
			fmt.Fprint(os.Stderr, err)
			os.Exit(-1)
		}
		res, err := processRoll(cnt, die)
		if err != nil {
			fmt.Fprint(os.Stderr, err)
			os.Exit(-1)
		}
		sum += res
	}
	fmt.Printf("\n%d\n", sum)
}
