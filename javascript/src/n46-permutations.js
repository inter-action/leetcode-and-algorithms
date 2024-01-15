var permute = function(nums) {

  const f = (collect, remaining = [], result = []) => {
    //       ^ using cb to reverse exe flow
    if (!remaining || !remaining.length) return collect(result)

    for (let i = 0; i<remaining.length; i++) {
      let e = remaining[i]
      let r = [...remaining]
      // ! can't use splice's return
      r.splice(i, 1);

      f(collect, r, [...result, e])
    }
  }

  var results = []

  f(e=> results.push(e), nums, [])

  return results
};


// main
console.log(permute([1, 2, 3]))

