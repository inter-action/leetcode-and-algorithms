import { describe, it } from "node:test";
import * as assert from "node:assert";
import {
  reverseKGroup,
  ListNode,
  findRange,
  reverse,
} from "./reverse-nodes-in-k-group.js";

describe("ListNode", () => {
  it("#toList/fromList", () => {
    // const [1,2,3,4,5], k = 2
    const head = ListNode.fromList([1, 2, 3, 4, 5]);
    assert.deepStrictEqual(head.toList(), [1, 2, 3, 4, 5]);
  });
});

describe("reverse-nodes-in-k-group", () => {
  it.only("#case1", () => {
    const head = ListNode.fromList([1, 2, 3, 4, 5]);
    assert.deepStrictEqual(reverseKGroup(head, 2)?.toList(), [2, 1, 4, 3, 5]);
  });
});

describe("reverse-nodes-in-k-group: utils function", () => {
  it("#findRange #case1", () => {
    // const [1,2,3,4,5], k = 2
    const head = ListNode.fromList([1, 2, 3, 4, 5]);
    const range = findRange(head, 2);
    assert.ok(range != null);
    assert.equal(range.val, 2);
  });

  it("#findRange #case1", () => {
    // const [1,2,3,4,5], k = 2
    const head = ListNode.fromList([1, 2, 3, 4, 5]);
    let end = findRange(head, 2);
    assert.ok(end != null);
    assert.equal(end.val, 2);

    end = findRange(end.next!, 2);
    assert.ok(end != null);
    assert.equal(end.val, 4);

    end = findRange(end.next!, 2);
    assert.ok(end == null);
  });

  it("#findRange #case1", () => {});

  it("#reverse #case1", () => {
    // const [1,2,3,4,5], k = 2
    const head = ListNode.fromList([1, 2, 3, 4, 5]);
    let end = findRange(head, 2);
    assert.ok(end != null);
    assert.equal(end.val, 2);
    let range = reverse(head, end);

    assert.deepStrictEqual(range?.newHead.toList(), [2, 1]);

    let h2 = range.next!;
    console.log("h2: ", h2.val);
    end = findRange(h2, 2);
    assert.ok(end != null);
    assert.equal(end.val, 4);

    range = reverse(h2, end);
    assert.deepStrictEqual(range?.newHead.toList(), [4, 3]);
  });
});
