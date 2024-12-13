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
			machine.X += 10000000000000
			machine.Y, _ = strconv.Atoi(res[2])
			machine.Y += 10000000000000
			machines = append(machines, machine)
		case 3:
			idx = -1
			machine = Machine{}
		}
		idx++
	}

	sum := int64(0)
	for _, m := range machines {
		X := float64(m.X)
		Y := float64(m.Y)
		kax := float64(m.kax)
		kay := float64(m.kay)
		kbx := float64(m.kbx)
		kby := float64(m.kby)

		d := kby - kay*kbx/kax
		b := math.Round((Y - kay*X/kax) / d)
		a := math.Round((X - kbx*b) / kax)

		if a*kax+b*kbx == X && a*kay+b*kby == Y {
			sum += int64(math.Round(a)*3) + int64(math.Round(b))
		}

	}
	fmt.Println(sum)
}
