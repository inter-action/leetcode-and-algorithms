// todo: merge this to ./common.ts
export class ListNode {
  val: number;
  next: ListNode | null;
  constructor(val?: number, next?: ListNode | null) {
    this.val = val === undefined ? 0 : val;
    this.next = next === undefined ? null : next;
  }

  static fromList(list: number[]): ListNode {
    let head = new ListNode();
    let cur = head;

    for (let i = 0; i < list.length; i++) {
      cur.val = list[i]!;
      if (i != list.length - 1) {
        cur.next = new ListNode();
        cur = cur.next;
      }
    }

    cur.next = null;

    return head;
  }

  toList(): number[] {
    let cur: ListNode | null = this;
    let r = [];

    while (true) {
      if (!cur) return r;
      r.push(cur.val);
      cur = cur.next;
    }
  }
}

export function reverseKGroup(
  head: ListNode | null,
  k: number,
): ListNode | null {
  let current = head;
  if (!current) return null;

  let newHead = head;
  let pEnd: ListNode | null = null;
  let isFirst = true;

  while (current) {
    let endNode = findRange(current, k);
    if (!endNode) {
      if (pEnd) {
        pEnd.next = current;
      }
      return newHead;
    }
    let range = reverse(current, endNode);
    if (!range) {
      return newHead;
    }

    if (isFirst) {
      newHead = range.newHead;
      pEnd = range.newTail;
      isFirst = false;
    } else {
      pEnd!.next = range.newHead;
      pEnd = range.newTail;
    }
    current = range.next;
  }

  return newHead;
}

export function reverse(
  startNode: ListNode,
  endNode: ListNode,
): { newHead: ListNode; newTail: ListNode; next: ListNode | null } | null {
  let newTail: ListNode | null = null;
  let current: ListNode = startNode;
  let p: ListNode | null = null;
  while (current != endNode) {
    let next: ListNode | null = current.next;
    current.next = p;
    if (!p) {
      newTail = current;
    }
    p = current;
    current = next!;
  }

  // current == endNode
  let next = current.next;
  current.next = p;

  return {
    newHead: current,
    newTail: newTail!,
    next,
  };
}

export function findRange(
  startNode: ListNode,
  targetSize: number,
): ListNode | null {
  if (targetSize == 0) throw new Error("invalid targetSize");

  let cur: ListNode | null = startNode;
  let s = 1;
  while (true) {
    if (!cur) break;
    cur = cur.next;
    s++;
    if (s == targetSize) {
      break;
    }
  }

  if (s == targetSize) {
    return cur;
  }

  return null;
}
