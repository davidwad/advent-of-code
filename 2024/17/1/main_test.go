package main

import (
	"fmt"
	"slices"
	"testing"
)

func Test_adv(t *testing.T) {
	var tests = []struct {
		A, o uint64
		want uint64
	}{
		{0, 1, 0},
		{1, 0, 1},
		{99, 2, 24},
	}

	for _, tt := range tests {

		testName := fmt.Sprintf("%d,%d", tt.A, tt.o)
		t.Run(testName, func(t *testing.T) {
			B := uint64(0)
			C := uint64(0)
			runProgram(&tt.A, &B, &C, []uint64{0, tt.o})
			if tt.A != tt.want {
				t.Errorf("got %d, want %d", tt.A, tt.want)
			}
		})
	}
}

func Test_bdv(t *testing.T) {
	var tests = []struct {
		A, o uint64
		want uint64
	}{
		{0, 1, 0},
		{1, 0, 1},
		{99, 2, 24},
	}

	for _, tt := range tests {

		testName := fmt.Sprintf("%d,%d", tt.A, tt.o)
		t.Run(testName, func(t *testing.T) {
			B := uint64(0)
			C := uint64(0)
			runProgram(&tt.A, &B, &C, []uint64{6, tt.o})
			if B != tt.want {
				t.Errorf("got %d, want %d", B, tt.want)
			}
		})
	}
}

func Test_cdv(t *testing.T) {
	var tests = []struct {
		A, o uint64
		want uint64
	}{
		{0, 1, 0},
		{1, 0, 1},
		{99, 2, 24},
	}

	for _, tt := range tests {

		testName := fmt.Sprintf("%d,%d", tt.A, tt.o)
		t.Run(testName, func(t *testing.T) {
			B := uint64(0)
			C := uint64(0)
			runProgram(&tt.A, &B, &C, []uint64{7, tt.o})
			if C != tt.want {
				t.Errorf("got %d, want %d", C, tt.want)
			}
		})
	}
}

func Test_bxl(t *testing.T) {
	instructions := []uint64{1, 7}
	A := uint64(0)
	B := uint64(29)
	C := uint64(0)

	runProgram(&A, &B, &C, instructions)

	if B != uint64(26) {
		t.Errorf("B = %d; want 26", B)
	}
}

func Test_bst(t *testing.T) {
	instructions := []uint64{2, 6}
	A := uint64(0)
	B := uint64(2)
	C := uint64(9)

	runProgram(&A, &B, &C, instructions)

	if B != uint64(1) {
		t.Errorf("B = %d; want 1", B)
	}
}

func Test_bxc(t *testing.T) {
	instructions := []uint64{4, 0}
	A := uint64(0)
	B := uint64(2024)
	C := uint64(43690)

	runProgram(&A, &B, &C, instructions)

	if B != uint64(44354) {
		t.Errorf("B = %d; want 44354", B)
	}
}

func Test_program1(t *testing.T) {
	instructions := []uint64{5, 0, 5, 1, 5, 4}
	A := uint64(10)
	B := uint64(0)
	C := uint64(0)
	expected := []uint64{0, 1, 2}

	output := runProgram(&A, &B, &C, instructions)

	if !slices.Equal(output, expected) {
		t.Errorf("output = %x; want %x", output, expected)
	}
}

func Test_program2(t *testing.T) {
	instructions := []uint64{0, 1, 5, 4, 3, 0}
	A := uint64(2024)
	B := uint64(0)
	C := uint64(0)
	expected := []uint64{4, 2, 5, 6, 7, 7, 7, 7, 3, 1, 0}

	output := runProgram(&A, &B, &C, instructions)

	if !slices.Equal(output, expected) {
		t.Errorf("output = %x; want %x", output, expected)
	}
	if A != 0 {
		t.Errorf("A = %d; want 0", A)
	}
}
