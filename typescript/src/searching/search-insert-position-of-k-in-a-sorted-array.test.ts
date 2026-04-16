import { describe, it } from "node:test";
import * as assert from "node:assert";
import { searchInsertK } from "./search-insert-position-of-k-in-a-sorted-array.js";

describe("test add suit", () => {
  it("search-insert-position-of-k-in-a-sorted-array: case 1", () => {
    let arr = [1, 3, 5, 6];
    let k = 5;

    assert.equal(searchInsertK(arr, k), 2);
  });

  it("search-insert-position-of-k-in-a-sorted-array: case 2", () => {
    let arr = [1, 3, 5, 6];
    let k = 2;
    assert.equal(searchInsertK(arr, k), 1);
  });
});
