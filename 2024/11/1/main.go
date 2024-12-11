package main

import (
	"fmt"
	"strconv"
	"strings"
	"utils"
)

func blink(a, k, kMax int) int {
	if k == kMax {
		return 1
	}
	if a == 0 {
		return blink(1, k+1, kMax)
	}
	s := strconv.Itoa(a)
	if len(s)%2 == 0 {
		a1, _ := strconv.Atoi(s[:len(s)/2])
		a2, _ := strconv.Atoi(s[len(s)/2:])
		return blink(a1, k+1, kMax) + blink(a2, k+1, kMax)
	}
	return blink(a*2024, k+1, kMax)
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\11\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	blinks := 25
	sum := 0
	split := strings.Split(lines[0], " ")
	for _, s := range split {
		a, _ := strconv.Atoi(s)
		sum += blink(a, 0, blinks)
	}

	fmt.Println(sum)
}
