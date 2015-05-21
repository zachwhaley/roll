#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct roll_t {
    int count;
    int die;
};

struct dice_t {
    int roll;
    int die;
    struct dice_t *next;
};

struct string_t {
    const char *str;
};

struct string_t d4[4]   = {{"   .  "}, {"  / \\ "}, {" / %d \\"}, {" `---´"}};
struct string_t d6[4]   = {{"      "}, {" .---."}, {" | %d |"}, {" '---'"}};
struct string_t d8[4]   = {{"  /'\\ "}, {" /___\\"}, {" \\ %d /"}, {"  \\./ "}};
struct string_t d10[4]  = {{"       "}, {"  ./\\. "}, {" //%02d\\\\"}, {" ``--´´"}};
struct string_t d12[4]  = {{"  .__. "}, {" /\\__/\\"}, {" \\/%02d\\/"}, {"  `--´ "}};
struct string_t d20[4]  = {{"   __  "}, {"  /__\\ "}, {" /\\%02d/\\"}, {" \\_\\/_/"}};
struct string_t d100[4] = {{"   .  "}, {" .´ `."}, {" \\%03d/"}, {"  `-´ "}};

void free_dice_t(struct dice_t *dice)
{
    if (dice == NULL) return;

    struct dice_t *d;
    do {
        d = dice->next;
        free(dice);
        dice = d;
    } while (dice);
}

struct string_t* line_map(int die)
{
    switch (die) {
        case 4:
            return d4;
        case 6:
            return d6;
        case 8:
            return d8;
        case 10:
            return d10;
        case 12:
            return d12;
        case 20:
            return d20;
        case 100:
            return d100;
        default:
            fprintf(stderr, "d%d is not a valid dice\n", die);
    }
    return NULL;
}

int parse_roll(const char *arg, struct roll_t *roll)
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
    roll->die = die;
    return 0;
}

struct dice_t * process_roll(struct dice_t **dice, int cnt, int die)
{
    struct dice_t *ret = *dice;
    while (dice) dice = dice->next;

    for (int i = 0; i < cnt; i++) {
        dice = (struct dice_t *)calloc(1, sizeof(struct dice_t));
        dice->roll = 1 + rand() / (RAND_MAX / die + 1);
        dice->die = die;
        dice = dice->next;
    }
    return ret;
}

void print_dice(struct dice_t *dice)
{
    struct dice_t *d;
    struct string_t *ln;
    for (int col = 0; col < 4; col++) {
        for (d = dice; d != NULL; d = d->next) {
            ln = line_map(d->die);
            printf(ln[col].str, d->roll);
        }
        puts("");
    }
}

int main(int argc, const char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "No dice\n");
        return -1;
    }
    srand(time(NULL));

    int mods, sum = 0;
    struct dice_t *dice = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '+' || argv[i][0] == '-') {
            mods += atoi(argv[i]);
        } else {
            struct roll_t roll;
            if (parse_roll(argv[i], &roll) == -1) {
                return -1;
            }
            dice = process_roll(&dice, roll.count, roll.die);
        }
    }
    print_dice(dice);

    printf("\nTotal modifiers: %d\n", mods);
    sum += mods;

    struct dice_t *d;
    for (d = dice; d != NULL; d = d->next) {
        sum += d->roll;
    }
    printf("\n%d\n", sum);
    free_dice_t(dice);
    return 0;
}
