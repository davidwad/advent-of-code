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

type CheatPos struct {
	p     Pos
	steps int
}

func hash(p Pos) string {
	return fmt.Sprintf("%d|%d", p.x, p.y)
}

func distance(p1, p2 Pos) int {
	return utils.Abs(p1.x-p2.x) + utils.Abs(p1.y-p2.y)
}

func insideMap(p Pos, size int) bool {
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

func shortestPath(start, end Pos, size int, distances map[string]int) (int, map[string]Pos) {
	debugIdx := 0

	visited := make(map[string]Pos)
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
			return distances[hash(closest)], visited
		}

		cHash := hash(closest)
		visited[cHash] = closest
		d := distances[cHash] + 1

		for _, nb := range getNeighbours(closest) {
			h := hash(nb)
			_, vOk := visited[h]
			od, dOk := distances[h]
			if insideMap(nb, size) && !vOk && distances[h] < math.MaxInt && (!dOk || d < od) {
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

func cheatPos(p Pos, r, size int) []CheatPos {
	pos := make([]CheatPos, 0)
	for x := range size {
		for y := range size {
			t := Pos{x, y}
			d := distance(p, t)
			if d <= r {
				pos = append(pos, CheatPos{t, d})
			}
		}
	}
	return pos
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

	steps := 20
	threshold := 100

	size := len(lines)
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

	_, visited := shortestPath(startPos, endPos, size, distances)
	sum := 0
	for k, v := range visited {
		origDist := distances[k]
		pos := cheatPos(v, steps, size)
		for _, dist := range pos {
			destDist := distances[hash(dist.p)]
			if destDist == math.MaxInt {
				continue
			}
			timeSave := destDist - dist.steps - origDist
			if timeSave >= threshold {
				sum++
			}
		}
	}
	fmt.Println(sum)
}
