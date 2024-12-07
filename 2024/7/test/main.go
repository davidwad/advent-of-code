package main

import "fmt"

func nextProduct(a []int, r int) func() []int {
	p := make([]int, r)
	x := make([]int, len(p))
	return func() []int {
		p = p[:len(x)]
		for i, xi := range x {
			p[i] = a[xi]
		}
		for i := len(x) - 1; i >= 0; i-- {
			x[i]++
			if x[i] < len(a) {
				break
			}
			x[i] = 0
			if i <= 0 {
				x = x[0:0]
				break
			}
		}
		return p
	}
}

func main() {
	a := []int{0, 1}
	k := 3
	np := nextProduct(a, k)
	for {
		product := np()
		if len(product) == 0 {
			break
		}
		fmt.Println(product)
	}
}
