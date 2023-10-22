import curses

screen = curses.initscr()

curses.curs_set(0)
screen.addstr("Hello, I will be cleared in 2 seconds.")
screen.refresh()
curses.napms(2000)

# Wipe the screen buffer and set the cursor to 0,0
screen.clear()

screen.refresh()
curses.napms(2000)

curses.endwin()