package main

import (
	"fmt"
	"utils"
)

func parseInput(lines []string) ([][]int, [][]int) {
	keys := make([][]int, 0)
	locks := make([][]int, 0)

	i := 0
	key := true
	for {
		if i >= len(lines) {
			break
		}
		heights := []int{0, 0, 0, 0, 0}
		ii := 0
		for {
			if i >= len(lines) || len(lines[i]) == 0 {
				if key {
					keys = append(keys, heights)
				} else {
					locks = append(locks, heights)
				}
				i++
				break
			}

			line := lines[i]
			if line == "#####" {
				if ii == 0 {
					key = false
					i++
					ii++
					continue
				} else if ii == 6 {
					key = true
					i++
					ii++
					continue
				}
			}

			for iii, r := range line {
				if r == '#' {
					heights[iii]++
				}
			}

			i++
			ii++
		}
	}
	return locks, keys
}

func fit(lock, key []int) bool {
	for i := range lock {
		if lock[i]+key[i] > 5 {
			return false
		}
	}

	return true
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\25\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	locks, keys := parseInput(lines)

	sum := 0
	for _, l := range locks {
		for _, k := range keys {
			if fit(l, k) {
				sum++
			}
		}
	}

	fmt.Println(sum)
}
