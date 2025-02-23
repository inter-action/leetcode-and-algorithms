struct Solution;

#[derive(Debug, PartialEq, Eq)]
pub enum NestedInteger {
    Int(i32),
    List(Vec<NestedInteger>),
}

struct TokenStream {
    idx: usize,
    str: String,
}

impl TokenStream {
    pub fn new(s: String) -> Self {
        TokenStream { idx: 0, str: s }
    }

    pub fn next(&mut self) -> Option<char> {
        let result = self.str.chars().nth(self.idx);
        self.idx += 1;
        result
    }

    pub fn consume(&mut self, c: char) -> Option<()> {
        let result = self.str.chars().nth(self.idx);
        result.and_then(|e| {
            self.idx += 1;
            if c == e {
                Some(())
            } else {
                None
            }
        })
    }

    pub fn peek(&mut self) -> Option<char> {
        self.str.chars().nth(self.idx)
    }

    pub fn isEOF(self) -> bool {
        self.idx == self.str.len()
    }
}
/*
grammar:

list: (num | list)*
num: [1-9]
 */
impl Solution {
    pub fn deserialize(s: String) -> NestedInteger {
        let mut ts = TokenStream::new(s);

        if let Some(c) = ts.peek() {
            if c.is_ascii_digit() {
                Solution::parseNum(&mut ts)
            } else {
                Solution::parseList(&mut ts)
            }
        } else {
            panic!("invalid ")
        }
    }

    pub fn parseNum(ts: &mut TokenStream) -> NestedInteger {
        let mut i: i32 = 0;
        loop {
            match ts.peek() {
                Some(c) if c.is_ascii_digit() => {
                    ts.consume(c);
                    i = i * 10 + c.to_digit(10).map(|e| e as i32).unwrap()
                }
                _ => {
                    // should make i as optional type.
                    // then check if i is been actually set
                    return NestedInteger::Int(i);
                }
            }
        }
    }

    pub fn parseList(ts: &mut TokenStream) -> NestedInteger {
        ts.consume('[').expect("start of list");
        let mut vec: Vec<NestedInteger> = vec![];

        loop {
            match ts.peek() {
                Some(c) => {
                    match c {
                        '0'..'9' => {
                            print!("0{} ", c);
                            vec.push(Solution::parseNum(ts));
                        }
                        ',' => {
                            print!("1{} ", c);
                            ts.consume(',');
                            // simply ignore this
                            continue;
                        }
                        '[' => {
                            print!("2{} ", c);
                            vec.push(Solution::parseList(ts))
                        }
                        ']' => {
                            print!("3{} ", c);
                            ts.consume(']').expect("curly braces not match");
                            return NestedInteger::List(vec);
                        }
                        _ => {
                            panic!("unexpected token");
                        }
                    }
                }
                _ => {
                    panic!("invalid string")
                }
            }
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_a() {
        let s = "[123,[456,[789]]]";

        assert_eq!(
            Solution::deserialize(s.into()),
            NestedInteger::List(vec![
                NestedInteger::Int(123),
                NestedInteger::List(vec![
                    NestedInteger::Int(456),
                    NestedInteger::List(vec![NestedInteger::Int(789),])
                ])
            ])
        );
    }

    #[test]
    fn test_b() {
        let s = "324";
        assert_eq!(Solution::deserialize(s.into()), NestedInteger::Int(324));
    }
}
