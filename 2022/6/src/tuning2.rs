use std::fs;
use std::io::{BufRead, BufReader};
use array_tool::vec::Uniq;

pub fn tuning_2() {
    let mut result: usize = 0;
    let mut chars: Vec<char> = Vec::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut line = String::new();
    buff_reader.read_line(&mut line).expect("Failed to read input!");

    for (i, c) in line.chars().enumerate() {
        chars.insert(0, c);
        if i > 12 {
            if chars.is_unique() {
                result = i + 1;
                break;
            } else {
                chars.pop();
            }
        }
    }
    println!("{}", result);
}
