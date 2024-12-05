package main

import (
	"fmt"
	"strconv"
	"strings"
	"utils"
)

func updateIsSafe(updates []int, rules map[int][]int) bool {
	past := make(map[int]bool)
	for _, update := range updates {
		forbidden := rules[update]
		for _, f := range forbidden {
			_, ok := past[f]
			if ok {
				return false
			}
		}
		past[update] = true
	}
	return true
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\5\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	splitIdx := -1
	rules := make(map[int][]int)
	sum := 0

	// Parse rules
	for i := range lines {
		line := lines[i]
		if line == "" {
			splitIdx = i
			break
		}
		nums := strings.Split(line, "|")
		l, _ := strconv.Atoi(nums[0])
		r, _ := strconv.Atoi(nums[1])
		val, ok := rules[l]
		if !ok {
			rules[l] = make([]int, 0)

		}
		val = append(val, r)
		rules[l] = val
	}

	// Parse updates and apply logic
	for i := splitIdx + 1; i < len(lines); i++ {
		splits := strings.Split(lines[i], ",")
		updates := make([]int, 0)
		for _, split := range splits {
			num, _ := strconv.Atoi(split)
			updates = append(updates, num)
		}
		safe := updateIsSafe(updates, rules)
		if safe {
			sum += updates[len(updates)/2]
		}
	}
	fmt.Println(sum)
}
