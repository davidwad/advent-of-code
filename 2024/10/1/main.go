package main

import (
	"fmt"
	"utils"
)

type Coordinate struct {
	I int
	J int
}

func hash(i, j, cols int) int {
	return i*cols + j
}

func ascendingNeighbors(i, j int, elevationMap [][]int) []Coordinate {
	neighbours := make([]Coordinate, 0)
	coords := []Coordinate{{i, j - 1}, {i, j + 1}, {i - 1, j}, {i + 1, j}}
	for _, coord := range coords {
		ii := coord.I
		jj := coord.J
		insideMap := ii >= 0 && ii < len(elevationMap) && jj >= 0 && jj < len(elevationMap[0])
		if insideMap && elevationMap[ii][jj] == elevationMap[i][j]+1 {
			neighbours = append(neighbours, Coordinate{ii, jj})
		}
	}
	return neighbours
}

func walk(i, j int, peaks map[int]bool, elevationMap [][]int) {
	if elevationMap[i][j] == 9 {
		peaks[hash(i, j, len(elevationMap[0]))] = true
	}
	neighbours := ascendingNeighbors(i, j, elevationMap)
	for _, coord := range neighbours {
		walk(coord.I, coord.J, peaks, elevationMap)
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\10\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	elevationMap := make([][]int, 0)
	trailheads := make([]Coordinate, 0)

	for i, line := range lines {
		elevationMap = append(elevationMap, make([]int, 0))
		for j, char := range line {
			elevationMap[i] = append(elevationMap[i], int(char-'0'))
			if char == '0' {
				trailheads = append(trailheads, Coordinate{i, j})
			}
		}
	}
	
	sum := 0
	for _, trailhead := range trailheads {
		peaks := make(map[int]bool)
		walk(trailhead.I, trailhead.J, peaks, elevationMap)
		sum += len(peaks)
	}

	fmt.Println(sum)
}
