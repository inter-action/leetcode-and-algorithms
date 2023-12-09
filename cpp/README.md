

## how to run

`cd src` directory

```shell
cd src
clang++ -std=c++17 -g -o test n26-remove-duplicates-from-sorted-array.cpp
./test
```


## how to debug using lldb

```shell
lldb test

lldb> process launch -s
# set a breakpoint
lldb> break main
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

# gui
lldb> gui



```






