// https://github.com/microsoft/RustTraining/blob/main/rust-patterns-book/src/ch17-exercises.md
// Create a Pipeline struct that chains transformations. It should support .pipe(f) to add a transformation and .execute(input) to run the full chain.
//

// lessons learned
//  - in `for in` statement, add `&<ref>` for reference, even though `<ref>` is aleady a reference
//  type,
//  -
//
struct Pipeline<T> {
    fns: Vec<Box<dyn Fn(T) -> T>>,
}

impl<T> Pipeline<T> {
    fn new() -> Self {
        Self { fns: vec![] }
    }

    fn pipe(self: &mut Self, f: impl Fn(T) -> T + 'static) -> &mut Self {
        self.fns.push(Box::new(f));
        self
    }

    fn execute(self: &Self, input: T) -> T {
        let mut t = input;

        for f in &self.fns {
            t = f(t);
        }

        t
        // self.transforms.into_iter().fold(input, |val, f| f(val))
    }
}

fn main() {
    let result = Pipeline::new()
        .pipe(|s: String| s.trim().to_string())
        .pipe(|s| s.to_uppercase())
        .pipe(|s| format!(">>> {s} <<<"))
        .execute("  hello world  ".to_string());

    println!("{result}"); // >>> HELLO WORLD <<<

    // Numeric pipeline:
    let result = Pipeline::new()
        .pipe(|x: i32| x * 2)
        .pipe(|x| x + 10)
        .pipe(|x| x * x)
        .execute(5);

    println!("{result}"); // (5*2 + 10)^2 = 400
}
