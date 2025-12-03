use std::fs;
use std::io::{BufRead, BufReader};

pub fn part2() {
    let mut sum: i64 = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let largest_joltage = build_largest_joltage(line.trim().to_string(), 11);
        println!("{largest_joltage}");
        sum += largest_joltage.parse::<i64>().expect("Failed to parse largest joltage string as i64");
    }

    println!("{}", sum);
}

fn build_largest_joltage(bank: String, n: usize) -> String {
    let mut max_idx = 0;
    let mut max = 0;
    for (i, c) in bank.get(0..bank.len()-n).expect("Failed to get slice of bank string").chars().enumerate() {
        let val = c.to_digit(10).expect("Failed to convert character to digit");
        if val > max {
            max = val;
            max_idx = i;
        }
    }

    let max_str = max.to_string();
    if n == 0 {
        return max_str;
    }
    let right_of_max = build_largest_joltage(bank[max_idx+1..].to_string(), n-1);
    let joltage = format!("{max_str}{right_of_max}");
    
    return joltage;
}