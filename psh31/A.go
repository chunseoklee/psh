package main

import (
	"bufio"
	"fmt"
	"os"
)

var N int64
var i int64
var a [100001]int64
var c [100001]int64
var l [100001]int64

func comp_l() {
	for i = 1; i <= 100000; i++ {
		l[a[i]]++
	}
}

func solve() {
	c[0] = 0
	c[1] = l[1]

	for i = 2; i <= 100000; i++ {
		// MAX
		c[i] = c[i-1]
		if c[i] < (c[i-2] + i*l[i]) {
			c[i] = c[i-2] + i*l[i]
		}
	}

	fmt.Printf("%v\n", c[100000])
}

func main() {
	input := bufio.NewReader(os.Stdin)
	// 1. read input
	fmt.Fscanf(input, "%d\n", &N)
	for i = 1; i <= N; i++ {
		fmt.Fscanf(input, "%d", &a[i])
	}
	comp_l()

	// 2. solve
	solve()

	return
}
