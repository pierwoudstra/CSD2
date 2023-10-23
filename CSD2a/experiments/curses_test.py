import curses

screen = curses.initscr()

curses.curs_set(0)
screen.addstr("   ----\n /      \\\n|  kick  |\n \      /\n   ----")
screen.refresh()
curses.napms(2000)

screen.clear()
screen.addstr("     ^\n    / \\\n   /   \\\n  /snare\\\n  - - - -")
screen.refresh()
curses.napms(2000)

# Wipe the screen buffer and set the cursor to 0,0
screen.clear()

screen.refresh()
curses.napms(2000)

curses.endwin()