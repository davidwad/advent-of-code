package main

import (
	"fmt"
	"slices"
	"strings"
	"utils"
)

func hash(k1, k2, k3 string) string {
	h := []string{k1, k2, k3}
	slices.Sort(h)
	return strings.Join(h, "|")
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\23\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	vertices := make(map[string][]string)
	triples := make(map[string][]string)

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

	for k1, v1 := range vertices {
		for _, v2 := range v1 {
			for _, v3 := range vertices[v2] {
				if slices.Contains(v1, v3) {
					t := []string{k1, v2, v3}
					triples[hash(k1, v2, v3)] = t
				}
			}
		}
	}

	sum := 0
	for _, v := range triples {
		for _, s := range v {
			if strings.HasPrefix(s, "t") {
				sum++
				break
			}
		}
	}
	fmt.Println(sum)
}
