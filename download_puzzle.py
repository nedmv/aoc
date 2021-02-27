#!/usr/bin/env python3
"""Go to adventofcode.com and get puzzle data.

Acquired data is saved it {year}/{date}/file folder structure.

Usage example:
python3 download_puzzle.py 2020 1
"""
import os
import requests
import argparse

import pypandoc
from bs4 import BeautifulSoup

USER_AGENT = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.190 Safari/537.36'
TOKEN_PATH=".aoc_token"

def request_puzzle_data(year: int, day: int):
  """Go to adventofcode.com and get puzzle data.

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  get_puzzle_text(year, day)
  get_puzzle_input(year, day)


def init_puzzle_dir(year: int, day: int):
  """Create puzzle dir if it not exists.
  Puzzle dir is located at ./{year}/{day}. 

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  try: 
    os.mkdir(str(year))
  except FileExistsError:
    print(f"Year {year} is already initialized.")
  try:
    os.mkdir(str(year) + '/' + str(day).zfill(2))
  except FileExistsError:
    print(f"Day {day} of year {year} is already initialized.")

def get_puzzle_text(year: int, day: int):
  """Get puzzle text and save it as markdown in ./{year}/{day}/puzzle.md

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  url = f"https://adventofcode.com/{year}/day/{day}"
  headers = {'user-agent': USER_AGENT}
  r = requests.get(url, headers = headers)
  if (r.status_code == 200):
    html = r.text
    soup = BeautifulSoup(html, features="html.parser")
    article = soup.body.find('article')
    md = pypandoc.convert_text(article, 'md', format='html')
    string_id = str(day).zfill(2)
    with open(f"{year}/{string_id}/puzzle.md", 'w') as f:
      f.write(md)
      f.name
      print(f"Puzzle text is available at {year}/{string_id}/puzzle.md")
  else:
    print(f"Request failed with code {r.status_code}.")


def get_puzzle_input(year: int, day: int):
  """Download input of the puzzle and store it in ./{year}/{day}/input.
  
  To get access function uses adventofcode.com session cookie. 
  It must be the only content of file located at TOKEN_PATH.

  Args:
      year (int): Puzzle year
      day (int): Puzzle day
  """  
  with open(TOKEN_PATH, 'r') as f:
    token = f.read()
  cookies=dict(session=token)

  url = f"https://adventofcode.com/{year}/day/{day}/input"
  headers = {'user-agent': USER_AGENT}
  r = requests.get(url, headers = headers, cookies = cookies)
  string_id = str(day).zfill(2)
  if (r.status_code == 200):
    with open(f"{year}/{string_id}/input", 'w') as f:
      f.write(r.text)
      print(f"Puzzle input is available at {year}/{string_id}/input")
  else:
    print(f"Request failed with code {r.status_code}.")

def main():
  """Check args and call logic.
  """  
  parser = argparse.ArgumentParser()
  parser.add_argument('year', nargs='+', metavar='YEAR', type=int, 
                      help = "valid adventofcode.com year (2015-2020)")
  parser.add_argument('day', nargs='+', metavar='DAY', type=int, 
                      help = "valid adventofcode.com day (1-25)")
  args = parser.parse_args()
  year = args.year[0]
  day = args.day[0]

  #TODO: handle future years
  assert (year >= 2015 and year <= 2020)
  assert (day >= 1 and day <= 25)
  init_puzzle_dir(year, day)
  #TODO: check if it's necessary to rewrite input when part2 unlocks.
  request_puzzle_data(year, day)


if __name__ == "__main__":
  main()