package main

import (
	"fmt"
	"regexp"
	"slices"
	"strconv"
	"strings"
	"utils"
)

type Gate struct {
	t string
	l string
	r string
	o string
}

type Pair struct {
	l string
	r string
}

func parseInput(lines []string) ([]Gate, map[string]bool, map[string]Pair, map[Pair]string) {
	re := regexp.MustCompile(`(\w{3}) (\w{2,3}) (\w{3}) -> (\w{3})`)

	results := make(map[string]bool)
	inputs := make(map[string]Pair)
	outputs := make(map[Pair]string)
	gates := make([]Gate, 0)

	i := 0
	for {
		line := lines[i]
		if len(line) == 0 {
			i++
			break
		}
		split := strings.Split(line, ": ")
		res, _ := strconv.Atoi(split[1])
		results[split[0]] = res == 1
		i++
	}

	for {
		if i == len(lines) {
			break
		}
		line := lines[i]
		match := re.FindStringSubmatch(line)
		gates = append(gates, Gate{match[2], match[1], match[3], match[4]})
		inputs[match[4]] = Pair{match[1], match[3]}
		outputs[Pair{match[1], match[3]}] = match[4]
		i++
	}

	return gates, results, inputs, outputs
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\24\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	gates, _, _, _ := parseInput(lines)
	xyz := []string{"x", "y", "z"}
	faulty := make(map[string]bool)
	for _, gate := range gates {
		if strings.HasPrefix(gate.o, "z") && gate.t != "XOR" && gate.o != "z45" {
			faulty[gate.o] = true
		}

		lp := string(gate.l[0])
		rp := string(gate.r[0])
		op := string(gate.o[0])
		if gate.t == "XOR" &&
			!slices.Contains(xyz, lp) &&
			!slices.Contains(xyz, rp) &&
			!slices.Contains(xyz, op) {
			faulty[gate.o] = true
		}

		if gate.t == "AND" && gate.l != "x00" && gate.r != "x00" {
			for _, g := range gates {
				if (gate.o == g.l || gate.o == g.r) && g.t != "OR" {
					faulty[gate.o] = true
				}
			}
		}

		if gate.t == "XOR" {
			for _, g := range gates {
				if (gate.o == g.l || gate.o == g.r) && g.t == "OR" {
					faulty[gate.o] = true
				}
			}
		}
	}
	f := make([]string, 0)
	for k, _ := range faulty {
		f = append(f, k)
	}
	slices.Sort(f)
	fmt.Println(strings.Join(f, ","))
}
