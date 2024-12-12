package main

import (
	"fmt"
	"slices"
	"utils"
)

type Coordinate struct {
	I int
	J int
}

type Plot struct {
	coordinate Coordinate
	plant      rune
}

type Region struct {
	coordinates []Coordinate
	plant       rune
}

func (r *Region) perimeter() int {
	sum := 0
	for _, c := range r.coordinates {
		for _, adj := range getAdjacent(c) {
			if !slices.Contains(r.coordinates, adj) {
				sum++
			}
		}
	}
	return sum
}

func getAdjacent(c Coordinate) []Coordinate {
	return []Coordinate{
		{c.I, c.J - 1},
		{c.I, c.J + 1},
		{c.I - 1, c.J},
		{c.I + 1, c.J},
	}
}

func grow(region *Region, plots *[]Plot) {
	for {
		growing := false
		for _, c := range region.coordinates {
			for _, adjacent := range getAdjacent(c) {
				idx := slices.Index(*plots, Plot{adjacent, region.plant})
				if idx != -1 {
					region.coordinates = append(region.coordinates, (*plots)[idx].coordinate)
					*plots = append((*plots)[:idx], (*plots)[idx+1:]...)
					growing = true
				}
			}
		}
		if !growing {
			break
		}
	}
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\12\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	regions := make([]Region, 0)
	plots := make([]Plot, 0)

	for i, line := range lines {
		for j, plant := range line {
			plots = append(plots, Plot{Coordinate{i, j}, plant})
		}
	}

	for {
		if len(plots) == 0 {
			break
		}
		plot := plots[0]
		plots = plots[1:]
		region := Region{[]Coordinate{{plot.coordinate.I, plot.coordinate.J}}, plot.plant}
		grow(&region, &plots)
		regions = append(regions, region)
	}

	sum := 0
	for _, region := range regions {
		sum += region.perimeter() * len(region.coordinates)
	}

	fmt.Println(sum)
}
