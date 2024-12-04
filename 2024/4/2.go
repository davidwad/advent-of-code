package main

import (
	"fmt"
	"utils"
)

type X struct {
	descDiag string
	ascDiag  string
}

func getXs(chars [][]rune) []X {
	var xs []X
	for i := range len(chars) - 2 {
		for j := range len(chars[0]) - 2 {
			descDiag := make([]rune, 3)
			descDiag[0] = chars[i][j]
			descDiag[1] = chars[i+1][j+1]
			descDiag[2] = chars[i+2][j+2]
			ascDiag := make([]rune, 3)
			ascDiag[0] = chars[i][j+2]
			ascDiag[1] = chars[i+1][j+1]
			ascDiag[2] = chars[i+2][j]
			x := X{descDiag: string(descDiag), ascDiag: string(ascDiag)}
			xs = append(xs, x)
		}
	}
	return xs
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\4\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	count := 0

	chars := make([][]rune, len(lines))
	for i := 0; i < len(lines); i++ {
		chars[i] = make([]rune, len(lines[0]))
	}
	for i, line := range lines {
		chars[i] = make([]rune, len(lines[0]))
		for j, c := range line {
			chars[i][j] = c
		}
	}

	xs := getXs(chars)
	for _, x := range xs {
		if (x.ascDiag == "MAS" || x.ascDiag == "SAM") && (x.descDiag == "MAS" || x.descDiag == "SAM") {
			count++
		}
	}

	fmt.Println(count)
}
