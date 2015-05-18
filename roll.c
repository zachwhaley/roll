#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct roll_t {
    int count;
    int dice;
};

typedef void (*print_dice_t)(int);

// .---.
// | 6 |
// '---'
void print_square(int d)
{
    printf(".---.\n| %d |\n'---'\n", d);
}

//   .
//  / \
// / 4 \
// `---'
//   ..
//  /  \
// / 20 \
// `----'
void print_triangle(int d)
{
    if (d < 10)
        printf("  .\n / \\\n/ %d \\\n`---'\n", d);
    else
        printf("  ..\n /  \\\n/ %d \\\n`----'\n", d);
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
void print_diamond(int d)
{
    if (d < 10)
        printf("  .\n,' ',\n\\ %d /\n `,'\n", d);
    else if (d < 100)
        printf("  ..\n /  \\\n/ %d \\\n`,  ,'\n  ''\n", d);
    else
        printf("  .\n,' ',\n\\%d/\n `,'\n", d);
}

//   .
// ,' ',
// \ 1 /
//  `-'
//   ..
// ,'  ',
// \ 12 /
//  `--'
void print_pentagon(int d)
{
    if (d < 10)
        printf("  .\n,' ',\n\\ %d /\n `-'\n", d);
    else
        printf("  ..\n,'  ',\n\\ %d /\n `--'\n", d);
}

struct roll_t parse_arg(const char *arg)
{
    // Null terminate the middle of the string, so that the arg is technically split into two
    // strings.  The first string, the count of dice, and the second string, the dice to roll.
    // e.g ['2','d','6','\0'] will become ['2','\0','6','\0']
    char *split = strchr(arg, 'd');
    *split = '\0';

    int cnt = atoi(arg);
    int die = atoi(split+1);
    struct roll_t roll = {
        .count = cnt,
        .dice = die,
    };
    return roll;
}

int process_roll(int cnt, int die)
{
    print_dice_t print_dice = NULL;

    switch (die) {
    case 4:
        print_dice = &print_triangle;
        break;
    case 6:
        print_dice = &print_square;
        break;
    case 8:
        print_dice = &print_triangle;
        break;
    case 10:
        print_dice = &print_diamond;
        break;
    case 12:
        print_dice = &print_pentagon;
        break;
    case 20:
        print_dice = &print_triangle;
        break;
    case 100:
        print_dice = &print_diamond;
        break;
    default:
        // error, not a valid dice
        return 0;
    }

    int result = 0;
    int sum = 0;
    for (int i = 0; i < cnt; i++) {
        // http://c-faq.com/lib/randrange.html
        result = 1 + rand() / (RAND_MAX / (die-2) + 1);
        print_dice(result);
        sum += result;
    }
    return sum;
}

void main(int argc, const char *argv[])
{
    srand(time(NULL));

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        struct roll_t roll = parse_arg(argv[i]);
        sum += process_roll(roll.count, roll.dice);
    }
    printf("\n%d\n", sum);
}
