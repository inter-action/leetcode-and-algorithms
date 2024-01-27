let assert = require("node:assert");

// keyword: stack

/**
 * @param {number[]} temperatures
 * @return {number[]}
 */
var dailyTemperatures = function (temperatures) {
  let stack = [];
  let head = null;
  let current = null;

  // create link list for result collecting
  for (let i = 0; i < temperatures.length; i++) {
    if (i == 0) {
      head = Node(temperatures[i], i);
      current = head;
    } else {
      let node = Node(temperatures[i], i);
      current = current.next = node;
    }
  }

  current = head;

  while (current) {
    if (current.index == 0) {
      stack.push(current);
    }

    // found a warmer temperature, pop the stacks
    if (current.value > stack[stack.length - 1].value) {
      while (stack.length && current.value > stack[stack.length - 1].value) {
        let node = stack.pop();
        node.diff = current.index - node.index;
      }
      stack.push(current);
    } else {
      stack.push(current);
    }

    current = current.next;
  }

  current = head;
  let result = [];
  while (current) {
    result.push(current.diff);
    current = current.next;
  }

  return result;
};

function Node(value, index) {
  return {
    value,
    index,
    // link list is used to better collect results
    next: null,
    diff: 0,
  };
}

// Input: temperatures = [73,74,75,71,69,72,76,73]
// Output: [1,1,4,2,1,1,0,0]

// need deepEqual to compare two arrays
let result;
result = dailyTemperatures([73, 74, 75, 71, 69, 72, 76, 73]);
assert.deepEqual(result, [1, 1, 4, 2, 1, 1, 0, 0]);


result = dailyTemperatures([30,40,50,60]);
assert.deepEqual(result, [1,1,1,0]);


result = dailyTemperatures([30,60,90]);
assert.deepEqual(result, [1,1,0]);
