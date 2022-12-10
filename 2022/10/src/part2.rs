use std::fs;
use std::io::{BufRead, BufReader};

pub fn part_2() {
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

    let mut line: String = String::new();
    for cycle in 0..register.len() {
        
        let pixel: i32 = cycle as i32 % 40;
        // println!("Pixel: {}, Register position: {}", pixel, register[cycle]);
        if pixel >= register[cycle] - 1 && pixel <= register[cycle] + 1 {
            line += "#";
        } else {
            line += ".";
        }

        if (cycle + 1) % 40 == 0 {
            println!("{}", line);
            line = String::new();
        }

        //println!("{}", line);
    }
}

