use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut sum: i64 = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split_line: Vec<&str> = line.trim().split(",").collect();
        for interval in split_line {
            let split_interval: Vec<&str> = interval.split("-").collect();
            let left = split_interval[0].parse::<i64>().expect("Failed to parse left");
            let right = split_interval[1].parse::<i64>().expect("Failed to parse right");
            sum += check_invalid_id(left, right);
        }
    }

    println!("{}", sum);
}

fn check_invalid_id(left: i64, right: i64) -> i64 {
    let mut sum: i64 = 0;
    for i in left..right + 1 {
        let s = i.to_string();
        let n = s.len();
        if n % 2 == 0 {
            let l = s.get(..n/2).expect("Failed to parse left half of number");
            let r = s.get(n/2..).expect("Failed to parse right half of number");
            if l == r {
                sum += i;
            }
        }
    }
    return sum
}