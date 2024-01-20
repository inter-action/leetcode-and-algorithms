use std::collections::HashMap;
use std::fmt::Debug;
use std::string::*;

#[derive(Debug)]
struct Solution;

impl Solution {
    // #[allow(dead_code)]
    pub fn check_inclusion(s1: String, s2: String) -> bool {
        let s1 = &s1;
        let s2 = &s2;

        if s1.len() > s2.len() {
            return false;
        }

        let chars = s2.chars();
        let mut expected = HashMap::<char, i32>::new();
        let mut window = HashMap::<char, i32>::new();
        let mut matched = 0;

        for char in s1.chars() {
            expected
                .entry(char)
                .and_modify(|value| *value += 1)
                .or_insert(1);
        }

        for (r, c) in chars.clone().enumerate() {
            let mut reach_end = false;
            if expected.contains_key(&c) {
                window.entry(c).and_modify(|value| *value += 1).or_insert(1);

                if expected.get(&c) == window.get(&c) {
                    matched += 1;
                }
            }

            for (l, c) in chars.clone().enumerate() {
                // we could have a match
                if (r - l) <= s1.len() {
                    reach_end = true;
                    break;
                }

                if expected.contains_key(&c) {
                    let value = window.get_mut(&c).unwrap();
                    *value -= 1;

                    if expected.get(&c) == window.get(&c) {
                        matched -= 1;
                    }
                }
            }

            if matched == s1.len() && reach_end {
                return true;
            }
        }

        false
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_a() {
        let s1 = String::from("ab");
        let s2 = String::from("eidbaooo");

        assert_eq!(Solution::check_inclusion(s1, s2), true);
    }

    #[test]
    fn test_should_return_false() {
        let s1 = String::from("axb");
        let s2 = String::from("eidbaooo");

        assert_eq!(Solution::check_inclusion(s1, s2), false);
    }
}
