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

	re := regexp.MustCompile(`mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\)`)
	sum := 0
	do := true

	instructions := re.FindAllString(lines[0], -1)
	for _, instruction := range instructions {
		if instruction == "do()" {
			do = true
			continue
		}
		if instruction == "don't()" {
			do = false
			continue
		}
		if do {
			re = regexp.MustCompile(`\d{1,3}`)
			digits := re.FindAllString(instruction, -1)
			l, _ := strconv.Atoi(digits[0])
			r, _ := strconv.Atoi(digits[1])
			sum += l * r
		}
	}
	fmt.Println(sum)
}
