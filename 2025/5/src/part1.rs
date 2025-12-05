use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut count = 0;
    let mut ranges = Vec::<(u64, u64)>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 || line.trim().len() == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split("-").collect();
        let left = split[0].parse::<u64>().expect("Failed to parse left part of range as u32");
        let right = split[1].parse::<u64>().expect("Failed to parse right part of range as u32");
        ranges.push((left, right));
    }

    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let id = line.trim().parse::<u64>().expect("Failed to parse left part of range as u32");
        let mut fresh = false;
        for (l, r) in ranges.iter() {
            if id >= *l && id <= *r {
                fresh = true;
            }
        }

        if fresh {
            count += 1;
        }
    }


    println!("{}", count);
}
