package main

import (
	"fmt"
	"strconv"
	"strings"
	"utils"
)

func blink(a, k, kMax int, blinkMap map[string]int) int {
	res, ok := blinkMap[fmt.Sprintf("%d|%d", k, a)]
	if ok {
		return res
	}
	if k == kMax {
		return 1
	}
	if a == 0 {
		r := blink(1, k+1, kMax, blinkMap)
		blinkMap[fmt.Sprintf("%d|%d", k, a)] = r
		return r
	}
	s := strconv.Itoa(a)
	if len(s)%2 == 0 {
		a1, _ := strconv.Atoi(s[:len(s)/2])
		a2, _ := strconv.Atoi(s[len(s)/2:])
		r1 := blink(a1, k+1, kMax, blinkMap)
		r2 := blink(a2, k+1, kMax, blinkMap)
		blinkMap[fmt.Sprintf("%d|%d", k, a)] = r1 + r2
		return r1 + r2
	}
	r := blink(a*2024, k+1, kMax, blinkMap)
	blinkMap[fmt.Sprintf("%d|%d", k, a)] = r
	return r
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\11\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	blinkMap := make(map[string]int)

	blinks := 75
	sum := 0
	split := strings.Split(lines[0], " ")
	for _, s := range split {
		a, _ := strconv.Atoi(s)
		sum += blink(a, 0, blinks, blinkMap)
	}

	fmt.Println(sum)
}
