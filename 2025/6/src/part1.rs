use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut sum: u64 = 0;
    let mut numbers = Vec::<Vec::<u64>>::new();
    let mut operators = Vec::<char>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0{
            break;
        }
        
        if line.chars().nth(0).expect("Failed to get first character in line") == '+' || line.chars().nth(0).expect("Failed to get first character in line") == '*' {
            for s in line.split_whitespace() {
                if s == "+" {
                    operators.push('+');
                } else if s == "*" {
                    operators.push('*');
                }
            }
        } else {
            let mut nums = Vec::<u64>::new();
            for s in line.split_whitespace() {
                nums.push(s.parse::<u64>().expect("Failed to parse number as u64"));
            }
            numbers.push(nums);
        }
    }

    assert_eq!(operators.len(), numbers[0].len());

    for (i, op) in operators.iter().enumerate() {
        let mut res: u64 = 0;
        if *op == '*' {
            res = 1;
        }
        
        for j in 0..numbers.len() {
            let n = numbers[j][i];
            if *op == '*' {
                res = res * n;
            } else {
                res = res + n;
            }
        }

        sum += res;
    }

    println!("{}", sum);
}
