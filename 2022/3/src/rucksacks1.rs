use std::fs;
use std::io::{BufRead, BufReader};
use array_tool::vec::Intersect;

pub fn rucksacks_1() {
    let mut total_priority = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        line = line.trim().parse().expect("Could not parse line!");
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
            let intersection = compartment1.intersect(compartment2);
            let prio = match intersection.first() {Some(x) => x, _ => panic!("Intersection is empty!")};
            total_priority += prio;
        }
    }
    println!("{}", total_priority);
}

fn char_to_prio(c: char) -> u32 {
    if c as u32 > 'Z' as u32 {
        return c as u32 - 'a' as u32 + 1;
    } else {
        return c as u32 - 'A' as u32 + 27;
    }
}