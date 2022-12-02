use std::fs;
use std::io::{BufRead, BufReader};

pub fn rock_paper_scissors_2() {
    let mut score = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        } else {
            let opp = line.chars().nth(0).unwrap();
            let me = line.chars().nth(2).unwrap();
            score += calculate_score(opp, me);
        }
    }

    println!("{}", score);
}

fn calculate_score(opp: char, me: char) -> i32 {
    let score = match me {
        'Z' => match opp {
            'A' => 8,
            'B' => 9,
            'C' => 7,
            _ => panic!("Unexpected char!"),
        },
        'Y' => match opp {
            'A' => 4,
            'B' => 5,
            'C' => 6,
            _ => panic!("Unexpected char!"),
        },
        'X' => match opp {
            'A' => 3,
            'B' => 1,
            'C' => 2,
            _ => panic!("Unexpected char!")
        },
        _ => panic!("Unexpected char!")
    };
    score
}