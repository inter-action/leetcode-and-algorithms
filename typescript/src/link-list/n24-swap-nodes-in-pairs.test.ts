import { ListNode } from "./common";
import { swapPairs } from "./n24-swap-nodes-in-pairs";

describe("swapPairs", () => {
  test("one element", () => {
    let swaped = swapPairs(ListNode.fromArray([1]));
    let swappedArray = ListNode.convertToArray(swaped);
    compareArray(swappedArray, [1]);
  });

  test("two element", () => {
    let swaped = swapPairs(ListNode.fromArray([1, 2]));
    let swappedArray = ListNode.convertToArray(swaped);
    compareArray(swappedArray, [2, 1]);
  });

  test(">3 elements", () => {
    let swaped = swapPairs(ListNode.fromArray([3, 4, 5]));
    let swappedArray = ListNode.convertToArray(swaped);
    compareArray(swappedArray, [4, 3, 5]);
  });
});

function compareArray<T>(a: T[], b: T[]) {
  expect(a.length).toBe(b.length);
  for (let i = 0; i < a.length; i++) {
    let av = a[i];
    expect(av).toBe(b[i]);
  }
}
