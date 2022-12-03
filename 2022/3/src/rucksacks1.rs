use std::fs;
use std::io::{BufRead, BufReader};
use array_tool;

pub fn rock_paper_scissors_1() {
    let mut total_priority = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        } else {
            let compartment_size = line.len() / 2;

            let mut compartment1 = Vec::new();
            let mut compartment2 = Vec::new();
            for (i, c) in line.chars().enumerate() {
                let prio = char_to_prio(c);
                if i < compartment_size {
                    compartment1.push(prio);
                } else {
                    compartment2.push(prio);
                }
            }
            
            
            
        }
    }

    println!("{}", total_priority);
}

fn char_to_prio(c: char) -> u32 {
    let term1 = match c.to_digit(10) {
        Some(x) => x,
        _ => panic!("Cannot convert to digit!")
    };
    let term2 = match 'a'.to_digit(10) {
        Some(x) => x,
        _ => panic!("Cannot convert to digit!") 
    };
    term1 - term2
}