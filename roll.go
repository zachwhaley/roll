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

func parseArg(arg string) (int, int) {
	n := strings.Index(arg, 'd')
	cnt, _ := strconv.Atoi(arg[:n])
	die, _ := strconv.Atoi(arg[n+1:])
	return cnt, die
}

func processRoll(cnt, die int) int {
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
		// error, not a valid dice
		return 0
	}

	var result int
	var sum int
	for i := 0; i < cnt; i++ {
		result = rand.Intn(die) + 1
		print_dice(result)
		sum += result
	}
	return sum
}

func main() {
	var sum int
	for i, arg := range os.Args {
		if i == 0 {
			continue
		}
		cnt, die := parseArg(arg)
		sum += processRoll(cnt, die)
	}
	fmt.Printf("\n%d\n", sum)
}
