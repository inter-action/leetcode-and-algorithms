

## how to run

`cd src` directory

```shell
cd src
clang++ -std=c++17 -g -o -O0 -Wall main n26-remove-duplicates-from-sorted-array.cpp
./main
```

## Anotation

```
NOTE: // notes
```

## Debugging

* compiler explorer - https://godbolt.org/


* add -v option to clang++ 

### how to debug using lldb

```shell
lldb main


# break at start
lldb> process launch -s

# run target
lldb> run

# set a breakpoint
lldb> b main

# list breakpoints
lldb> breakpoint list

# add auto command to breakpoint
lldb> breakpoint command add 1.1


# continue 
lldb> c
# next line
lldb> n
# step in
lldb> i
# print current source
lldb> f

# p
lldb> p <variable_name>
lldb> p/x <variable_name>

# inspect all variables in current frame
lldb> v

# run until reach line no.
lldb> thread until 113

# call stack 
lldb> bt

# select frame
lldb> frame select 1


# gui
lldb> gui


```





## clang-format
```
clang-format -i some.cpp

// or using FZF
clang-format -i src/~~
```


## contents


```
* 差分数组
    * src/n1109-corporate-flight-bookings.cpp

* parsing
    * src/parsing/n385-mini-parser.cpp
        * 西八! 从22:00 写到凌晨1点一刻 :(
```


## failed items
* #5, https://leetcode.cn/problems/longest-palindromic-substring/description/
* #76, src/sliding-window/n76-minimum-window-substring.cpp


## notes

- use `begin != end` to compare all STL containers, hashmap can't using `<` to compare.
- `always delcare a default deconstructor implementation on base class`
    - https://www.geeksforgeeks.org/difference-between-virtual-function-and-pure-virtual-function-in-c/
    - src/parsing/n394-decode-string.cpp
