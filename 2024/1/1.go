package main

import (
	"fmt"
	"slices"
	"strconv"
	"strings"
	"utils"
)

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\1\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	var lNums []int
	var rNums []int
	var sum int
	for _, line := range lines {
		split := strings.Split(line, "   ")
		l, _ := strconv.Atoi(split[0])
		r, _ := strconv.Atoi(split[1])

		lNums = append(lNums, l)
		rNums = append(rNums, r)
	}
	slices.Sort(lNums)
	slices.Sort(rNums)

	for i := range len(lNums) {
		sum += utils.Abs(lNums[i] - rNums[i])
	}

	fmt.Println(sum)
}
