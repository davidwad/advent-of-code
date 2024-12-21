package main

import (
	"container/heap"
	"fmt"
	"math"
	"utils"
)

type Pos struct {
	x int
	y int
}

func hash(p Pos) string {
	return fmt.Sprintf("%d|%d", p.x, p.y)
}

func insideMap(p Pos, width, height int) bool {
	return p.x >= 1 && p.x < width-1 && p.y >= 1 && p.y < height-1
}

func getNeighbours(p Pos) []Pos {
	return []Pos{
		{p.x, p.y - 1},
		{p.x, p.y + 1},
		{p.x - 1, p.y},
		{p.x + 1, p.y},
	}
}

func shortestPath(start, end Pos, width, height int, distances map[string]int) int {
	debugIdx := 0

	visited := make(map[string]bool)
	pq := make(utils.PriorityQueue, 0)

	item := &utils.Item{
		Value:    start,
		Priority: 0,
	}
	heap.Push(&pq, item)
	distances[hash(start)] = 0

	for {
		if pq.Len() == 0 {
			fmt.Println(debugIdx)
			panic("priority queue is empty")
		}
		closest := heap.Pop(&pq).(*utils.Item).Value.(Pos)
		if closest == end {
			return distances[hash(closest)]
		}

		cHash := hash(closest)
		visited[cHash] = true
		d := distances[cHash] + 1

		for _, nb := range getNeighbours(closest) {
			h := hash(nb)
			_, vOk := visited[h]
			od, dOk := distances[h]
			if insideMap(nb, width, height) && !vOk && distances[h] < math.MaxInt && (!dOk || d < od) {
				distances[h] = d
				heap.Push(&pq, &utils.Item{
					Value:    nb,
					Priority: d,
				})
			}
		}
		debugIdx++
	}
}

func printMap(width, height int, distances map[string]int) {
	for y := range height {
		for x := range width {
			d, ok := distances[hash(Pos{x, y})]
			if ok {
				if d == math.MaxInt {
					fmt.Print("#")
					continue
				}
			}
			fmt.Print(".")
		}
		fmt.Println()
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\20\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	width := len(lines[0])
	height := len(lines)
	distances := make(map[string]int)

	var startPos Pos
	var endPos Pos
	idx := 0
	for y, line := range lines {
		for x, char := range line {
			pos := Pos{x, y}
			h := hash(pos)
			switch char {
			case '.':
				distances[h] = math.MaxInt / 2
			case '#':
				distances[h] = math.MaxInt
			case 'S':
				startPos = pos
			case 'E':
				distances[h] = math.MaxInt / 2
				endPos = pos
			}
			idx++
		}
	}

	tempDist := make(map[string]int)
	for k, v := range distances {
		tempDist[k] = v
	}
	origDist := shortestPath(startPos, endPos, width, height, tempDist)
	timeSaves := make(map[string]int)
	for x := 1; x < width-1; x++ {
		for y := 1; y < height-1; y++ {
			p := Pos{x, y}
			tempDist = make(map[string]int)
			for k, v := range distances {
				tempDist[k] = v
			}
			tempDist[hash(p)] = math.MaxInt / 2
			dist := shortestPath(startPos, endPos, width, height, tempDist)
			timeSaves[hash(p)] = origDist - dist
		}
	}
	sum := 0
	for _, v := range timeSaves {
		if v >= 100 {
			sum++
		}
	}
	fmt.Println(sum)
}
