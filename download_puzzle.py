#!/usr/bin/env python3
"""Go to adventofcode.com and get puzzle data.

Acquired data is saved in puzzles/{year}/{date}/file folder structure.

Usage example:
python3 download_puzzle.py 2020 1
"""
import os
import requests
import argparse
from datetime import datetime

import pypandoc
from bs4 import BeautifulSoup

USER_AGENT = 'github.com/nedmv/aoc by nedmvl@rambler.ru'
TOKEN_PATH=".aoc_token"

def request_puzzle_data(year: int, day: int):
  """Go to adventofcode.com and get puzzle data.

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  get_puzzle_text(year, day)
  get_puzzle_input(year, day)

def fd(day: int):
  """Convert day to string with leading zero if needed
  
  Args:
      day (int): Puzzle day
  """
  return str(day).zfill(2)

def init_year_header(year):
  """Init puzzles/{year}/{year}.hpp if it doesn't exist.

  Args:
      year: Puzzle year
  """
  path = os.path.join("puzzles",f"{year}",f"{year}.hpp");
  if os.path.exists(path):
    print(f"{path} is already initialized!")
  else:
    with open(path, 'w') as f:
      f.write('#pragma once\n')
      f.write('#include "../headers.hpp"\n')
      f.write('#include "../../src/Task.hpp" //ERROR_STRING\n\n')
      f.write(f'namespace y{year} ' + '{\n\n')

      for i in range(1, 26):
        f.write(f'std::string solve_{fd(i)}a(const std::vector<std::string> &input);'+'\n')
        if (i != 25):
          f.write(f'std::string solve_{fd(i)}b(const std::vector<std::string> &input);'+'\n\n')
      
      f.write('}\n')
    print(f'Successfully initialized {path}')




def init_puzzle_source(year, day):
  """Init puzzle cpp file with template.

  Args:
      year: Puzzle year
      day: Puzzle day
  """
  path = os.path.join("puzzles",f"{year}",f"{day}",f"{day}.cpp");
  if os.path.exists(path):
    print(f"{path} is already initialized!")
  else:
    with open(path, 'w') as f:
      f.write(f'// Puzzle is available at https://adventofcode.com/{year}/day/{int(day):g}'+'\n')
      f.write(f'// Keywords:'+'\n')
      f.write(f'#include "../{year}.hpp"'+'\n')
      f.write(f'#include "../../../src/utils.hpp"'+'\n')
      f.write('using namespace std;\n\n')
      f.write(f'std::string y{year}::solve_{day}a(const std::vector<std::string> &input)' + ' {\n\n\n')
      f.write('  return ERROR_STRING;\n')
      if day != 25:
        f.write('}\n\n')
        f.write(f'std::string y{year}::solve_{day}b(const std::vector<std::string> &input)' + ' {\n\n\n')
        f.write('  return ERROR_STRING;\n')
      f.write('}\n')
    print(f"Successfully initialized {path}")

def init_puzzle_dir(year: int, day: int):
  """Create puzzle dir if it not exists.
  Puzzle dir is located at ./puzzles/{year}/{day}. 

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  day = fd(day)
  year = str(year)
  try: 
    os.mkdir(os.path.join("puzzles",f"{year}"))
  except FileExistsError:
    print(f"Year {year} is already initialized.")
  try:
    os.mkdir(os.path.join("puzzles",f"{year}",f"{day}"))
  except FileExistsError:
    print(f"Day {day} of year {year} is already initialized.")
  init_year_header(year)
  init_puzzle_source(year, day)

def init_test_input(year: int, day: int):
  """Create puzzle test input if it not exists.
  Input is located at ./puzzles/{year}/{day}/test. 

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """ 
  day = fd(day)
  year = str(year)
  path = os.path.join("puzzles",f"{year}",f"{day}", "test")
  if os.path.exists(path):
    print(f"{path} is already initialized!")
  else:
    with open(path, 'w') as f:
      f.write('\n')
    print(f"Successfully initialized {path}")

def get_puzzle_text(year: int, day: int):
  """Get puzzle text and save it as markdown in ./puzzles/{year}/{day}/puzzle.md

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """
  path = os.path.join("puzzles",f"{year}",f"{fd(day)}","puzzle.md");
  if os.path.isfile(path):
    print(f"Puzzle text is already downloaded.")
  else:
    url = f"https://adventofcode.com/{year}/day/{day}"
    headers = {'user-agent': USER_AGENT}
    r = requests.get(url, headers = headers)
    if (r.status_code == 200):
      html = r.text
      soup = BeautifulSoup(html, features="html.parser")
      article = soup.body.find('article')
      md = pypandoc.convert_text(article, 'md', format='html')
      day = fd(day)
      with open(path, 'w') as f:
        f.write(md)
        f.name
        print(f"Puzzle text is available at {path}")
    else:
      print(f"Request failed with code {r.status_code}.")


def get_puzzle_input(year: int, day: int):
  """Download input of the puzzle and store it in ./puzzles/{year}/{day}/input.
  
  To get access function uses adventofcode.com session cookie. 
  It must be the only content of file located at TOKEN_PATH.

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  path = os.path.join("puzzles",f"{year}",f"{fd(day)}","input");
  if os.path.isfile(path):
    print(f"Puzzle input is already downloaded.")
  else:
    with open(TOKEN_PATH, 'r') as f:
      token = f.read()
    cookies=dict(session=token)

    headers = {'user-agent': USER_AGENT}
    url = f"https://adventofcode.com/{year}/day/{day}/input"
    r = requests.get(url, headers = headers, cookies = cookies)
    day = fd(day)
    if (r.status_code == 200):
      with open(path, 'w') as f:
        f.write(r.text)
        print(f"Puzzle input is available at {path}")
    else:
      print(f"Request failed with code {r.status_code}.")

 
def puzzle_date_is_valid(year: int, day: int) -> bool:
  """Check if puzzle with given date should be available by now.

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """ 
  date = datetime.utcnow()
  try:
    assert (2015 <= year and year <= (date.year if date.month == 12 else date.year - 1))
    assert (1 <= day)
    if year == date.year:
      assert (day <= date.day)
      if (day == date.day):
        assert (5 <= date.hour) #puzzle unlocks in 05:00UTC
    else:
      assert (day <= 25)
  except AssertionError:
    print(f"Error: invalid puzzle date {day}/12/{year}")
    return False
  return True

def main():
  """Check args and call logic.
  """  
  parser = argparse.ArgumentParser()
  parser.add_argument('year', nargs='+', metavar='YEAR', type=int, 
                      help = "valid adventofcode.com year (since 2015)")
  parser.add_argument('day', nargs='+', metavar='DAY', type=int, 
                      help = "valid adventofcode.com day (1-25)")
  args = parser.parse_args()
  year = args.year[0]
  day = args.day[0]

  if puzzle_date_is_valid(year, day):
    init_puzzle_dir(year, day)
    request_puzzle_data(year, day)
    init_test_input(year, day)

if __name__ == "__main__":
  main()