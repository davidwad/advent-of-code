package main

import (
	"fmt"
	"regexp"
	"strconv"
	"utils"
)

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\3\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	sum := 0
	re := regexp.MustCompile(`mul\(\d{1,3},\d{1,3}\)`)
	muls := re.FindAllString(lines[0], -1)
	for _, mul := range muls {
		re = regexp.MustCompile(`\d{1,3}`)
		digits := re.FindAllString(mul, -1)
		l, _ := strconv.Atoi(digits[0])
		r, _ := strconv.Atoi(digits[1])
		sum += l * r
		fmt.Println(mul)
	}
	fmt.Println(sum)
}
