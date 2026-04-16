// https://www.geeksforgeeks.org/dsa/search-insert-position-of-k-in-a-sorted-array/

// Given a 0 based sorted array arr[] of distinct integers and an integer k, find the index of k if it is present. If not, return the index where k should be inserted to maintain the sorted order.

// Input: arr[] = [1, 3, 5, 6], k = 5
// Output: 2
// Explanation: Since 5 is found at index 2 as arr[2] = 5, the output is 2.
//
// Input: arr[] = [1, 3, 5, 6], k = 2
// Output: 1
// Explanation: The element 2 is not present in the array, but inserting it at index 1 will maintain the sorted order.

export function searchInsertK(arr: number[], k: number): number {
  if (!arr.length) {
    return 0;
  }

  let l = 0;
  let r = arr.length - 1;
  while (l <= r) {
    let m = Math.ceil((r - l) / 2);
    if (arr[m] == k) {
      return m;
    } else if (arr[m]! > k) {
      if (m - l <= 1) {
        return m;
      } else {
        r = m - 1;
      }
    } else if (arr[m]! < k) {
      if (r - m <= 1) {
        if (r - m == 0) {
          // collide
          return m + 1;
        }
        return r;
      } else {
        l = m + 1;
      }
    }
  }

  throw new Error("never reach here");
}

// Driver Code
let arr = [3];
let k = 2;
console.log(searchInsertK(arr, k));
