use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut n_dial_at_zero = 0;
    let mut dial_pos = 50;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let dir = line.chars().nth(0).expect("Failed to parse direction");
        let val_str = line.trim().get(1..).expect("Failed to parse value as string");
        let val = val_str.parse::<i32>().expect("Failed to parse value as int");

        dial_pos = match dir {
            'L' => (dial_pos - val) % 100,
            'R' => (dial_pos + val) % 100,
            _ => panic!("Unrecognized direction")
        };

        if dial_pos == 0 {
            n_dial_at_zero += 1;
        }
    }

    println!("{}", n_dial_at_zero);
}