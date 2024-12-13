package main

import (
	"fmt"
	"math"
	"regexp"
	"strconv"
	"utils"
)

// Machine
// x = k_ax * a + k_bx * b
// y = k_ay * a + k_by * b
// t = 3a + b
type Machine struct {
	kax int
	kbx int
	kay int
	kby int
	X   int
	Y   int
}

type ButtonPresses struct {
	A int
	B int
}

func (m *Machine) reachX(tries int) []ButtonPresses {
	presses := make([]ButtonPresses, 0)
	for a := range tries {
		for b := range tries {
			if a*m.kax+b*m.kbx == m.X {
				presses = append(presses, ButtonPresses{a, b})
			}
		}
	}
	return presses
}

func (m *Machine) reachY(tries int) []ButtonPresses {
	presses := make([]ButtonPresses, 0)
	for a := range tries {
		for b := range tries {
			if a*m.kay+b*m.kby == m.Y {
				presses = append(presses, ButtonPresses{a, b})
			}
		}
	}
	return presses
}

func getInterSection(aSlice, bSlice []ButtonPresses) []ButtonPresses {
	interSection := make([]ButtonPresses, 0)
	for _, a := range aSlice {
		for _, b := range bSlice {
			if a == b {
				interSection = append(interSection, a)
			}
		}
	}
	return interSection
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\13\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	rA := regexp.MustCompile(`Button A: X\+(\d+), Y\+(\d+)`)
	rB := regexp.MustCompile(`Button B: X\+(\d+), Y\+(\d+)`)
	rP := regexp.MustCompile(`Prize: X=(\d+), Y=(\d+)`)

	idx := 0
	machines := make([]Machine, 0)
	machine := Machine{}
	for _, line := range lines {
		switch idx {
		case 0:
			res := rA.FindStringSubmatch(line)
			machine.kax, _ = strconv.Atoi(res[1])
			machine.kay, _ = strconv.Atoi(res[2])
		case 1:
			res := rB.FindStringSubmatch(line)
			machine.kbx, _ = strconv.Atoi(res[1])
			machine.kby, _ = strconv.Atoi(res[2])
		case 2:
			res := rP.FindStringSubmatch(line)
			machine.X, _ = strconv.Atoi(res[1])
			machine.Y, _ = strconv.Atoi(res[2])
			machines = append(machines, machine)
		case 3:
			idx = -1
			machine = Machine{}
		}
		idx++
	}

	sum := 0
	for _, m := range machines {
		xPresses := m.reachX(101)
		yPresses := m.reachY(101)
		interSection := getInterSection(xPresses, yPresses)
		minCost := math.MaxInt
		for _, presses := range interSection {
			cost := 3*presses.A + presses.B
			if cost < minCost {
				minCost = cost
			}
		}
		if minCost < math.MaxInt {
			sum += minCost
		}

	}
	fmt.Println(sum)
}
