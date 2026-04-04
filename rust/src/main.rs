fn main() {
    println!("Hello, world!");
}

fn add(a: i32, b: i32) -> i32 {
    a + b
}

#[test]
fn it_works() {
    assert_eq!(add(1, 2), 4);
}
