package main

import (
	"fmt"
	"slices"
	"time"
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

func exited(lines []string, guard Guard, obstacles []Coordinate) bool {
	finish := false
	visited := make([][]Direction, 0)

	for i := range len(lines) {
		visited = append(visited, make([]Direction, 0))
		for range len(lines[0]) {
			visited[i] = append(visited[i], Unknown)
		}
	}
	visited[guard.Pos.I][guard.Pos.J] = Up

	for {
		switch guard.Dir {
		case Up:
			i, collision := collideUp(guard, obstacles)
			if !collision {
				for idx := 0; idx < guard.Pos.I; idx++ {
					visited[idx][guard.Pos.J] = Up
				}
				finish = true
			} else {
				for idx := i; idx < guard.Pos.I; idx++ {
					if visited[idx][guard.Pos.J] == Up {
						return false
					}
					visited[idx][guard.Pos.J] = Up
				}
				guard.Pos.I = i
				guard.Dir = Right
			}
		case Right:
			j, collision := collideRight(guard, obstacles)
			if !collision {
				for idx := guard.Pos.J + 1; idx < len(lines[0]); idx++ {
					visited[guard.Pos.I][idx] = Right
				}
				finish = true
			} else {
				for idx := guard.Pos.J + 1; idx <= j; idx++ {
					if visited[guard.Pos.I][idx] == Right {
						return false
					}
					visited[guard.Pos.I][idx] = Right
				}
				guard.Pos.J = j
				guard.Dir = Down
			}
		case Down:
			i, collision := collideDown(guard, obstacles)
			if !collision {
				for idx := guard.Pos.I + 1; idx < len(lines); idx++ {
					visited[idx][guard.Pos.J] = Down
				}
				finish = true
			} else {
				for idx := guard.Pos.I + 1; idx <= i; idx++ {
					if visited[idx][guard.Pos.J] == Down {
						return false
					}
					visited[idx][guard.Pos.J] = Down
				}
				guard.Pos.I = i
				guard.Dir = Left
			}
		case Left:
			j, collision := collideLeft(guard, obstacles)
			if !collision {
				for idx := 0; idx < guard.Pos.J; idx++ {
					visited[guard.Pos.I][idx] = Left
				}
				finish = true
			} else {
				for idx := j; idx < guard.Pos.J; idx++ {
					if visited[guard.Pos.I][idx] == Left {
						return false
					}
					visited[guard.Pos.I][idx] = Left
				}
				guard.Pos.J = j
				guard.Dir = Up
			}
		case Unknown:
			// This should not happen
		}
		if finish {
			return true
		}
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\6\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	start := time.Now()

	obstacles := make([]Coordinate, 0)
	guard := Guard{}
	loops := 0

	for i, line := range lines {
		for j, char := range line {
			switch string(char) {
			case "#":
				obstacles = append(obstacles, Coordinate{i, j})
			case "^":
				guard.Pos = Coordinate{i, j}
				guard.Dir = Up
			}
		}
	}

	for i := range len(lines) {
		for j := range len(lines[0]) {
			if !exited(lines, guard, append(obstacles, Coordinate{i, j})) {
				loops++
			}

		}
	}
	duration := time.Since(start)
	fmt.Println(duration)
	fmt.Println(loops)
}
