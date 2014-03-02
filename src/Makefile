# Executable's name
NAME	= trantor
# Source files
SRC	= utils/utils.c \
	  utils/stack.c \
	  utils/hashmap.c \
	  utils/buffstr.c \
	  hari-main.c \
	  yugo-ast.c \
	  salvor-bytecode.c \
	  daneel-vm.c

# ##################################################################

# Paths to header files
IPATH	= -I. -I../../include -I../include
# Path to libraries and lib's names
LDPATH	= -L. -L../lib -ll -lgc -lpthread -Wl,-rpath -Wl,'$$ORIGIN/../lib'
# Compiler options
EXEOPT	= -O3 # -g for debug

# ###################################################################

CC	= gcc
OBJS	= $(SRC:.c=.o)
# Objects compilation options
CFLAGS	= -ansi -std=c99 -Wall -Wextra -Wmissing-prototypes \
	  -Wno-long-long -Wno-unused-parameter -Wno-variadic-macros -D_GNU_SOURCE -D_THREAD_SAFE \
	  $(IPATH) $(EXEOPT)
# Link options
LDFLAGS = $(EXEOPT) $(LDPATH)

# ###################################################################

.PHONY:	all clean test

$(NAME): preem-grammar.tab.o lex.yy.o $(OBJS)
	@echo "##### LINKING EXECUTABLE"
	$(CC) $(OBJS) preem-grammar.tab.o lex.yy.o $(LDFLAGS) -o $(NAME)

all: clean $(NAME)

clean:
	@echo "##### CLEANING"
	rm -f lex.yy.c preem-grammar.tab.c preem-grammar.tab.h *.o trantor utils/*.o

lex.yy.c: gaal-lexer.l
	@echo "##### BUILDING LEXER"
	lex gaal-lexer.l

preem-grammar.tab.c: preem-grammar.y
	@echo "##### BUILDING PARSER"
	bison -d preem-grammar.y

lex.yy.o: lex.yy.c
	@echo "##### COMPILING lex.yy.c"
	$(CC) -pedantic -ansi -std=c99 -Wall -D_GNU_SOURCE -Wno-unused-function -c lex.yy.c

preem-grammar.tab.o: preem-grammar.tab.c
	@echo "##### COMPILING grammar.tab.c"
	$(CC) -pedantic -ansi -std=c99 -Wall -D_GNU_SOURCE -c preem-grammar.tab.c

.c.o:
	@echo "##### COMPILING $<"
	$(CC) $(CFLAGS) -c $< -o $@

test:
	@echo ; more test ; echo ; echo "================" ; echo
	@./$(NAME) test

