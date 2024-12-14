package main

import (
	"fmt"
	"regexp"
	"strconv"
	"utils"
)

type Robot struct {
	x  int
	y  int
	vx int
	vy int
}

func printRobots(robots []Robot, xMax, yMax int) {
	for y := range yMax {
		for x := range xMax {
			count := 0
			for _, r := range robots {
				if r.x == x && r.y == y {
					count++
				}
			}
			if count == 0 {
				fmt.Print(".")
			} else {
				fmt.Print(count)
			}
		}
		fmt.Println()
	}
}

func teleport(xy, xyMax int) int {
	for {
		if xy >= 0 && xy < xyMax {
			return xy
		}
		if xy < 0 {
			xy = xyMax + xy
		} else if xy >= xyMax {
			xy = xy % xyMax
		}
	}
}

func safetyFactor(robots []Robot, xMax, yMax int) int {
	xMiddle := xMax / 2
	yMiddle := yMax / 2
	counts := []int{0, 0, 0, 0}
	for _, r := range robots {
		if r.x < xMiddle && r.y < yMiddle {
			counts[0] = counts[0] + 1
		}
		if r.x > xMiddle && r.y < yMiddle {
			counts[1] = counts[1] + 1
		}
		if r.x < xMiddle && r.y > yMiddle {
			counts[2] = counts[2] + 1
		}
		if r.x > xMiddle && r.y > yMiddle {
			counts[3] = counts[3] + 1
		}
	}
	return counts[0] * counts[1] * counts[2] * counts[3]
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\14\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	iterations := 100
	xMax := 101
	yMax := 103
	re := regexp.MustCompile(`p=(\d+),(\d+) v=(-?\d+),(-?\d+)`)

	robots := make([]Robot, 0)
	for _, line := range lines {
		match := re.FindStringSubmatch(line)
		x, _ := strconv.Atoi(match[1])
		y, _ := strconv.Atoi(match[2])
		vx, _ := strconv.Atoi(match[3])
		vy, _ := strconv.Atoi(match[4])
		robots = append(robots, Robot{x, y, vx, vy})
	}
	//printRobots(robots, xMax, yMax)
	//fmt.Println("-----------------------------------------------")

	for i := range len(robots) {
		r := &robots[i]
		r.x = teleport(r.x+r.vx*iterations, xMax)
		r.y = teleport(r.y+r.vy*iterations, yMax)
	}
	//printRobots(robots, xMax, yMax)
	fmt.Println(safetyFactor(robots, xMax, yMax))

}
