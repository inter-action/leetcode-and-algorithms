# src file path to dist file path
file_to_dist = dist/$(subst .cpp,,$(subst src/,,$1))
# compile command arguments
compile_tpl = -std=c17 -Wall -Wextra -O0 -fsanitize=address -g $(1) -o $(call file_to_dist,$(1))
# default file path
FILE ?= src/hello.c

SOURCE = $(shell fd -t f '\.(c|h)'  src)


.PHONY: all compile run fmt
all: compile run

compile:
	mkdir -p $(dir $(call file_to_dist,$(FILE))) # make sure dist dir exist
	clang $(call compile_tpl,$(FILE))

run:
	./$(call file_to_dist,$(FILE))

fmt:
	echo "ready to fmt"
	clang-format -i $(SOURCE)

