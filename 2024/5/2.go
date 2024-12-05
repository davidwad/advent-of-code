package main

import (
	"fmt"
	"strconv"
	"strings"
	"utils"
)

type Rule struct {
	L int
	R int
}

func updateIsUnsafe(updates []int, rules map[int][]int) bool {
	past := make(map[int]bool)
	for _, update := range updates {
		forbidden := rules[update]
		for _, f := range forbidden {
			_, ok := past[f]
			if ok {
				return true
			}
		}
		past[update] = true
	}
	return false
}

func reorderUpdate(updates []int, rules []Rule) []int {
	for _, rule := range rules {
		switchPlaces(&updates, rule.L, rule.R)
	}
	return updates
}

func switchPlaces(updates *[]int, l int, r int) {
	idxL := -1
	idxR := -1
	for i := range len(*updates) {
		if (*updates)[i] == l {
			idxL = i
		}
		if (*updates)[i] == r {
			idxR = i
		}
	}
	if idxR > -1 && idxL > -1 && idxR < idxL {
		(*updates)[idxR] = l
		(*updates)[idxL] = r
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\5\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	splitIdx := -1
	var rules []Rule
	ruleMap := make(map[int][]int)
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
		rules = append(rules, Rule{L: l, R: r})
		val, ok := ruleMap[l]
		if !ok {
			ruleMap[l] = make([]int, 0)

		}
		val = append(val, r)
		ruleMap[l] = val
		rules = append(rules, Rule{L: l, R: r})
	}

	// Parse updates and apply logic
	for i := splitIdx + 1; i < len(lines); i++ {
		splits := strings.Split(lines[i], ",")
		updates := make([]int, 0)
		for _, split := range splits {
			num, _ := strconv.Atoi(split)
			updates = append(updates, num)
		}
		unsafe := updateIsUnsafe(updates, ruleMap)
		if unsafe {
			for {
				updates = reorderUpdate(updates, rules)
				if !updateIsUnsafe(updates, ruleMap) {
					break
				}
			}
			sum += updates[len(updates)/2]
		}
	}
	fmt.Println(sum)
}
