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

        let split_line: Vec<&str> = line.trim().split(",").collect();
        for interval in split_line {
            let split_interval: Vec<&str> = interval.split("-").collect();
            let left = split_interval[0].parse::<i64>().expect("Failed to parse left");
            let right = split_interval[1].parse::<i64>().expect("Failed to parse right");
            for i in left..right + 1 {
                if check_invalid_id(i) {
                    sum += i;
                }
            }
        }
    }

    println!("{}", sum);
}

fn check_invalid_id(val: i64) -> bool {
    let s = val.to_string();
    let n = s.len();
    for i in 2..n+1 {
        if n % i == 0 {
            let step = n / i;
            let first_split = s.get(0..step).expect("Failed to get slice of number string");
            let mut idx = step;
            while idx < n {
                let split = s.get(idx..idx+step).expect("Failed to get slice of number string");
                if split != first_split {
                    break;
                }
                idx = idx + step;
            }
            if idx >= n {
                return true;
            }
        }
    }
    return false;
}
