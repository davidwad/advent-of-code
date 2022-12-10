use std::fs;
use std::io::{BufRead, BufReader};

pub fn part_1() {
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut register: Vec<i32> = Vec::new();
    register.push(1);

    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!").trim().parse().expect("Failed to parse line!");
        if parsed == "noop" {
            register.push(register[register.len()-1]);
        } else {
            let mut split = parsed.split_whitespace();
            split.next();
            let value: i32 = split.next().expect("Iterator out of bounds!").parse().expect("Failed to parse string as i32!");
            register.push(register[register.len()-1]);
            register.push(register[register.len()-1] + value);
        }
    }

    let mut total_signal_strength = 0;
    for cycle in 1..=register.len() {
        if cycle % 40 == 20 {
            let signal_strength = register[cycle-1] * cycle as i32;
            total_signal_strength += signal_strength;
            println!("Cycle {}: {}", cycle, signal_strength)
        }
    }

    println!("{}", total_signal_strength);
}

