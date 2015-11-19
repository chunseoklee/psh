package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	MAX int = 100001
)

var (
	N    string
	QN   int
	i, j int
	Q    [MAX][2]string
	s, t string
	str  string
)

func max(a int, b int) int {
	var ret int
	ret = a
	if a < b {
		ret = b
	}
	return ret
}

func solve() {
	for i = 1; i <= QN; i++ {
	}
}

func main() {
	input := bufio.NewReader(os.Stdin)
	// 1. read input
	fmt.Fscanf(input, "%s\n%d\n", &N, &QN)

	for i = 1; i <= QN; i++ {
		fmt.Fscanf(input, "%s\n", &str)

		if len(str) == 3 {
			fmt.Sscanf(str, "%s->\n", &Q[i][0])
			Q[i][1] = ""
		} else {
			fmt.Sscanf(str, "%s->%s\n", &Q[i][0], &Q[i][1])
		}

	}

	fmt.Printf("%s\n", N)
	fmt.Printf("%v\n%v\n", Q[1], Q[2])

	// 2. solve
	solve()

	return
}
