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

// .---.
// | 6 |
// '---'
func printSquare(d int) {
	fmt.Printf(".---.\n| %d |\n'---'\n", d)
}

//   .
//  / \
// / 4 \
// `---'
//   ..
//  /  \
// / 20 \
// `----'
func printTriangle(d int) {
	if d < 10 {
		fmt.Printf("  .\n / \\\n/ %d \\\n`---'\n", d)
	} else {
		fmt.Printf("  ..\n /  \\\n/ %d \\\n`----'\n", d)
	}
}

//   .
//  / \
// / 1 \
// `, ,'
//   '
//   ..
//  /  \
// / 10 \
// `,  ,'
//   ''
func printDiamond(d int) {
	if d < 10 {
		fmt.Printf("  .\n,' ',\n\\ %d /\n `,'\n", d)
	} else if d < 100 {
		fmt.Printf("  ..\n /  \\\n/ %d \\\n`,  ,'\n  ''\n", d)
	} else {
		fmt.Printf("  .\n,' ',\n\\%d/\n `,'\n", d)
	}
}

//   .
// ,' ',
// \ 1 /
//  `-'
//   ..
// ,'  ',
// \ 12 /
//  `--'
func printPentagon(d int) {
	if d < 10 {
		fmt.Printf("  .\n,' ',\n\\ %d /\n `-'\n", d)
	} else {
		fmt.Printf("  ..\n,'  ',\n\\ %d /\n `--'\n", d)
	}
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
		print_dice = printTriangle
	case 6:
		print_dice = printSquare
	case 8:
		print_dice = printTriangle
	case 10:
		print_dice = printDiamond
	case 12:
		print_dice = printPentagon
	case 20:
		print_dice = printTriangle
	case 100:
		print_dice = printDiamond
	default:
		return -1, fmt.Errorf("d%d is not a valid dice\n", die)
	}

	var result int
	var sum int
	for i := 0; i < cnt; i++ {
		result = rand.Intn(die) + 1
		print_dice(result)
		sum += result
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
