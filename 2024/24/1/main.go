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
	t  string
	i1 string
	i2 string
	o  string
}

func output(x1, x2 bool, t string) bool {
	switch t {
	case "AND":
		return x1 && x2
	case "OR":
		return x1 || x2
	case "XOR":
		return (x1 || x2) && !(x1 && x2)
	default:
		panic("unexpected gate type")
	}
	return false
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\24\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	re := regexp.MustCompile(`(\w{3}) (\w{2,3}) (\w{3}) -> (\w{3})`)

	results := make(map[string]bool)
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
		i++
	}

	for {
		if len(gates) == 0 {
			break
		}
		gate := gates[0]
		r1, ok1 := results[gate.i1]
		r2, ok2 := results[gate.i2]
		if ok1 && ok2 {
			results[gate.o] = output(r1, r2, gate.t)
		} else {
			// Move gate to last place in slice
			gates = append(gates, gate)
		}
		gates = gates[1:]
	}
	outputs := make([]string, 0)
	for k, _ := range results {
		if strings.HasPrefix(k, "z") {
			outputs = append(outputs, k)
		}
	}

	slices.Sort(outputs)
	sum := 0
	x := 1
	for _, o := range outputs {
		if results[o] {
			sum += x
		}
		x = x * 2
	}
	fmt.Println(sum)
}
