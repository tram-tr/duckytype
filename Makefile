CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
LDFLAGS = -lcurl
SRCDIR = src
INCDIR = include
TESTDIR = test
BUILDDIR = build
TARGET = duckytype

SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(BUILDDIR)/%.o,$(SRCS))
DEPS = $(wildcard $(INCDIR)/*.h)

.PHONY: all clean fetch_paragraph

all: $(TARGET)

$(TARGET): $(BUILDDIR)/fetch_data.o $(BUILDDIR)/main.o $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/fetch_data.o: $(SRCDIR)/fetch_data.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

$(BUILDDIR)/main.o: $(SRCDIR)/main.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

fetch_paragraph: $(BUILDDIR)/fetch_data.o
	$(CC) $(LDFLAGS) -o $(BUILDDIR)/fetch_data $^
	$(BUILDDIR)/fetch_data

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET) $(BUILDDIR)/fetch_data

test: $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCDIR)/typingtest.c $(TESTDIR)/test.c -o $(BUILDDIR)/test
	$(BUILDDIR)/test
