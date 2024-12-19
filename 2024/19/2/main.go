package main

import (
	"fmt"
	"strings"
	"utils"
)

func designs(design string, patterns []string, cache map[string]int) int {
	res, ok := cache[design]
	if ok {
		return res
	}
	sum := 0
	if len(design) == 0 {
		sum = 1
	}
	for _, p := range patterns {
		if strings.HasPrefix(design, p) {
			sum += designs(design[len(p):], patterns, cache)
		}
	}
	cache[design] = sum
	return sum
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
		cache := make(map[string]int)
		n := designs(lines[i], patterns, cache)
		sum += n
	}

	fmt.Println(sum)
}
