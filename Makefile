CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS =
SRCDIR = src
INCDIR = include
TESTDIR = test
BUILDDIR = build
TARGET = meattype

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(wildcard $(INCDIR)/*.h)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)

test: $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCDIR)/typingtest.c $(TESTDIR)/test.c -o $(BUILDDIR)/test
	$(BUILDDIR)/test
