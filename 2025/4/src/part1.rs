use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut count = 0;
    let mut lines = Vec::<String>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        lines.push(line.trim().to_string());
    }

    for x in 0..lines[0].len() {
        for y in 0..lines.len() {
            if lines[y].chars().nth(x).expect("Failed to get character from paper roll map") == '@' {
                if can_be_accessed(&lines, x as i32, y as i32) {
                    count += 1;
                }
            }
        }
    }

    println!("{}", count);
}

fn can_be_accessed(rolls: &Vec<String>, x: i32, y: i32) -> bool {
    let mut count = 0;
    let width = rolls[0].len() as i32;
    let height = rolls.len() as i32;
    for xi in x-1..x+2 {
        if xi < 0 || xi >= width {
            continue;
        }
        for yi in y-1..y+2 {
            if yi < 0 || yi >= height {
                continue;
            }

            if xi == x && yi == y {
                continue;
            }

            if rolls[yi as usize].chars().nth(xi as usize).expect("Failed to get character from paper roll map") == '@' {
                count += 1;
            }
        }
    }

    return count < 4;
}
