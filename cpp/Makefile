file_to_dist = dist/$(subst .cpp,,$(subst src/,,$1))
compile_tpl = -std=c++17 -Wall -Wextra -O0 -fsanitize=address -g $(1) -o $(call file_to_dist,$(1))
FILE ?= src/n19-remove-nth-node-from-end-of-list.cpp

SOURCE = $(shell fd -t f -e cpp)


.PHONY: compile run fmt
compile:
	mkdir -p $(dir $(call compile_tpl,$(FILE))) # make sure dist dir exist
	clang++ $(call compile_tpl,$(FILE))

run:
	./$(call file_to_dist,$(FILE))

fmt:
	echo "ready to fmt"
	clang-format -i $(SOURCE)

