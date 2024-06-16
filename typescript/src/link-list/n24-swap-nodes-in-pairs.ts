// https://leetcode.cn/problems/swap-nodes-in-pairs/solutions/444474/liang-liang-jiao-huan-lian-biao-zhong-de-jie-di-91/

import { ListNode } from "./common";

type Nullable<T> = T | null;

// the official solutions is more elegant
export function swapPairs(head: ListNode | null): ListNode | null {
  if (!head || !head.next) return head;
  if (!head.next.next) {
    let next = head.next;
    next.next = head;
    head.next = null;
    return next;
  }

  let remaining = head.next.next;
  head.next.next = null;

  let swappedRemaining = swapPairs(remaining);
  let newHead = swapPairs(head);
  newHead!.next!.next = swappedRemaining;
  return newHead;
}

// export function swapPairs(head: ListNode | null): ListNode | null {
//   if (!head || !head.next) return head;
//   if (!head.next.next) return rotatePair(head);

//   let remaining = head.next.next;
//   let newHead = rotatePair(head);
//   let swappedRemaining = swapPairs(remaining);
//   newHead.next!.next = swappedRemaining;
//   return newHead;
// }

function rotatePair(head: ListNode) {
  let i = 0;

  let iter = rotate(head);
  let continueOn = true;

  while (true) {
    i++;
    if (i >= 3) {
      continueOn = false;
    }

    let { done, value } = iter.next(continueOn);
    if (done) {
      return value;
    }
  }
}

// to call this function, it must has at least 2 nodes
// this function always returns a valid ListNode
function* rotate(head: ListNode): Generator<ListNode, ListNode, boolean> {
  let cur: ListNode | null = head;
  let pre = null;

  while (cur) {
    let next: Nullable<ListNode> = cur.next;
    cur.next = pre;
    pre = cur;

    let continueOn = yield cur;
    if (!continueOn) {
      return cur;
    }

    if (next) {
      cur = next;
    } else {
      break;
    }
  }

  return cur;
}
