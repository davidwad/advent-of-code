package main

import (
	"fmt"
	"utils"
)

func destination(direction rune, i, j int) (int, int) {
	switch direction {
	case '^':
		return i - 1, j
	case '>':
		return i, j + 1
	case 'v':
		return i + 1, j
	case '<':
		return i, j - 1
	default:
		panic("unexpected direction")
	}
}

func move(direction rune, i, j int, warehouse *[][]rune) (int, int) {
	iDest, jDest := destination(direction, i, j)
	destObj := (*warehouse)[iDest][jDest]
	switch destObj {
	case '#':
		return i, j
	case 'O':
		if push(direction, iDest, jDest, warehouse) {
			return iDest, jDest
		} else {
			return i, j
		}
	case '.':
		return iDest, jDest
	default:
		panic("unexpected rune in warehouse map")
	}
}

func push(direction rune, i, j int, warehouse *[][]rune) bool {
	iDest, jDest := destination(direction, i, j)
	switch (*warehouse)[iDest][jDest] {
	case '#':
		return false
	case '.':
		(*warehouse)[iDest][jDest] = 'O'
		(*warehouse)[i][j] = '.'
		return true
	case 'O':
		if push(direction, iDest, jDest, warehouse) {
			(*warehouse)[iDest][jDest] = 'O'
			(*warehouse)[i][j] = '.'
			return true
		} else {
			return false
		}
	default:
		panic("unexpected rune in warehouse map")
	}
}

func coordinateSum(warehouse [][]rune) int {
	sum := 0
	for i, row := range warehouse {
		for j, object := range row {
			if object == 'O' {
				sum += 100*i + j
			}
		}
	}
	return sum
}

func printWarehouse(warehouse [][]rune, i, j int) {
	for ii, row := range warehouse {
		for jj, object := range row {
			if i == ii && j == jj {
				fmt.Print("@")
			} else {
				fmt.Print(string(object))
			}
		}
		fmt.Println()
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\15\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	readingMoves := false
	warehouse := make([][]rune, 0)
	moves := make([]rune, 0)
	var i, j int
	for ii, line := range lines {
		if len(line) == 0 {
			readingMoves = true
			continue
		}
		row := make([]rune, 0)
		for jj, char := range line {
			if char == '@' {
				i = ii
				j = jj
				row = append(row, '.')
			} else {
				row = append(row, char)
			}
		}
		if readingMoves {
			moves = append(moves, row...)
		} else {
			warehouse = append(warehouse, row)
		}
	}

	for _, m := range moves {
		i, j = move(m, i, j, &warehouse)
	}

	fmt.Println(coordinateSum(warehouse))
}
