package main

import (
	"fmt"
	"slices"
	"utils"
)

type Direction int

const (
	Up Direction = iota
	Right
	Down
	Left
	Unknown
)

type Coordinate struct {
	I int
	J int
}

type Guard struct {
	Pos Coordinate
	Dir Direction
}

func collideUp(guard Guard, obstacles []Coordinate) (int, bool) {
	coords := make([]int, 0)
	for _, obstacle := range obstacles {
		if obstacle.J == guard.Pos.J && obstacle.I < guard.Pos.I {
			coords = append(coords, obstacle.I)
		}
	}
	if len(coords) == 0 {
		return -1, false
	}
	return slices.Max(coords) + 1, true
}

func collideRight(guard Guard, obstacles []Coordinate) (int, bool) {
	coords := make([]int, 0)
	for _, obstacle := range obstacles {
		if obstacle.I == guard.Pos.I && obstacle.J > guard.Pos.J {
			coords = append(coords, obstacle.J)
		}
	}
	if len(coords) == 0 {
		return -1, false
	}
	return slices.Min(coords) - 1, true
}

func collideDown(guard Guard, obstacles []Coordinate) (int, bool) {
	coords := make([]int, 0)
	for _, obstacle := range obstacles {
		if obstacle.J == guard.Pos.J && obstacle.I > guard.Pos.I {
			coords = append(coords, obstacle.I)
		}
	}
	if len(coords) == 0 {
		return -1, false
	}
	return slices.Min(coords) - 1, true
}

func collideLeft(guard Guard, obstacles []Coordinate) (int, bool) {
	coords := make([]int, 0)
	for _, obstacle := range obstacles {
		if obstacle.I == guard.Pos.I && obstacle.J < guard.Pos.J {
			coords = append(coords, obstacle.J)
		}
	}
	if len(coords) == 0 {
		return -1, false
	}
	return slices.Max(coords) + 1, true
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\6\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	obstacles := make([]Coordinate, 0)
	guard := Guard{}
	finish := false
	visited := make([][]bool, 0)
	numVisited := 0

	for i, line := range lines {
		visited = append(visited, make([]bool, 0))
		for j, char := range line {
			switch string(char) {
			case "#":
				obstacles = append(obstacles, Coordinate{i, j})
			case "^":
				guard.Pos = Coordinate{i, j}
				guard.Dir = Up
			}
			visited[i] = append(visited[i], false)
		}
	}
	visited[guard.Pos.I][guard.Pos.J] = true

	for {
		switch guard.Dir {
		case Up:
			i, collision := collideUp(guard, obstacles)
			if !collision {
				for idx := 0; idx < guard.Pos.I; idx++ {
					visited[idx][guard.Pos.J] = true
				}
				finish = true
			} else {
				for idx := i; idx < guard.Pos.I; idx++ {
					visited[idx][guard.Pos.J] = true
				}
				guard.Pos.I = i
				guard.Dir = Right
			}
		case Right:
			j, collision := collideRight(guard, obstacles)
			if !collision {
				for idx := guard.Pos.J + 1; idx < len(lines[0]); idx++ {
					visited[guard.Pos.I][idx] = true
				}
				finish = true
			} else {
				for idx := guard.Pos.J + 1; idx <= j; idx++ {
					visited[guard.Pos.I][idx] = true
				}
				guard.Pos.J = j
				guard.Dir = Down
			}
		case Down:
			i, collision := collideDown(guard, obstacles)
			if !collision {
				for idx := guard.Pos.I + 1; idx < len(lines); idx++ {
					visited[idx][guard.Pos.J] = true
				}
				finish = true
			} else {
				for idx := guard.Pos.I + 1; idx <= i; idx++ {
					visited[idx][guard.Pos.J] = true
				}
				guard.Pos.I = i
				guard.Dir = Left
			}
		case Left:
			j, collision := collideLeft(guard, obstacles)
			if !collision {
				for idx := 0; idx < guard.Pos.J; idx++ {
					visited[guard.Pos.I][idx] = true
				}
				finish = true
			} else {
				for idx := j; idx < guard.Pos.J; idx++ {
					visited[guard.Pos.I][idx] = true
				}
				guard.Pos.J = j
				guard.Dir = Up
			}
		case Unknown:
			// This should not happen
		}
		if finish {
			break
		}
	}
	for _, row := range visited {
		for _, v := range row {
			if v {
				numVisited++
			}
		}
	}
	fmt.Println(numVisited)
}
