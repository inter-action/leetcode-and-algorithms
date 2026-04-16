# src file path to dist file path
file_to_dist = dist/$(subst .rs,,$(subst src/,,$1))
# compile command arguments
compile_tpl = -g -o dist/bin $1
compile_test_tpl = --test -g -o dist/bin $1
# default file path
FILE ?= src/main.rs

SOURCE = $(shell fd -t f -e rs)


.PHONY: all compile run fmt
all: compile run


run_main:
	mkdir -p dist
	@# mkdir -p $(dir $(call file_to_dist,$(FILE))) # make sure dist dir exist
	rustc $(call compile_tpl,$(FILE))
	command ./dist/bin

run_test:
	mkdir -p dist
	@# mkdir -p $(dir $(call file_to_dist,$(FILE))) # make sure dist dir exist
	rustc $(call compile_test_tpl,$(FILE))
	command ./dist/bin

fmt:
	echo "ready to fmt"
	@# rustfmt $(SOURCE)
	@rustfmt **/*.rs
