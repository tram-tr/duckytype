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

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

fetch_paragraph:
	$(CC) $(CFLAGS) $(SRCDIR)/fetch_data.c -lcurl -o $(BUILDDIR)/fetch_data
	$(BUILDDIR)/fetch_data

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET) $(BUILDDIR)/test $(BUILDDIR)/fetch_data

test: $(OBJS)
	$(CC) $(CFLAGS) -I$(INCDIR) $(SRCDIR)/typingtest.c $(TESTDIR)/test.c -o $(BUILDDIR)/test
	$(BUILDDIR)/test
