export class ListNode {
  val: number;
  next: ListNode | null;
  constructor(val?: number, next?: ListNode | null) {
    this.val = val === undefined ? 0 : val;
    this.next = next === undefined ? null : next;
  }

  static convertToArray(head: Nullable<ListNode>) {
    if (!head) return [];

    let cur: Nullable<ListNode> = head;
    let res = [];

    while (cur) {
      res.push(cur.val);
      cur = cur.next;
    }

    return res;
  }

  static fromArray(arr: number[]): ListNode {
    if (!arr.length) throw new Error("must have at least 1 element");

    let head: Nullable<ListNode> = null;
    let cur: Nullable<ListNode> = null;

    arr.forEach((e) => {
      if (!head) {
        head = new ListNode(e, null);
        cur = head;
      } else {
        cur!.next = new ListNode(e, null);
        cur = cur!.next;
      }
    });

    return head!;
  }
}

type Nullable<T> = T | null;
