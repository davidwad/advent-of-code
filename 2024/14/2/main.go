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

func hash(x, y int) string {
	return fmt.Sprintf("%d,%d", x, y)
}

func hasTriangle(robotMap map[string]bool, xMax, yMax int) bool {
	for x := 3; x < xMax-4; x++ {
		for y := 0; y < yMax-3; y++ {
			hashes := getTriangle(x, y)
			missing := false
			for _, h := range hashes {
				_, ok := robotMap[h]
				if !ok {
					missing = true
					break
				}
			}
			if !missing {
				return true
			}
		}

	}

	return false
}

func getTriangle(tipX, tipY int) []string {
	hashes := make([]string, 0)
	coordinates := [][]int{
		{tipX, tipY},
		{tipX - 1, tipY + 1},
		{tipX + 1, tipY + 1},
		{tipX - 2, tipY + 2},
		{tipX + 2, tipY + 2},
		{tipX - 3, tipY + 3},
		{tipX + 3, tipY + 3},
	}
	for _, c := range coordinates {
		hashes = append(hashes, hash(c[0], c[1]))
	}
	return hashes
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\14\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

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

	iteration := 0
	robotMap := make(map[string]bool)
	for {
		if hasTriangle(robotMap, xMax, yMax) {
			break
		}
		robotMap = make(map[string]bool)
		for i := range len(robots) {
			r := &robots[i]
			r.x = teleport(r.x+r.vx, xMax)
			r.y = teleport(r.y+r.vy, yMax)
			h := hash(r.x, r.y)
			robotMap[h] = true
		}
		iteration++
	}

	printRobots(robots, xMax, yMax)
	fmt.Println(iteration)
}
