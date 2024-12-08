package main

import (
	"fmt"
	"utils"
)

type Coordinate struct {
	I int
	J int
}

func (c Coordinate) hash(cols int) int {
	return c.I*cols + c.J
}

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

func makeRange(min, max int) []int {
	a := make([]int, max-min+1)
	for i := range a {
		a[i] = min + i
	}
	return a
}

func antiNodes(c1, c2 Coordinate, rows, cols int) []Coordinate {
	if c1 == c2 {
		return []Coordinate{}
	}
	coords := make([]Coordinate, 0)
	coords = append(coords, c1)
	coords = append(coords, c2)

	iDiff := c1.I - c2.I
	jDiff := c1.J - c2.J
	k := 2
	for {
		i := c1.I - iDiff*k
		j := c1.J - jDiff*k
		if i < 0 || i >= cols {
			break
		}
		if j < 0 || j >= cols {
			break
		}
		coords = append(coords, Coordinate{i, j})
		k++
	}
	return coords
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\8\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	antennas := make(map[rune][]Coordinate)
	anMap := make(map[int]bool)
	for i, line := range lines {
		for j, char := range line {
			if string(char) != "." {
				coords, ok := antennas[char]
				if ok {
					antennas[char] = append(coords, Coordinate{i, j})
				} else {
					antennas[char] = []Coordinate{{i, j}}
				}
			}
		}
	}

	for _, coords := range antennas {
		np := nextProduct(makeRange(0, len(coords)-1), 2)
		for {
			product := np()
			if len(product) == 0 {
				break
			}
			ans := antiNodes(coords[product[0]], coords[product[1]], len(lines), len(lines[0]))
			for _, an := range ans {
				anMap[an.hash(len(lines[0]))] = true
			}
		}
	}
	fmt.Println(len(anMap))
}
