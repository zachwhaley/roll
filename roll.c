#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct roll_t {
    int count;
    int dice;
};

typedef void (*print_dice_t)(int);

//   .
//  / \
// / 4 \
// `---´
void print_d4(int d)
{
    printf("\n  .\n / \\\n/ %d \\\n`---´\n", d);
}

// .---.
// | 6 |
// '---'
void print_d6(int d)
{
    printf("\n.---.\n| %d |\n'---'\n", d);
}

//  /'\
// /___\
// \ 8 /
//  \./
void print_d8(int d)
{
    printf("\n /'\\\n/___\\\n\\ %d /\n \\./\n", d);
}

//  ./\.
// //10\\
// ``--´´
void print_d10(int d)
{
    printf("\n ./\\. \n//%02d\\\\\n``--´´\n", d);
}

//  .__.
// /\__/\
// \/12\/
//  `--´
void print_d12(int d)
{
    printf("\n .__. \n/\\__/\\\n\\/%02d\\/\n `--´ \n", d);
}

//   __
//  /__\
// /\20/\
// \_\/_/
void print_d20(int d)
{
    printf("\n  __  \n /__\\ \n/\\%02d/\\\n\\_\\/_/\n", d);
}

//   .
// .´ `.
// \100/
//  `-´
void print_d100(int d)
{
    printf("\n  .\n.´ `.\n\\%03d/\n `-´\n", d);
}

int parse_arg(const char *arg, struct roll_t *roll)
{
    // Null terminate the middle of the string, so that the arg is technically split into two
    // strings.  The first string, the count of dice, and the second string, the dice to roll.
    // e.g ['2','d','6','\0'] will become ['2','\0','6','\0']
    char *split = strchr(arg, 'd');
    if (split == NULL) {
        fprintf(stderr, "Bad argument: %s\n", arg);
        return -1;
    }
    *split = '\0';

    // Since input like d6 is valid (equal to 1d6) we need to check if arg is now set to a null
    // terminator; if so, set the dice count to 1
    int cnt = (*arg != '\0') ? atoi(arg) : 1;
    int die = atoi(split+1);
    roll->count = cnt;
    roll->dice = die;
    return 0;
}

int process_roll(int cnt, int die)
{
    print_dice_t print_dice = NULL;

    switch (die) {
    case 4:
        print_dice = &print_d4;
        break;
    case 6:
        print_dice = &print_d6;
        break;
    case 8:
        print_dice = &print_d8;
        break;
    case 10:
        print_dice = &print_d10;
        break;
    case 12:
        print_dice = &print_d12;
        break;
    case 20:
        print_dice = &print_d20;
        break;
    case 100:
        print_dice = &print_d100;
        break;
    default:
        fprintf(stderr, "d%d is not a valid dice\n", die);
        return -1;
    }

    int roll, sum = 0;
    for (int i = 0; i < cnt; i++) {
        roll = 1 + rand() / (RAND_MAX / die + 1);
        print_dice(roll);
        sum += roll;
    }
    return sum;
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "No dice\n");
        return -1;
    }
    srand(time(NULL));

    int res, sum = 0;
    for (int i = 1; i < argc; i++) {
        struct roll_t roll;
        if (parse_arg(argv[i], &roll) == -1)
            return -1;
        if ((res = process_roll(roll.count, roll.dice)) == -1)
            return -1;
        sum += res;
    }
    printf("\n%d\n", sum);
    return 0;
}
