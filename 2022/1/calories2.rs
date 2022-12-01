use std::fs;
use std::io::{BufRead, BufReader};

fn main() {
    let mut value = 0;
    let mut values = Vec::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            values.push(value);
            break;
        } else if line.trim() == "" {
            values.push(value);
            value = 0;
        } else {
            let parsed: i32 = line.trim().parse().expect("Input not an integer");
            value += parsed;
        }
    }
    values.sort();
    let max_value = values[values.len() - 1] + values[values.len() - 2] + values[values.len() - 3];
    println!("{}", max_value);
}
