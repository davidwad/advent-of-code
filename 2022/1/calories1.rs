use std::fs;
use std::io::{BufRead, BufReader};

fn main() {
    let mut value = 0;
    let mut max_value = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            if value > max_value {
                max_value = value;
            }
            break;
        } else if line.trim() == "" {
            if value > max_value {
                max_value = value;
            }
            value = 0;
        } else {
            let parsed: i32 = line.trim().parse().expect("Input not an integer");
            value += parsed;
        }
    }
    println!("{}", max_value);
}
