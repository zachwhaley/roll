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

type Roll struct {
	die, val int
}

var dmap = map[int][]string{
	4:   {"   .  ", "  / \\ ", " / %d \\", " `---´"},
	6:   {"      ", " .---.", " | %d |", " '---'"},
	8:   {"  /'\\ ", " /___\\", " \\ %d /", "  \\./ "},
	10:  {"       ", "  ./\\. ", " //%02d\\\\", " ``--´´"},
	12:  {"  .__. ", " /\\__/\\", " \\/%02d\\/", "  `--´ "},
	20:  {"   __  ", "  /__\\ ", " /\\%02d/\\", " \\_\\/_/"},
	100: {"   .  ", " .´ `.", " \\%03d/", "  `-´ "},
}

func parseRoll(arg string) (int, int, error) {
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

func processRoll(cnt, die int) []Roll {
	var dice []Roll

	for i := 0; i < cnt; i++ {
		roll := rand.Intn(die) + 1
		dice = append(dice, Roll{die, roll})
	}
	return dice
}

func printDice(dice []Roll) {
	for i := 0; i < 4; i++ {
		for _, roll := range dice {
			l := dmap[roll.die]
			if i != 2 {
				fmt.Print(l[i])
			} else {
				fmt.Printf(l[i], roll.val)
			}
		}
		fmt.Println()
	}
}

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "No dice\n")
		os.Exit(1)
	}

	var mods, sum int
	var dice []Roll
	for i := 1; i < len(os.Args); i++ {
		arg := os.Args[i]
		if arg[0] == '+' || arg[0] == '-' {
			mod, _ := strconv.Atoi(arg)
			mods += mod
		} else {
			cnt, die, err := parseRoll(arg)
			if err != nil {
				fmt.Fprint(os.Stderr, err)
				os.Exit(-1)
			}
			dice = append(dice, processRoll(cnt, die)...)
		}
	}
	printDice(dice)

	fmt.Printf("\nTotal modifiers: %d\n", mods)
	sum += mods

	for _, roll := range dice {
		sum += roll.val
	}
	fmt.Printf("\n%d\n", sum)
}
