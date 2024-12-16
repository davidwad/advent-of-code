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

func shortestPath(start, end Pos, maze [][]rune, distances map[string]int) int {
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
			printMazeTrail(maze, directions)
			return distances[hash(closest)]
		}

		cHash := hash(closest)
		dir := directions[cHash]
		visited[cHash] = true

		forward := getForward(closest, dir)
		left := getLeft(closest, dir)
		right := getRight(closest, dir)

		// Forward
		h := hash(forward)
		_, ok := visited[h]
		if !ok && distances[h] < math.MaxInt {
			d := distances[cHash] + 1
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
		if !ok && distances[h] < math.MaxInt {
			d := distances[cHash] + 1001
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
		if !ok && distances[h] < math.MaxInt {
			d := distances[cHash] + 1001
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

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\16\\input.txt"
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

	d := shortestPath(startPos, endPos, maze, distances)

	fmt.Println(d)
}
