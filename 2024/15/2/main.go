package main

import (
	"fmt"
	"utils"
)

type Pos struct {
	i int
	j int
}

type Box struct {
	i  int
	jl int
	jr int
}

func getBoxIdx(p Pos, boxes []Box) int {
	for idx, box := range boxes {
		if box.i == p.i && (box.jl == p.j || box.jr == p.j) {
			return idx
		}
	}
	return -1
}

func destination(direction rune, pos Pos) Pos {
	switch direction {
	case '^':
		return Pos{pos.i - 1, pos.j}
	case '>':
		return Pos{pos.i, pos.j + 1}
	case 'v':
		return Pos{pos.i + 1, pos.j}
	case '<':
		return Pos{pos.i, pos.j - 1}
	default:
		panic("unexpected direction")
	}
}

func destinations(direction rune, box Box) []Pos {
	switch direction {
	case '^':
		return []Pos{
			{box.i - 1, box.jl},
			{box.i - 1, box.jr},
		}
	case '>':
		return []Pos{
			{box.i, box.jr + 1},
		}
	case 'v':
		return []Pos{
			{box.i + 1, box.jl},
			{box.i + 1, box.jr},
		}
	case '<':
		return []Pos{
			{box.i, box.jl - 1},
		}
	default:
		panic("unexpected direction")
	}
}

func move(direction rune, pos Pos, warehouse [][]rune, boxes *[]Box) Pos {
	nextPos := destination(direction, pos)
	destObj := warehouse[nextPos.i][nextPos.j]
	switch destObj {
	case '#':
		return pos
	case '.':
		idx := getBoxIdx(nextPos, *boxes)
		if idx == -1 {
			return nextPos
		}
		box := (*boxes)[idx]
		if canPush(direction, box, warehouse, boxes) {
			push(direction, box, warehouse, boxes)
			return nextPos
		} else {
			return pos
		}
	default:
		panic("unexpected rune in warehouse map")
	}
}

func canPush(direction rune, box Box, warehouse [][]rune, boxes *[]Box) bool {
	destPos := destinations(direction, box)
	success := true
	for _, pos := range destPos {
		boxIdx := getBoxIdx(pos, *boxes)
		if boxIdx == -1 {
			if warehouse[pos.i][pos.j] == '#' {
				success = false
			}
		} else {
			if !canPush(direction, (*boxes)[boxIdx], warehouse, boxes) {
				success = false
			}
		}
	}
	return success
}

func push(direction rune, box Box, warehouse [][]rune, boxes *[]Box) {
	destPos := destinations(direction, box)
	for _, pos := range destPos {
		boxIdx := getBoxIdx(pos, *boxes)
		if boxIdx != -1 {
			push(direction, (*boxes)[boxIdx], warehouse, boxes)
		}
	}

	boxIdx := getBoxIdx(Pos{box.i, box.jl}, *boxes)
	switch direction {
	case '^':
		(*boxes)[boxIdx] = Box{box.i - 1, box.jl, box.jr}
	case '>':
		(*boxes)[boxIdx] = Box{box.i, box.jl + 1, box.jr + 1}
	case 'v':
		(*boxes)[boxIdx] = Box{box.i + 1, box.jl, box.jr}
	case '<':
		(*boxes)[boxIdx] = Box{box.i, box.jl - 1, box.jr - 1}
	default:
		panic("unexpected direction")
	}
}

func coordinateSum(boxes []Box) int {
	sum := 0
	for _, box := range boxes {
		sum += box.i*100 + box.jl
	}
	return sum
}

func printWarehouse(warehouse [][]rune, boxes []Box, i, j int) {
	for ii, row := range warehouse {
		for jj, object := range row {
			boxIdx := getBoxIdx(Pos{ii, jj}, boxes)
			if boxIdx == -1 {
				if i == ii && j == jj {
					fmt.Print("@")
				} else {
					fmt.Print(string(object))
				}
			} else {
				if boxes[boxIdx].jl == jj {
					fmt.Print("[")
				} else if boxes[boxIdx].jr == jj {
					fmt.Print("]")
				}
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
	boxes := make([]Box, 0)
	moves := make([]rune, 0)
	pos := Pos{}
	for i, line := range lines {
		if len(line) == 0 {
			readingMoves = true
			continue
		}

		if readingMoves {
			row := make([]rune, 0)
			for _, char := range line {
				row = append(row, char)
			}
			moves = append(moves, row...)
		} else {
			row := make([]rune, 0)
			for j, char := range line {
				switch char {
				case '@':
					pos.i = i
					pos.j = 2 * j
					row = append(row, '.')
					row = append(row, '.')
				case 'O':
					boxes = append(boxes, Box{i, 2 * j, 2*j + 1})
					row = append(row, '.')
					row = append(row, '.')
				default:
					row = append(row, char)
					row = append(row, char)
				}
			}
			warehouse = append(warehouse, row)
		}
	}

	for _, m := range moves {
		pos = move(m, pos, warehouse, &boxes)
	}

	fmt.Println(coordinateSum(boxes))
}
