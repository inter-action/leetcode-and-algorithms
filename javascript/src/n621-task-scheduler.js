
let assert = require("node:assert");

/**
 * @param {character[]} tasks
 * @param {number} n
 * @return {number}
 */
//Input: tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
//


const IDLE = 'idle'
class Scheduler {
  constructor(tasks, n) {
    this.tasks = tasks
    this.counts = this.tasks.reduce((p, c)=> {
      if (p[c] == null) {
        p[c] = 0
      } 
      p[c]++
      return p
    }, {})
    this.blocked = this.tasks.reduce((p,c)=>{
      if (p[c] == null) {
        p[c] = 0
      }
      return p
    }, {})

    this.n = n
    this.total = Object.keys(this.counts).length
  }

  take(){
    if (!this.total) return null;
    let result = null;

    // [A, A, B, C]
    //  ^ take A
    //  block A from taking again, blocked[A] = this.n
    //  choose remaining qualified elements 
    //    if None insert an idle.
    //    decrease blocked for all elements

    // take the one has the most repeating elements
    let max = 0 
    // can use heap to optimize this for loop
    for (let [key, value] of Object.entries(this.blocked)) {
      if (value === 0 && this.counts[key]) {
        if (this.counts[key] > max) {
          result = key
          max = this.counts[key]
        }
      }
    }

    Object.keys(this.blocked).map((k)=> {
      if (k != result && this.blocked[k] > 0) {
        this.blocked[k] -= 1
      }
    })

    if (result != null) {
      this.counts[result] -= 1;
      if (this.counts[result] == 0) {
        this.total -= 1;
      }
      this.blocked[result] = this.n;
      return result;
    } else {
      return IDLE;
    }
  }
}

var leastInterval = function(tasks, n) {
  let scheduler = new Scheduler(tasks, n)
  let result = []
  while(true) {
    let t = scheduler.take()
    if (t == null) {
      break
    }

    result.push(t)
  }

  return result.length
};


let result;
result= leastInterval(["A","A","A","B","B","B"], 2)
assert.equal(result, 8)

result = leastInterval(["A","A","A","B","B","B"], 0)
assert.equal(result, 6)

result = leastInterval(["A","A","A","A","A","A","B","C","D","E","F","G"], 2)
assert.equal(result, 16)


result = leastInterval(["A","A","A","B","B","B", "C","C","C", "D", "D", "E"], 2)
assert.equal(result, 12)
