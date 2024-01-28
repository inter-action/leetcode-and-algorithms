
let assert = require("node:assert");


/**
 * @param {number[][]} matrix
 * @return {void} Do not return anything, modify matrix in-place instead.
 */
var rotate = function(matrix) {
  const swap = (array, i, j)=> {
    let t = array[i];
    array[i] = array[j]
    array[j] = t;
  }

  const swapMatrix = (matrix, ai, aj, bi, bj) => {
    let t = matrix[ai][aj]
    matrix[ai][aj] = matrix[bi][bj]
    matrix[bi][bj] = t
  }

  let rows = matrix.length;
  let cols = matrix[0].length


  for (let i = 0; i<rows; i++) {
    // swap values along the i == j diagonal line
    for (j = i + 1; j < cols; j++) {
      swapMatrix(matrix, i, j, j, i);
    }

    // swap horizontally
    let si = 0;
    let sj = cols - 1;
    while(si < sj) {
      swap(matrix[i], si, sj)
      si++;
      sj--;
    }
  }
};


// 15, 13, 2, 5
// [
// [5,1,9,11],
// [2,4,8,10],
// [13,3,6,7],
// [15,14,12,16]]

let result = [[1,2,3],[4,5,6],[7,8,9]]
rotate(result)
console.log('result: ', result)

result = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
rotate(result)
console.log('result: ', result)
