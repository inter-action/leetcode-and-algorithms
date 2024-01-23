let assert = require("node:assert");

/**
 * @param {string[]} tokens
 * @return {number}
 */
var evalRPN = function (tokens) {
  let stack = [];

  tokens.forEach((e, i) => {
    let a, b;
    switch (e) {
      case "+":
        b = stack.pop();
        a = stack.pop();
        stack.push(a + b);
        break;
      case "-":
        b = stack.pop();
        a = stack.pop();
        stack.push(a - b);
        break;
      case "*":
        b = stack.pop();
        a = stack.pop();
        stack.push(a * b);
        break;
      case "/":
        b = stack.pop();
        a = stack.pop();
        // ! note: ceil for negative value here.
        // for cpp a/b would equal to this
        stack.push(a / b > 0 ? Math.floor(a/b) : Math.ceil(a/b))
        break;
      default:
        stack.push(+e);
    }
  });

  return stack.pop();
};

let result = 0;
// result = evalRPN(["2", "1", "+", "3", "*"]);
// assert.equal(result, 9);
// // Explanation: ((2 + 1) * 3) = 9
// 
// result = evalRPN([
//   "10",
//   "6",
//   "9",
//   "3",
//   "+",
//   "-11",
//   "*",
//   "/",
//   "*",
//   "17",
//   "+",
//   "5",
//   "+",
// ]);
// assert.equal(result, 22);
// Output: 22


result = evalRPN(["-78","-33","196","+","-19","-","115","+","-","-99","/","-18","8","*","-86","-","-","16","/","26","-14","-","-","47","-","101","-","163","*","143","-","0","-","171","+","120","*","-60","+","156","/","173","/","-24","11","+","21","/","*","44","*","180","70","-40","-","*","86","132","-84","+","*","-","38","/","/","21","28","/","+","83","/","-31","156","-","+","28","/","95","-","120","+","8","*","90","-","-94","*","-73","/","-62","/","93","*","196","-","-59","+","187","-","143","/","-79","-89","+","-"])

// 165
console.log(result)
