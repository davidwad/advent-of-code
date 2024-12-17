package main

import (
	"container/heap"
	"fmt"
	"math"
	"strconv"
	"utils"
)

type Direction int

const (
	Up Direction = iota
	Right
	Down
	Left
)

type Pos struct {
	i int
	j int
}

func getForward(p Pos, dir Direction) Pos {
	switch dir {
	case Up:
		return Pos{p.i - 1, p.j}
	case Right:
		return Pos{p.i, p.j + 1}
	case Down:
		return Pos{p.i + 1, p.j}
	case Left:
		return Pos{p.i, p.j - 1}
	default:
		panic("unexpected direction")
	}
}

func getRight(p Pos, dir Direction) Pos {
	switch dir {
	case Up:
		return Pos{p.i, p.j + 1}
	case Right:
		return Pos{p.i + 1, p.j}
	case Down:
		return Pos{p.i, p.j - 1}
	case Left:
		return Pos{p.i - 1, p.j}
	default:
		panic("unexpected direction")
	}
}

func getLeft(p Pos, dir Direction) Pos {
	switch dir {
	case Up:
		return Pos{p.i, p.j - 1}
	case Right:
		return Pos{p.i - 1, p.j}
	case Down:
		return Pos{p.i, p.j + 1}
	case Left:
		return Pos{p.i + 1, p.j}
	default:
		panic("unexpected direction")
	}
}

func hash(p Pos) string {
	return fmt.Sprintf("%d|%d", p.i, p.j)
}

func shortestPath(start, end Pos, maze [][]rune, distances map[string]int) (int, map[string]int) {
	visited := make(map[string]bool)
	directions := make(map[string]Direction)
	directions[hash(start)] = Right
	pq := make(utils.PriorityQueue, 0)

	item := &utils.Item{
		Value:    start,
		Priority: 0,
	}
	heap.Push(&pq, item)

	for {
		if pq.Len() == 0 {
			panic("no squares in pq")
		}
		closest := heap.Pop(&pq).(*utils.Item).Value.(Pos)
		if closest == end {
			//printMazeTrail(maze, directions)
			return distances[hash(closest)], distances
		}

		cHash := hash(closest)
		dir := directions[cHash]
		visited[cHash] = true

		//printMazeVisited(maze, visited)

		forward := getForward(closest, dir)
		left := getLeft(closest, dir)
		right := getRight(closest, dir)

		// Forward
		h := hash(forward)
		_, ok := visited[h]
		od, _ := distances[h]
		if !ok && od < math.MaxInt {
			d := min(distances[cHash]+1, od)
			distances[h] = d
			heap.Push(&pq, &utils.Item{
				Value:    forward,
				Priority: d,
			})
			directions[h] = dir
		}

		// Right
		h = hash(right)
		_, ok = visited[h]
		od, _ = distances[h]
		if !ok && od < math.MaxInt {
			d := min(distances[cHash]+1001, od)
			distances[h] = d
			heap.Push(&pq, &utils.Item{
				Value:    right,
				Priority: d,
			})
			directions[h] = (dir + 1) % 4
		}

		// Left
		h = hash(left)
		_, ok = visited[h]
		od, _ = distances[h]
		if !ok && od < math.MaxInt {
			d := min(distances[cHash]+1001, od)
			distances[h] = d
			heap.Push(&pq, &utils.Item{
				Value:    left,
				Priority: d,
			})
			if dir == 0 {
				directions[h] = 3
			} else {
				directions[h] = dir - 1
			}

		}

		//fmt.Println(distances[hash(Pos{7, 4})])
	}
}

// 7|5: 3009
// 7|4: 4011

func walk(p, end Pos, distances map[string]int, visited map[string]bool, maze [][]rune) {
	visited[hash(p)] = true
	//printMazeVisited(maze, visited)
	if p == end {
		return
	}
	neighbours := []Pos{
		{p.i - 1, p.j},
		{p.i, p.j + 1},
		{p.i + 1, p.j},
		{p.i, p.j - 1},
	}
	minDist := math.MaxInt
	for _, np := range neighbours {
		d, ok := distances[hash(np)]
		if ok {
			if d < minDist {
				minDist = d
			}
		}
	}
	for _, np := range neighbours {
		d, ok := distances[hash(np)]
		_, v := visited[hash(np)]
		if ok {
			if d == minDist && !v {
				//fmt.Println(hash(p))
				walk(np, end, distances, visited, maze)
			}
		}
	}
}

func printMaze(maze [][]rune) {
	for _, row := range maze {
		for _, char := range row {
			fmt.Print(string(char))
		}
		fmt.Println()
	}
}

func printMazeDistances(maze [][]rune, distances map[string]int) {
	for i, row := range maze {
		for j, char := range row {
			res, ok := distances[hash(Pos{i, j})]
			if char == '.' && ok {
				fmt.Print(strconv.Itoa(res % 10))
			} else {
				fmt.Print(string(char))
			}
		}
		fmt.Println()
	}
}

func printMazeTrail(maze [][]rune, directions map[string]Direction) {
	for i, row := range maze {
		for j, char := range row {
			dir, ok := directions[hash(Pos{i, j})]
			if ok {
				switch dir {
				case Up:
					fmt.Print("^")
				case Right:
					fmt.Print(">")
				case Down:
					fmt.Print("v")
				case Left:
					fmt.Print("<")
				}
			} else {
				fmt.Print(string(char))
			}

		}
		fmt.Println()
	}
}

func printMazeVisited(maze [][]rune, visited map[string]bool) {
	for i, row := range maze {
		for j, char := range row {
			_, ok := visited[hash(Pos{i, j})]
			if ok {
				fmt.Print("O")
			} else {
				fmt.Print(string(char))
			}

		}
		fmt.Println()
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\16\\example.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	maze := make([][]rune, 0)
	distances := make(map[string]int)

	var startPos Pos
	var endPos Pos
	idx := 0
	for i, line := range lines {
		row := make([]rune, 0)
		for j, char := range line {
			row = append(row, char)
			pos := Pos{i, j}
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
		maze = append(maze, row)
	}

	d, newDists := shortestPath(startPos, endPos, maze, distances)

	visited := make(map[string]bool)
	walk(endPos, startPos, newDists, visited, maze)

	//printMazeVisited(maze, visited)
	fmt.Println(d)
	//fmt.Println(visited)
	fmt.Println(len(visited))
}
