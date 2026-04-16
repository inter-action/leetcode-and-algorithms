// - dereferencing
//  - *T is dereferencing
//  - let a = *T; is dereferencing and moving out
// - `assume_init_drop` must be called, if you reset the whole with another MaybeUninit::uninit, the
//  Drop for T would never be triggerred
// - const
//  - const variadic type - const N: usize
//  - const expression - const { MaybeUninit::uninit() }
// - unsafe { std::slice::from_raw_parts(self.data.as_ptr() as *const T, self.len) }
//  - create a slice from consecutive memory

use std::mem::MaybeUninit;

pub struct FixedVec<T, const N: usize> {
    data: [MaybeUninit<T>; N],
    len: usize,
}

impl<T, const N: usize> FixedVec<T, N> {
    pub fn new() -> Self {
        FixedVec {
            data: [const { MaybeUninit::uninit() }; N],
            len: 0,
        }
    }

    pub fn push(&mut self, value: T) -> Result<(), T> {
        if self.len >= N {
            return Err(value);
        }
        // SAFETY: len < N, so data[len] is within bounds.
        self.data[self.len] = MaybeUninit::new(value);
        self.len += 1;
        Ok(())
    }

    pub fn pop(&mut self) -> Option<T> {
        if self.len == 0 {
            return None;
        }
        self.len -= 1;
        // SAFETY: data[len] was initialized (len was > 0 before decrement).
        // or using std::mem:read
        Some(unsafe { self.data[self.len].assume_init_read() })
    }

    pub fn as_slice(&self) -> &[T] {
        // SAFETY: data[0..len] are all initialized, and MaybeUninit<T>
        // has the same layout as T.
        unsafe { std::slice::from_raw_parts(self.data.as_ptr() as *const T, self.len) }
    }

    pub fn len(&self) -> usize {
        self.len
    }
    pub fn is_empty(&self) -> bool {
        self.len == 0
    }
}

impl<T, const N: usize> Drop for FixedVec<T, N> {
    fn drop(&mut self) {
        // SAFETY: data[0..len] are initialized — drop each one.
        for i in 0..self.len {
            unsafe {
                self.data[i].assume_init_drop();
            }
        }
    }
}

fn main() {
    let mut v = FixedVec::<String, 4>::new();
    v.push("hello".into()).unwrap();
    v.push("world".into()).unwrap();
    assert_eq!(v.as_slice(), &["hello", "world"]);
    assert_eq!(v.pop(), Some("world".into()));
    assert_eq!(v.len(), 1);
    // Drop cleans up remaining "hello"
}
