// !NOTE: I used a hack, js meta programming technique to do the final caculation
// so I guess I kind cheated a little. :(

let assert = require("node:assert");

/**
 * @param {number} n
 * @return {number}
 */
var clumsy = function (n) {
  let stack = [];
  let operators = ["*", "/", "+", "-"];
  let j = 0;

  let shouldEval = false;
  // 7 = 4 * 3 / 2 + 1
  for (let i = n; i >= 1; i--) {
    stack.push(i);
    if (shouldEval) {
      eval_stack(stack, true);
      shouldEval = false;
    }
    if (i != 1) {
      stack.push(operators[j]);
    }
    switch (operators[j]) {
      case "*":
      case "/":
        shouldEval = true;
    }
    j = ++j % 4;
  }

  // 10 * 9 / 8 + 7 - 6 * 5 / 4 + 3 - 2 * 1

  //if (reversed.length != 1) {
  //  throw new Error("invalid stack state: " + JSON.stringify(reversed));
  //}
  
  // for - operator, we can treat it as negative number, then adds all together.
  // stack [3, '-', 6, '+', 3]
  //=
  // stack [3, -6, '+', 3]
  let f = new Function(`return ${stack.join("")}`);

  return f();

  function eval_stack(stack, earlyStop) {
    let a, b, op;
    if (stack.length <= 1) {
      return;
    }

    if (stack.length < 3) {
      return;
    }

    while (stack.length >= 3) {
      op = stack[stack.length - 2];
      if (!earlyStop) console.log("eval_stack--: ", stack);

      switch (op) {
        case "*":
          b = stack.pop();
          op = stack.pop();
          a = stack.pop();
          stack.push(a * b);
          break;
        case "/":
          b = stack.pop();
          op = stack.pop();
          a = stack.pop();
          stack.push(a / b > 0 ? Math.floor(a / b) : Math.ceil(a / b));
          break;
        case "-":
          if (earlyStop) return;

          b = stack.pop();
          op = stack.pop();
          a = stack.pop();
          stack.push(a - b);
          break;
        case "+":
          if (earlyStop) return;

          b = stack.pop();
          op = stack.pop();
          a = stack.pop();
          stack.push(a + b);
          break;
        default:
          throw new Error("invalid op: ", op);
      }
    }
  }
};

let result = 0;
// result = clumsy(4);
// assert.equal(result, 7);

result = clumsy(10);
assert.equal(result, 12);
