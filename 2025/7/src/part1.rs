use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut count: u32 = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    let mut line = String::new();
    buff_reader.read_line(&mut line).expect("Failed to read input!");
    let mut beam_idx = parse_line(&line);
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0{
            break;
        }

        let splitter_idx = parse_line(&line);
        if splitter_idx.len() == 0 {
            continue;
        }

        for i in &splitter_idx {
            if beam_idx.contains(i) {
                count += 1;
                if !beam_idx.contains(&(i-1)) {
                    beam_idx.push(i-1);
                }
                if !beam_idx.contains(&(i+1)) {
                    beam_idx.push(i+1);
                }
                
                let idx = beam_idx.iter().position(|x| x == i).expect("Index not found in beam_idx");
                beam_idx.remove(idx);
            }
        }
    }

    println!("{}", count);
}

fn parse_line(line: &String) -> Vec<usize> {
    let mut idx = Vec::<usize>::new();
    for (i, c) in line.trim().chars().enumerate() {
        if c != '.' {
            idx.push(i);
        }
    }

    return idx;
}
