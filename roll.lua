#!/usr/bin/env lua

printf = function(s,...) return io.write(s:format(...)) end

--   .
--  / \
-- / 4 \
-- `---´
function printd4(d)
  printf("\n  .\n / \\\n/ %d \\\n`---´\n", d)
end

-- .---.
-- | 6 |
-- '---'
function printd6(d)
  printf("\n.---.\n| %d |\n'---'\n", d)
end

--  /'\
-- /___\
-- \ 8 /
--  \./
function printd8(d)
  printf("\n /'\\\n/___\\\n\\ %d /\n \\./\n", d)
end

--  ./\.
-- //10\\
-- ``--´´
function printd10(d)
  printf("\n ./\\. \n//%02d\\\\\n``--´´\n", d)
end

--  .__.
-- /\__/\
-- \/12\/
--  `--´
function printd12(d)
  printf("\n .__. \n/\\__/\\\n\\/%02d\\/\n `--´ \n", d)
end

--   __
--  /__\
-- /\20/\
-- \_\/_/
function printd20(d)
  printf("\n  __  \n /__\\ \n/\\%02d/\\\n\\_\\/_/\n", d)
end

--   .
-- .´ `.
-- \100/
--  `-´
function printd100(d)
  printf("\n  .\n.´ `.\n\\%03d/\n `-´\n", d)
end

function parseroll(arg)
  local i, j, cnt, die
  i, j = string.find(arg, 'd')
  cnt = (i > 1 and string.sub(arg, 1, i-1) or 1)
  die = string.sub(arg, j+1, #arg)
  return tonumber(cnt), tonumber(die)
end

function processroll(cnt, die)
  local printdice
  if die == 4 then
    printdice = printd4
  elseif die == 6 then
    printdice = printd6
  elseif die == 8 then
    printdice = printd8
  elseif die == 10 then
    printdice = printd10
  elseif die == 12 then
    printdice = printd12
  elseif die == 20 then
    printdice = printd20
  elseif die == 100 then
    printdice = printd100
  else
    -- error, not a valid dice
    return 0
  end

  local sum, roll = 0, 0
  for i=1,cnt do
    roll = math.random(die)
    printdice(roll)
    sum = sum + roll
  end
  return sum
end

-- main
sum = 0
for i,v in ipairs(arg) do
  cnt, die = parseroll(v)
  sum = sum + processroll(cnt, die)
end
printf("\n%d\n", sum)
