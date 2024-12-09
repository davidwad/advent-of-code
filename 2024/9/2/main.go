package main

import (
	"fmt"
	"utils"
)

type Hole struct {
	startIdx int
	size     int
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\9\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	blocks := make([]int, 0)
	blockIndices := make(map[int][]int)
	holes := make([]Hole, 0)

	idx := 0
	nBlocks := 0
	for i, char := range lines[0] {
		if i%2 == 0 {
			for range int(char - '0') {
				blocks = append(blocks, nBlocks)
				bi, ok := blockIndices[nBlocks]
				if ok {
					blockIndices[nBlocks] = append(bi, idx)
				} else {
					blockIndices[nBlocks] = []int{idx}
				}
				idx++
			}
			nBlocks++
		} else {
			hole := Hole{idx, 0}
			for range int(char - '0') {
				blocks = append(blocks, -1)
				idx++
			}
			hole.size = idx - hole.startIdx
			if hole.size > 0 {
				holes = append(holes, hole)
			}
		}
	}

	for id := nBlocks - 1; id >= 0; id-- {
		originIndices := blockIndices[id]

		holeIdx := 0
		for _, hole := range holes {
			if hole.size >= len(originIndices) && hole.startIdx < originIndices[0] {
				dIdx := hole.startIdx
				for _, oIdx := range originIndices {
					blocks[dIdx] = blocks[oIdx]
					blocks[oIdx] = -1
					dIdx++
				}
				if hole.size == len(originIndices) {
					holes = append(holes[:holeIdx], holes[holeIdx+1:]...)
				} else {
					hole.startIdx = hole.startIdx + len(originIndices)
					hole.size = hole.size - len(originIndices)
					holes[holeIdx] = hole
				}
				break
			}
			holeIdx++
		}
	}

	sum := 0
	for i, id := range blocks {
		if id != -1 {
			sum += i * id
		}

	}
	fmt.Println(sum)
}
