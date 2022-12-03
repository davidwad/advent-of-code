use std::fs;
use std::io::{BufRead, BufReader};
use array_tool::vec::Intersect;

pub fn rucksacks_2() {
    let mut total_priority = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut elf1: Vec<u32> = Vec::new();
    let mut elf2: Vec<u32> = Vec::new();
    let mut elf3: Vec<u32> = Vec::new();
    let mut elf_idx = 0;
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        line = line.trim().parse().expect("Could not parse line!");
        if num_bytes == 0 {
            break;
        } else {
            if elf_idx == 0 {
                for c in line.chars() {
                    let prio = char_to_prio(c);
                    elf1.push(prio);
                }

                elf_idx += 1;
            } else if elf_idx == 1 {
                for c in line.chars() {
                    let prio = char_to_prio(c);
                    elf2.push(prio);
                }

                elf_idx += 1;
            } else {
                for c in line.chars() {
                    let prio = char_to_prio(c);
                    elf3.push(prio);
                }

                let intersection = elf1.intersect(elf2.clone()).intersect(elf3.clone());
                let prio = match intersection.first() {Some(x) => x, _ => panic!("Intersection is empty!")};
                total_priority += prio;

                elf_idx = 0;
                elf1 = Vec::new();
                elf2 = Vec::new();
                elf3 = Vec::new();
            }
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
