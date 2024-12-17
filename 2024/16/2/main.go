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

func hashDir(p Pos, dir Direction) string {
	return fmt.Sprintf("%d|%d|%d", p.i, p.j, dir)
}

func shortestPath(start, end Pos, prio Direction, maze [][]rune, distances map[string]int) (int, map[string]int) {
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
		visited[hashDir(closest, dir)] = true

		//printMazeVisited(maze, visited)

		forward := getForward(closest, dir)
		left := getLeft(closest, dir)
		right := getRight(closest, dir)

		// Forward
		h := hash(forward)
		_, ok := visited[hashDir(forward, dir)]
		od, _ := distances[h]
		if !ok && od < math.MaxInt {
			//var d int
			//if distances[hash(getForward(forward, dir))] == math.MaxInt {
			//	d = min(distances[cHash]+1001, od)
			//} else {
			//	d = min(distances[cHash]+1, od)
			//}

			//d := min(distances[cHash]+1, od)
			d := distances[cHash] + 1
			if d < od {
				distances[h] = d
				heap.Push(&pq, &utils.Item{
					Value:    forward,
					Priority: d,
				})
				directions[h] = dir
			}

		}

		// Right
		h = hash(right)
		newDir := (dir + 1) % 4
		_, ok = visited[hashDir(right, newDir)]
		od, _ = distances[h]
		if !ok && od < math.MaxInt {
			d := distances[cHash] + 1001
			if d < od {
				distances[h] = d
				if prio == Left {
					heap.Push(&pq, &utils.Item{
						Value:    right,
						Priority: d + 2000,
					})
				} else {
					heap.Push(&pq, &utils.Item{
						Value:    right,
						Priority: d,
					})
				}
				directions[h] = newDir
			}
			//d := min(distances[cHash]+1001, od)

		}

		// Left
		h = hash(left)
		if dir == 0 {
			newDir = 3
		} else {
			newDir = dir - 1
		}
		_, ok = visited[hashDir(left, newDir)]
		od, _ = distances[h]
		if !ok && od < math.MaxInt {
			d := distances[cHash] + 1001
			if d < od {
				distances[h] = d
				if prio == Right {
					heap.Push(&pq, &utils.Item{
						Value:    left,
						Priority: d + 2000,
					})
				} else {
					heap.Push(&pq, &utils.Item{
						Value:    left,
						Priority: d,
					})
				}

				directions[h] = newDir
			}
			//d := min(distances[cHash]+1001, od)

			//if dir == 0 {
			//	directions[h] = 3
			//} else {
			//	directions[h] = dir - 1
			//}

		}

		//fmt.Println("------------------------------")
		//pp := Pos{9, 3}
		//if closest == pp {
		//	fmt.Print(".")
		//}
	}
}

// 7|5: 3009
// 7|4: 4011

func walk(p, end Pos, distances map[string]int, visited map[string]bool, maze [][]rune) {
	visited[hash(p)] = true
	//pp := Pos{7, 5}
	//if p == pp {
	//	printMazeVisited(maze, visited)
	//	fmt.Println(distances[hash(Pos{7, 5})])
	//	fmt.Println(distances[hash(Pos{7, 4})])
	//	fmt.Println(distances[hash(Pos{8, 5})])
	//	//fmt.Println()
	//}

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
			if (d == minDist || utils.Abs(d-minDist) == 1000) && !v {
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

	//d, newDists := shortestPath(startPos, endPos, maze, distances)
	d, dLeft := shortestPath(startPos, endPos, Left, maze, distances)
	maze = make([][]rune, 0)
	distances = make(map[string]int)

	idx = 0
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
	d, dRight := shortestPath(startPos, endPos, Right, maze, distances)

	visitedLeft := make(map[string]bool)
	walk(endPos, startPos, dLeft, visitedLeft, maze)
	visitedRight := make(map[string]bool)
	walk(endPos, startPos, dRight, visitedRight, maze)

	//fmt.Println(visitedLeft)
	//fmt.Println(visitedRight)

	//printMazeVisited(maze, visited)
	fmt.Println(d)
	//fmt.Println(visited)
	fmt.Println(len(visitedLeft))
	fmt.Println(len(visitedRight))
	//printMazeVisited(maze, visited)
	//fmt.Println(distances[hash(Pos{7, 5})])
	//fmt.Println(distances[hash(Pos{7, 4})])
	//fmt.Println(distances[hash(Pos{8, 5})])
	//fmt.Println(distances[hash(Pos{8, 3})])
}
