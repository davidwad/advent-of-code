package main

import (
	"container/heap"
	"fmt"
	"math"
	"regexp"
	"strconv"
	"utils"
)

type Pos struct {
	x int
	y int
}

func hash(p Pos) string {
	return fmt.Sprintf("%d|%d", p.x, p.y)
}

func insideMemory(p Pos, size int) bool {
	return p.x >= 0 && p.x < size && p.y >= 0 && p.y < size
}

func getNeighbours(p Pos) []Pos {
	return []Pos{
		{p.x, p.y - 1},
		{p.x, p.y + 1},
		{p.x - 1, p.y},
		{p.x + 1, p.y},
	}
}

func shortestPath(start, end Pos, size int, distances map[string]int) int {
	debugIdx := 0

	visited := make(map[string]bool)
	pq := make(utils.PriorityQueue, 0)

	item := &utils.Item{
		Value:    start,
		Priority: 0,
	}
	heap.Push(&pq, item)

	for {
		if pq.Len() == 0 {
			return -1
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
			if insideMemory(nb, size) && !vOk && distances[h] < math.MaxInt && (!dOk || d < od) {
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

func printBytesVisited(size int, distances map[string]int, visited map[string]bool) {
	for y := range size {
		for x := range size {
			d, ok := distances[hash(Pos{x, y})]
			if ok {
				if d == math.MaxInt {
					fmt.Print("#")
					continue
				}
			}
			_, ok = visited[hash(Pos{x, y})]
			if ok {
				fmt.Print("O")
				continue
			}
			fmt.Print(".")
		}
		fmt.Println()
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\18\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	size := 71
	start := Pos{0, 0}
	end := Pos{size - 1, size - 1}

	re := regexp.MustCompile(`(\d+),(\d+)`)

	distances := make(map[string]int)
	for i := range len(lines) {
		match := re.FindStringSubmatch(lines[i])
		x, _ := strconv.Atoi(match[1])
		y, _ := strconv.Atoi(match[2])
		p := Pos{x, y}
		distances[hash(p)] = math.MaxInt
		tempDist := make(map[string]int)
		for k, v := range distances {
			tempDist[k] = v
		}
		d := shortestPath(start, end, size, tempDist)
		if d == -1 {
			fmt.Println(fmt.Sprintf("%d,%d", x, y))
			break
		}
	}
}
