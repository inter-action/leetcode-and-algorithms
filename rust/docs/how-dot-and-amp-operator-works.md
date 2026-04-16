# `.` and `&` operator


## `.` operator
- `.` operator has higher precedence over `&` and `*` operator

### `.` on function call
- https://doc.rust-lang.org/reference/expressions/method-call-expr.html

rule for `t.call()`
- try find method on `T.<method>`
- try `*` reference to convert to `T`
- then try add `&mt` or `&` and find method there

```rust
let a = String::new("hello");
a.find(",") // a -> &str
let b = &a;
let c = &b; // &&str
c.find(",") // (&(**c)).find()
```
