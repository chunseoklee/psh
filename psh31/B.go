package main

import (
	"bufio"
	"fmt"
	"os"
)

const (
	MAX int = 1002
	H   int = 0
	V   int = 1
)

var (
	cur_max int = 0
	N       int
	M       int
	i       int
	a       [MAX][MAX]int
	c1, c2  [MAX][MAX]int // [0] for --> [1] for |
	c3, c4  [MAX][MAX]int
)

func maX(a int, b int) int {
	var ret int
	ret = a
	if a < b {
		ret = b
	}
	return ret
}

func print_c() {
	fmt.Printf("c1 : [H V]\n")
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			fmt.Printf("%d ", c1[i][j])
		}
		fmt.Printf("\n")
	}

	fmt.Printf("c3 : [H V]\n")
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			fmt.Printf("%d ", c3[i][j])
		}
		fmt.Printf("\n")
	}

	fmt.Printf("c2 : [H V]\n")
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			fmt.Printf("%d ", c2[i][j])
		}
		fmt.Printf("\n")
	}

	fmt.Printf("c4 : [H V]\n")
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			fmt.Printf("%d ", c4[i][j])
		}
		fmt.Printf("\n")
	}

}

func precomp() {
	// c1 lahua
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			c1[i][j] = maX(c1[i-1][j]+a[i][j], c1[i][j-1]+a[i][j])
		}
	}
	// c3 lahua
	for i = N; i >= 1; i-- {
		for j := M; j >= 1; j-- {
			c3[i][j] = maX(c3[i+1][j]+a[i][j], c3[i][j+1]+a[i][j])
		}
	}

	// c2 lahuania
	for i = N; i >= 1; i-- {
		for j := 1; j <= M; j++ {
			c2[i][j] = maX(c2[i+1][j]+a[i][j], c2[i][j-1]+a[i][j])
		}
	}

	// c4 lahuania
	for i = 1; i <= N; i++ {
		for j := M; j >= 1; j-- {
			c4[i][j] = maX(c4[i-1][j]+a[i][j], c4[i][j+1]+a[i][j])
		}
	}

}

func solve() {
	for i = 2; i < N; i++ {
		for j := 2; j < M; j++ {
			var v1 int = c1[i][j-1] + c3[i][j+1] + c2[i+1][j] + c4[i-1][j]
			var v2 int = c1[i-1][j] + c3[i+1][j] + c2[i][j-1] + c4[i][j+1]
			if maX(v1, v2) > cur_max {
				cur_max = maX(v1, v2)
			}
		}
	}
	fmt.Printf("%d\n", cur_max)
}

func main() {
	input := bufio.NewReader(os.Stdin)
	// 1. read input
	fmt.Fscanf(input, "%d %d\n", &N, &M)
	for i = 1; i <= N; i++ {
		for j := 1; j <= M; j++ {
			fmt.Fscanf(input, "%d ", &a[i][j])
		}
	}

	precomp()
	//print_c()

	// 2. solve
	solve()

	return
}
