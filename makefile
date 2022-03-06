# ----------------------------
# Makefile Options
# ----------------------------

NAME = COMMCHCK
ICON = icon.png
DESCRIPTION = "Commander Checkers"
COMPRESSED = YES
ARCHIVED = NO

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)
