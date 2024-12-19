package main

import (
	"fmt"
	"slices"
	"strings"
	"utils"
)

func isDesignPossible(design string, patterns []string, cache map[string]bool) bool {
	res, ok := cache[design]
	if ok {
		return res
	}
	if slices.Contains(patterns, design) {
		cache[design] = true
		return true
	}
	for i := 1; i < len(design); i++ {
		if isDesignPossible(design[:i], patterns, cache) && isDesignPossible(design[i:], patterns, cache) {
			cache[design] = true
			return true
		}
	}
	cache[design] = false
	return false
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\19\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	patterns := strings.Split(lines[0], ", ")
	sum := 0
	for i := 2; i < len(lines); i++ {
		cache := make(map[string]bool)
		if isDesignPossible(lines[i], patterns, cache) {
			sum++
		}
	}

	fmt.Println(sum)
}
