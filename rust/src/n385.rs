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

    #[allow(dead_code)]
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
                Solution::parse_num(&mut ts)
            } else {
                Solution::parse_list(&mut ts)
            }
        } else {
            panic!("invalid ")
        }
    }

    pub fn parse_num(ts: &mut TokenStream) -> NestedInteger {
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

    pub fn parse_list(ts: &mut TokenStream) -> NestedInteger {
        ts.consume('[').expect("start of list");
        let mut vec: Vec<NestedInteger> = vec![];

        loop {
            match ts.peek() {
                Some(c) => {
                    match c {
                        '0'..'9' => {
                            vec.push(Solution::parse_num(ts));
                        }
                        ',' => {
                            ts.consume(',');
                            // simply ignore this
                            continue;
                        }
                        '[' => {
                            vec.push(Solution::parse_list(ts))
                        }
                        ']' => {
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

// standard solution
// impl NestedInteger {
//     // Constructor for integer
//     fn new_int(value: i32) -> Self {
//         NestedInteger::Int(value)
//     }
    
//     // Constructor for empty list
//     fn new_list() -> Self {
//         NestedInteger::List(Vec::new())
//     }
    
//     // Add element to list (only valid for List variant)
//     fn add(&mut self, elem: NestedInteger) {
//         if let NestedInteger::List(ref mut list) = self {
//             list.push(elem);
//         }
//     }
// }

// fn deserialize(s: String) -> NestedInteger {
//     // Handle empty string
//     if s.is_empty() {
//         return NestedInteger::new_list();
//     }
    
//     // If no brackets, it's just a number
//     if !s.starts_with('[') {
//         return NestedInteger::new_int(s.parse::<i32>().unwrap());
//     }
    
//     let mut stack: Vec<NestedInteger> = Vec::new();
//     let mut num = 0;
//     let mut sign = 1;
//     let chars: Vec<char> = s.chars().collect();
    
//     for (i, &c) in chars.iter().enumerate() {
//         match c {
//             '[' => {
//                 stack.push(NestedInteger::new_list());
//             }
//             '-' => {
//                 sign = -1;
//             }
//             '0'..='9' => {
//                 num = num * 10 + (c as i32 - '0' as i32);
//             }
//             ',' | ']' => {
//                 // If previous character was a digit, add the number
//                 if i > 0 && chars[i-1].is_digit(10) {
//                     if let Some(top) = stack.last_mut() {
//                         top.add(NestedInteger::new_int(sign * num));
//                     }
//                 }
//                 // Reset number and sign
//                 num = 0;
//                 sign = 1;
                
//                 // If closing bracket and multiple levels, complete sublist
//                 if c == ']' && stack.len() > 1 {
//                     let completed = stack.pop().unwrap();
//                     stack.last_mut().unwrap().add(completed);
//                 }
//             }
//             _ => {}
//         }
//     }
    
//     stack.pop().unwrap()
// }

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
