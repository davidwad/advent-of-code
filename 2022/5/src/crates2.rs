use std::fs;
use std::io::{BufRead, BufReader};

pub fn crates_2() {
    const CRATE_LINES: i32 = 8;
    const N_STACKS: usize = 9;

    let mut stacks: Vec<Vec<char>> = Vec::new();

    for _ in 0..N_STACKS {
        let stack: Vec<char> = Vec::new();
        stacks.push(stack);
    }

    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));

    for _ in 0..CRATE_LINES {
        let mut line = String::new();
        buff_reader.read_line(&mut line).expect("Failed to read input!");

        let mut char_pos = 1;
        for stack_idx in 0..N_STACKS {
            let c = line.chars().nth(char_pos).expect("Failed to read character from line!");
            if c != ' ' {
                stacks[stack_idx].insert(0, c);
            }
            char_pos += 4;
        }
    }

    // Read two lines
    let mut line = String::new();
    buff_reader.read_line(&mut line).expect("Failed to read input!");
    buff_reader.read_line(&mut line).expect("Failed to read input!");

    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        } else {
            let mut instructions: Vec<usize>= Vec::new();
            let parts = line.split_whitespace();
            for part in parts {
                match part.parse::<usize>() {
                    Ok(x) => instructions.push(x),
                    _ => ()
                }
            }

            let mut temp_stack: Vec<char> = Vec::new();
            for _ in 0..instructions[0] {
                let c = stacks[instructions[1] - 1].pop().unwrap();
                temp_stack.push(c);
                
            }

            for _ in 0..temp_stack.len() {
                stacks[instructions[2] - 1].push(temp_stack.pop().unwrap());
            }
        }
    }

    let mut result = String::new();
    
    for mut stack in stacks {
        result.push(stack.pop().unwrap());
    }

    println!("{}", result);
}
