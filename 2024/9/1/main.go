package main

import (
	"fmt"
	"utils"
)

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\9\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	empty := make([]int, 0)
	blocks := make([]int, 0)

	idx := 0
	nBlocks := 0
	for i, char := range lines[0] {
		if i%2 == 0 {
			for range int(char - '0') {
				blocks = append(blocks, nBlocks)
				idx++
			}
			nBlocks++
		} else {
			for range int(char - '0') {
				empty = append(empty, idx)
				blocks = append(blocks, -1)
				idx++
			}
		}
	}

	for {
		emptyIdx := empty[0]
		if emptyIdx >= len(blocks) {
			break
		}
		if blocks[len(blocks)-1] != -1 {
			blocks[emptyIdx] = blocks[len(blocks)-1]
			empty = empty[1:]
		}
		blocks = blocks[:len(blocks)-1]
	}

	sum := 0
	for i, id := range blocks {
		sum += i * id
	}
	fmt.Println(sum)
}
