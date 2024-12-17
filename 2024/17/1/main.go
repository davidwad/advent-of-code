package main

import (
	"fmt"
	"math"
	"regexp"
	"strconv"
	"utils"
)

func combo(operand uint64, A, B, C uint64) uint64 {
	switch operand {
	case 0, 1, 2, 3:
		return operand
	case 4:
		return A
	case 5:
		return B
	case 6:
		return C
	default:
		panic("unexpected operand")
	}
}

func adv(operand uint64, A, B, C *uint64) {
	res := float64(*A) / math.Round(math.Pow(float64(2), float64(combo(operand, *A, *B, *C))))
	*A = uint64(res)
}

func bxl(operand uint64, B *uint64) {
	res := *B ^ operand
	*B = res
}

func bst(operand uint64, A, B, C *uint64) {
	res := combo(operand, *A, *B, *C) % 8
	*B = res
}

func jnz(operand uint64, ip, A *uint64) {
	if *A == 0 {
		*ip += 2
	} else {
		*ip = operand
	}
}

func bxc(B, C *uint64) {
	res := *B ^ *C
	*B = res
}

func out(operand uint64, A, B, C *uint64, output *[]uint64) {
	*output = append(*output, combo(operand, *A, *B, *C)%8)
}

func bdv(operand uint64, A, B, C *uint64) {
	res := float64(*A) / math.Round(math.Pow(float64(2), float64(combo(operand, *A, *B, *C))))
	*B = uint64(res)
}

func cdv(operand uint64, A, B, C *uint64) {
	res := float64(*A) / math.Round(math.Pow(float64(2), float64(combo(operand, *A, *B, *C))))
	*C = uint64(res)
}

func runProgram(A, B, C *uint64, instructions []uint64) []uint64 {
	output := make([]uint64, 0)
	ip := uint64(0)
	for {
		if ip == uint64(len(instructions)-1) {
			panic("instruction pointer is pointing to an operand")
		}
		if ip < 0 {
			panic("instruction pointer is negative")
		}
		if ip >= uint64(len(instructions)-1) {
			return output
		}
		opcode := instructions[ip]
		operand := instructions[ip+1]
		switch opcode {
		case 0:
			adv(operand, A, B, C)
			ip += 2
		case 1:
			bxl(operand, B)
			ip += 2
		case 2:
			bst(operand, A, B, C)
			ip += 2
		case 3:
			jnz(operand, &ip, A)
		case 4:
			bxc(B, C)
			ip += 2
		case 5:
			out(operand, A, B, C, &output)
			ip += 2
		case 6:
			bdv(operand, A, B, C)
			ip += 2
		case 7:
			cdv(operand, A, B, C)
			ip += 2
		default:
			panic("unexpected opcode")
		}
	}
}

func printRegisters(A, B, C uint64) {
	fmt.Println(fmt.Sprintf("Register A: %d", A))
	fmt.Println(fmt.Sprintf("Register B: %d", B))
	fmt.Println(fmt.Sprintf("Register C: %d", C))
	fmt.Println("---------------")
}

func printOutput(output []uint64) {
	for i := range len(output) - 2 {
		fmt.Print(fmt.Sprintf("%d,", output[i]))
	}
	fmt.Println(fmt.Sprintf("%d", output[len(output)-1]))
}

func main() {
	fileName := "C:\\Users\\DavidWadmark\\repos\\advent-of-code\\2024\\17\\input.txt"
	lines, err := utils.ReadFile(fileName)
	if err != nil {
		panic(err)
	}

	re := regexp.MustCompile(`\d+`)
	A, _ := strconv.ParseUint(re.FindString(lines[0]), 10, 64)
	B, _ := strconv.ParseUint(re.FindString(lines[1]), 10, 64)
	C, _ := strconv.ParseUint(re.FindString(lines[2]), 10, 64)

	instructions := make([]uint64, 0)
	res := re.FindAllString(lines[4], -1)
	for _, r := range res {
		i, _ := strconv.ParseUint(r, 10, 64)
		instructions = append(instructions, i)
	}

	output := runProgram(&A, &B, &C, instructions)
	printOutput(output)
}
