package main

import (
	"bufio"
	"container/list"
	"fmt"
	"os"
)

const (
	MAX int = 100001
)

var (
	N          int
	i, j       int
	E          [MAX]*list.List
	TE         [MAX]*list.List
	bad        [MAX]*list.List
	tbad       [MAX]*list.List
	visited    [MAX]bool
	parent     [MAX]int
	bad_child  [MAX]int
	parent_bad [MAX]bool
)

type Stack struct {
	top  *Element
	size int
}

type Element struct {
	value interface{} // All types satisfy the empty interface, so we can store anything here.
	next  *Element
}

// Return the stack's length
func (s *Stack) Len() int {
	return s.size
}

// Push a new element onto the stack
func (s *Stack) Push(value interface{}) {
	s.top = &Element{value, s.top}
	s.size++
}

// Remove the top element from the stack and return it's value
// If the stack is empty, return nil
func (s *Stack) Pop() (value interface{}) {
	if s.size > 0 {
		value, s.top = s.top.value, s.top.next
		s.size--
		return
	}
	return nil
}

func max(a int, b int) int {
	var ret int
	ret = a
	if a < b {
		ret = b
	}
	return ret
}

func solve() {
	result := list.New()

	for i = 1; i <= N; i++ {
		if parent_bad[i] && bad_child[i] == 0 {
			result.PushBack(i)
		}
	}
	fmt.Printf("%d\n", result.Len())
	for e := result.Front(); e != nil; e = e.Next() {
		fmt.Printf("%v ", e.Value)
	}
}

func print() {
	for i = 1; i <= N; i++ {
		for e := TE[i].Front(); e != nil; e = e.Next() {
			fmt.Printf("%d-th node: %v\n", i, e.Value)
		}
	}
}

func maketree(index int) {
	st := new(Stack)
	st.Push(index)

	for st.Len() > 0 {

		visited[index] = true

		for e, eb := E[index].Front(), bad[index].Front(); e != nil; e, eb = e.Next(), eb.Next() {

			var next = e.Value.(int)
			var nextb = eb.Value.(int)
			if visited[next] == false {
				TE[index].PushBack(next)
				tbad[index].PushBack(nextb)
				parent[next] = index
				maketree(next)
			}
		}
	}
}

// return # of bad egdes below this node
func count_badedge_below_node(index int) int {
	if TE[index].Len() == 0 { // leaf
		return 0
	}

	var n_bad int = 0

	for e, eb := TE[index].Front(), tbad[index].Front(); e != nil; e, eb = e.Next(), eb.Next() {
		var next = e.Value.(int)
		var nextb = eb.Value.(int)
		if nextb == 2 {
			n_bad++
			parent_bad[next] = true
		}
		n_bad += count_badedge_below_node(next)
	}

	bad_child[index] = n_bad
	return n_bad
}

func main() {
	input := bufio.NewReader(os.Stdin)
	// 1. read input
	fmt.Fscanf(input, "%d\n", &N)

	for i = 0; i <= N; i++ {
		E[i] = list.New()
		bad[i] = list.New()
		TE[i] = list.New()
		tbad[i] = list.New()
	}
	for i = 1; i <= N-1; i++ {
		var s, t, b int
		fmt.Fscanf(input, "%d %d %d\n", &s, &t, &b)
		E[s].PushBack(t)
		bad[s].PushBack(b)
		E[t].PushBack(s)
		bad[t].PushBack(b)
	}

	// make tree
	maketree(1)
	//print()
	count_badedge_below_node(1)
	// 2. solve
	solve()

	return
}
