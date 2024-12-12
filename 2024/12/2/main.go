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

type Side struct {
	coordinate Coordinate
	direction  int
}

type Plot struct {
	coordinate Coordinate
	plant      rune
}

type Region struct {
	coordinates []Coordinate
	plant       rune
}

func (r *Region) perimeter() []Side {
	coordinates := make([]Coordinate, 0)
	sides := make([]Side, 0)
	for _, c := range r.coordinates {
		for i, adj := range getAdjacent(c) {
			if !slices.Contains(r.coordinates, adj) {
				coordinates = append(coordinates, adj)
				sides = append(sides, Side{adj, i})
			}
		}
	}
	return sides
}

func getAdjacent(c Coordinate) []Coordinate {
	return []Coordinate{
		{c.I - 1, c.J},
		{c.I, c.J + 1},
		{c.I + 1, c.J},
		{c.I, c.J - 1},
	}
}

func getAdjacentSides(c Coordinate, dir int) []Side {
	return []Side{
		{Coordinate{c.I - 1, c.J}, dir},
		{Coordinate{c.I, c.J + 1}, dir},
		{Coordinate{c.I + 1, c.J}, dir},
		{Coordinate{c.I, c.J - 1}, dir},
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

func growPerimeterSection(section *[]Side, perimeter *[]Side) {
	for {
		growing := false
		for _, s := range *section {
			for _, adjacent := range getAdjacentSides(s.coordinate, s.direction) {
				idx := slices.Index(*perimeter, adjacent)
				if idx != -1 {
					*section = append(*section, adjacent)
					*perimeter = append((*perimeter)[:idx], (*perimeter)[idx+1:]...)
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
		sections := make([][]Side, 0)
		perimeter := region.perimeter()
		for {
			if len(perimeter) == 0 {
				break
			}
			section := []Side{perimeter[0]}
			perimeter = perimeter[1:]
			growPerimeterSection(&section, &perimeter)
			sections = append(sections, section)
		}
		sum += len(region.coordinates) * len(sections)
	}

	fmt.Println(sum)
}
