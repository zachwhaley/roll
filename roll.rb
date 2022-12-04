#!/usr/bin/env ruby

#   .    /'\          .__.    __     .
#  / \  /___\  ./\.  /\__/\  /__\  .´ `.
# / 4 \ \ 8 / //10\\ \/12\/ /\20/\ \100/
# `---´  \./  ``--´´  `--´  \_\/_/  `-´

ASCII_MAP = {
  '4': ['   .  ', '  / \ ', ' / %d \\', ' `---´'],
  '6': ['      ', ' .---.', ' | %d |', ' \'---\''],
  '8': ['  /\'\ ', ' /___\\', ' \ %d /', '  \./ '],
  '10': ['       ', '  ./\. ', ' //%02d\\\\', ' ``--´´'],
  '12': ['  .__. ', ' /\__/\\', ' \/%02d\/', '  `--´ '],
  '20': ['   __  ', '  /__\ ', ' /\\%02d/\\', ' \_\/_/'],
  '100': ['   .  ', ' .´ `.', ' \\%03d/', '  `-´ '],
}

def parse_roll(argument)
  dice_values = argument.split('d')

  raise "Bad argument: #{argument}" if dice_values.count < 1

  count = dice_values.count == 2 ? dice_values.first.to_i : 1
  dice = dice_values.last.to_sym
  [count, dice]
end

def valid_dice?(dice)
  ASCII_MAP.keys.include?(dice)
end

def process_roll(count, dice)
  raise "#{dice} is not a valid dice" unless valid_dice?(dice)

  result = []
  count.times do
      result << [rand(1..dice.to_s.to_i), dice]
  end

  result
end

def print_dice(dice)
  4.times do |line|
    dice.each do |die|
      line_parts = ASCII_MAP[die.last.to_sym]
      string = line != 2 ? line_parts[line] : printf(line_parts[line], die.first)
      print(string)
    end
    puts ""
  end
end

raise "No Dice" if ARGV.count < 1

sum = 0
mods = 0
dice = []

ARGV.each do |argument|
  if ["-", "+"].include?(argument[0])
    mods += argument.to_i
  else
    count, die = parse_roll(argument)
    dice += process_roll(count, die)
  end
end

print_dice(dice)

puts "\nTotal modifiers: #{mods}"

sum += mods
sum += dice.sum { |d| d.first }

puts "\n#{sum}"

exit
