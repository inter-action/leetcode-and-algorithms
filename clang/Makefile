# src file path to dist file path
file_to_dist = dist/$(subst .cpp,,$(subst src/,,$1))
# compile command arguments
# compile_tpl = -std=c17 -Wall -Wextra -O0 -fsanitize=address -g $(1) -o $(call file_to_dist,$(1))
compile_tpl = -std=c17 -Wall -Wextra -O0 -g src/utils.c $(1) -o dist/main
# default file path
FILE ?= src/hello.c

SOURCE = $(shell fd -t f '\.(c|h)'  src)


.PHONY: all compile run fmt
all: compile run

compile:
	mkdir -p $(dir $(call file_to_dist,$(FILE))) # make sure dist dir exist
	clang $(call compile_tpl,$(FILE))

run: compile
	# ./$(call file_to_dist,$(FILE))
	command ./dist/main

fmt:
	echo "ready to fmt"
	clang-format -i $(SOURCE)

