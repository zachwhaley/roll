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
        fprintf(stderr, "d%d is not a valid dice\n", die);
        return -1;
    }

    int result = 0;
    int sum = 0;
    for (int i = 0; i < cnt; i++) {
        result = 1 + rand() / (RAND_MAX / die + 1);
        print_dice(result);
        sum += result;
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

    int res = 0;
    int sum = 0;
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
