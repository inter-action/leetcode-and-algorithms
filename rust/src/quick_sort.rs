use std::fmt::Debug;

fn pivot<T: PartialOrd + Debug>(v: &mut [T]) -> usize {
    let mut p = 0;

    for i in 1..v.len() {
        if v[i] < v[p] {
            v.swap(p + 1, i);
            v.swap(p, p + 1); // make pivot consistent
            p += 1;
        }
    }

    p
}

fn quick_sort<T>(v: &mut [T])
where
    T: Debug + PartialOrd,
{
    if v.len() <= 1 {
        return;
    }

    let p = pivot(v);
    println!("{:?}, pivot: {}", v, p);

    let (a, b) = v.split_at_mut(p);
    quick_sort(a);
    quick_sort(&mut b[1..]);
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_quick_sort() {
        let mut v = vec![2, 4, 3, 1];
        quick_sort(&mut v);

        assert_eq!(v, vec![1, 2, 3, 4])
    }
}
