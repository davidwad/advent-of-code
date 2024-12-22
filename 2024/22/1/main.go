package main

import (
	"fmt"
	"strconv"
	"utils"
)

const Pruner = 16777216

func evolve(x uint64, n int) uint64 {
	for range n {
		x = (x ^ (x * 64)) % Pruner
		x = (x ^ (x / 32)) % Pruner
		x = (x ^ (x * 2048)) % Pruner
	}
	return x
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\22\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	sum := uint64(0)
	for _, line := range lines {
		x, _ := strconv.Atoi(line)
		sum += evolve(uint64(x), 2000)
	}
	fmt.Println(sum)
}
