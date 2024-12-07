package main

import (
	"fmt"
	"strconv"
	"strings"
	"time"
	"utils"
)

type Operation int

const (
	Addition Operation = iota
	Multiplication
)

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

func calculate(operands []int, operators []int) int {
	res := operands[0]
	for i, operator := range operators {
		if operator == int(Addition) {
			res = res + operands[i+1]
		} else if operator == int(Multiplication) {
			res = res * operands[i+1]
		}
	}
	return res
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\7\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	start := time.Now()

	totalSum := 0

	for _, line := range lines {
		s1 := strings.Split(line, ":")
		res, _ := strconv.Atoi(s1[0])
		s2 := strings.Split(s1[1], " ")
		operands := make([]int, 0)
		for _, s := range s2[1:] {
			operand, _ := strconv.Atoi(s)
			operands = append(operands, operand)
		}

		np := nextProduct([]int{0, 1}, len(operands)-1)
		for {
			product := np()
			c := calculate(operands, product)
			if c == res {
				totalSum += res
				break
			}
			if len(product) == 0 {
				break
			}
		}
	}
	fmt.Println(time.Since(start))
	fmt.Println(totalSum)
}
