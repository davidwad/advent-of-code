package main

import (
	"fmt"
	"strconv"
	"strings"
	"utils"
)

func safe(levels []int) bool {
	diff := levels[1] - levels[0]
	if utils.Abs(diff) < 1 || utils.Abs(diff) > 3 {
		return false
	}
	positive := diff > 0
	for i := 2; i < len(levels); i++ {
		newDiff := levels[i] - levels[i-1]
		if utils.Abs(newDiff) < 1 || utils.Abs(newDiff) > 3 {
			return false
		}
		if newDiff > 0 != positive {
			return false
		}
	}
	return true
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\2\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	nSafe := 0
	for _, line := range lines {
		var levels []int
		split := strings.Split(line, " ")
		for _, level := range split {
			l, _ := strconv.Atoi(level)
			levels = append(levels, l)

		}
		if safe(levels) {
			nSafe += 1
		}
	}
	fmt.Println(nSafe)
}
