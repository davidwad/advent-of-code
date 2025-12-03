use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut sum = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        sum += find_largest_joltage(line.trim());
    }

    println!("{}", sum);
}

fn find_largest_joltage(bank: &str) -> i32 {
    let mut max = 0;
    for (i, left) in bank.chars().enumerate() {
        for right in bank.get(i+1..).expect("Failed to get slice").chars() {
            let candidate = format!("{left}{right}").parse::<i32>().expect("Failed to parse characters as int");
            if candidate > max {
                max = candidate;
            }
        }
    }
    return max;
}