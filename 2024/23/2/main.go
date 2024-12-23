package main

import (
	"fmt"
	"math"
	"slices"
	"strings"
	"utils"
)

func grow(node string, set map[string]bool, vertices map[string][]string) {
	neighbours := vertices[node]
	for k, _ := range set {
		if !slices.Contains(neighbours, k) {
			return
		}
	}
	set[node] = true
	for _, nb := range neighbours {
		if _, visited := set[nb]; !visited {
			grow(nb, set, vertices)
		}
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\23\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	vertices := make(map[string][]string)

	for _, line := range lines {
		split := strings.Split(line, "-")
		e1 := split[0]
		e2 := split[1]

		if _, ok := vertices[e1]; ok {
			vertices[e1] = append(vertices[e1], e2)
		} else {
			vertices[e1] = []string{e2}
		}

		if _, ok := vertices[e2]; ok {
			vertices[e2] = append(vertices[e2], e1)
		} else {
			vertices[e2] = []string{e1}
		}
	}

	maxSize := math.MinInt
	biggestSet := make([]string, 0)
	for k, _ := range vertices {
		set := make(map[string]bool)
		grow(k, set, vertices)
		if len(set) > maxSize {
			biggestSet = []string{}
			for kk, _ := range set {
				biggestSet = append(biggestSet, kk)
			}
			maxSize = len(set)
		}
	}
	slices.Sort(biggestSet)
	password := strings.Join(biggestSet, ",")
	fmt.Println(password)
}
