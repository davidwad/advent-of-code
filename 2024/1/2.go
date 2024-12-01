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
	counts := make(map[int]int)
	var sum int
	for _, line := range lines {
		split := strings.Split(line, "   ")
		l, _ := strconv.Atoi(split[0])
		r, _ := strconv.Atoi(split[1])

		lNums = append(lNums, l)
		rNums = append(rNums, r)
	}
	slices.Sort(rNums)

	prevNum := -1
	count := 0
	for _, num := range rNums {
		if prevNum != num {
			counts[prevNum] = count
			prevNum = num
			count = 0
		}
		count++
	}
	counts[prevNum] = count

	for _, num := range lNums {
		c, ok := counts[num]
		if ok {
			sum += num * c
		}
	}

	fmt.Println(sum)
}
