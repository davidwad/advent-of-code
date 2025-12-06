use std::fs;
use std::io::{BufRead, BufReader};

pub fn part2() {
    let mut sum: u64 = 0;
    let mut lines = Vec::<String>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0{
            break;
        }

        line.pop();
        lines.push(line);
    }

    let width = lines[0].len();
    let height = lines.len();

    let mut res: u64 = 0;
    let mut operator = '-';
    for i in 0..width {
        let c = lines[height - 1].chars().nth(i).expect("Failed to get char from line");
        if c == '+' {
            operator = c;
            res = 0;
        } else if c == '*' {
            res = 1;
            operator = c;
        }

        let mut s = String::from("");
        for j in 0..height - 1 {
            let c = lines[j].chars().nth(i).expect("Failed to get char from line");
            s.push(c);
        }
        
        s = s.trim().to_string();
        if s == String::from("") {
            sum += res;
            res = 0;
        } else {
            if operator == '+' {
                res = res + s.parse::<u64>().expect("Failed to parse number as u64");
            } else if operator == '*' {
                res = res * s.parse::<u64>().expect("Failed to parse number as u64");
            }
        }
    }

    println!("{}", sum);
}
