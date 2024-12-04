package main

import (
	"fmt"
	"utils"
)

func getDescendingDiagonals(chars [][]rune) []string {
	var diags []string
	for i := range len(chars) - 3 {
		for j := range len(chars[0]) - 3 {
			diag := make([]rune, 4)
			diag[0] = chars[i][j]
			diag[1] = chars[i+1][j+1]
			diag[2] = chars[i+2][j+2]
			diag[3] = chars[i+3][j+3]
			diags = append(diags, string(diag))
		}
	}
	return diags
}

func getAscendingDiagonals(chars [][]rune) []string {
	var diags []string
	for i := range len(chars) - 3 {
		for j := 3; j < len(chars); j++ {
			diag := make([]rune, 4)
			diag[0] = chars[i][j]
			diag[1] = chars[i+1][j-1]
			diag[2] = chars[i+2][j-2]
			diag[3] = chars[i+3][j-3]
			diags = append(diags, string(diag))
		}
	}
	return diags
}

func getRows(chars [][]rune) []string {
	var rows []string
	for i := range len(chars) {
		for j := range len(chars) - 3 {
			row := make([]rune, 4)
			row[0] = chars[i][j]
			row[1] = chars[i][j+1]
			row[2] = chars[i][j+2]
			row[3] = chars[i][j+3]
			rows = append(rows, string(row))
		}
	}
	return rows
}

func getCols(chars [][]rune) []string {
	var rows []string
	for i := range len(chars) - 3 {
		for j := range len(chars) {
			row := make([]rune, 4)
			row[0] = chars[i][j]
			row[1] = chars[i+1][j]
			row[2] = chars[i+2][j]
			row[3] = chars[i+3][j]
			rows = append(rows, string(row))
		}
	}
	return rows
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

	descDiags := getDescendingDiagonals(chars)
	ascDiags := getAscendingDiagonals(chars)
	rows := getRows(chars)
	cols := getCols(chars)

	for _, str := range descDiags {
		if str == "XMAS" || str == "SAMX" {
			count++
		}
	}

	for _, str := range ascDiags {
		if str == "XMAS" || str == "SAMX" {
			count++
		}
	}

	for _, str := range rows {
		if str == "XMAS" || str == "SAMX" {
			count++
		}
	}

	for _, str := range cols {
		if str == "XMAS" || str == "SAMX" {
			count++
		}
	}

	fmt.Println(count)
}
