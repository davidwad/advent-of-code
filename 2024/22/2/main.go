package main

import (
	"fmt"
	"math"
	"strconv"
	"utils"
)

const Pruner = 16777216

func hash(x1, x2, x3, x4 int) string {
	return fmt.Sprintf("%d|%d|%d|%d", x1, x2, x3, x4)
}

func evolve(x, n int) ([]int, []int, []int) {
	numbers := make([]int, 0)
	prices := make([]int, 0)
	changes := make([]int, 0)

	numbers = append(numbers, x)
	prices = append(prices, x%10)
	for range n {
		x = (x ^ (x * 64)) % Pruner
		x = (x ^ (x / 32)) % Pruner
		x = (x ^ (x * 2048)) % Pruner
		numbers = append(numbers, x)
		prices = append(prices, x%10)
		changes = append(changes, prices[len(prices)-1]-prices[len(prices)-2])
	}
	return numbers, prices, changes
}

func fillPriceMap(priceMap map[string]int, prices, changes []int) {
	used := make(map[string]bool)
	for i := 4; i < len(prices); i++ {
		h := hash(changes[i-4], changes[i-3], changes[i-2], changes[i-1])
		_, u := used[h]
		if u {
			continue
		}
		used[h] = true
		p, ok := priceMap[h]
		if ok {
			priceMap[h] = p + prices[i]
		} else {
			priceMap[h] = prices[i]
		}
	}
}

func getMaxTotal(priceMap map[string]int) int {
	maxTotal := math.MinInt
	for _, v := range priceMap {
		if v > maxTotal {
			maxTotal = v
		}
	}
	return maxTotal
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\22\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	priceMap := make(map[string]int)

	for _, line := range lines {
		x, _ := strconv.Atoi(line)
		_, prices, changes := evolve(x, 2000)
		fillPriceMap(priceMap, prices, changes)
	}
	//fmt.Println(priceMap[hash(-2, 1, -1, 3)])
	fmt.Println(getMaxTotal(priceMap))

}

// Each price can be mapped to a sequence of changes
// Find sequence of changes which gives max sum of prices
// Only one price for each buyer can be used

// Idea:
// For each buyer, make list/map of prices and sequences
// For each sequence for all buyers, calculate sum of prices

// Idea:
// For each buyer, make list/map of prices and sequences
// For each buyer, make map between sequences and prize
