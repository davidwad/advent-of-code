use std::fs;
use std::io::{BufRead, BufReader};

pub fn part2() {
    let mut n_dial_at_zero = 0;
    let mut dial_pos = 50;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let dir = line.chars().nth(0).expect("Failed to parse direction");
        let val_str = line.trim().get(1..).expect("Failed to parse value as string");
        let val = val_str.parse::<i32>().expect("Failed to parse value as int");
        let n_passed_zero: i32;
        (dial_pos, n_passed_zero) = match dir {
            'L' => turn_left(dial_pos, val),
            'R' => turn_right(dial_pos, val),
            _ => panic!("Unrecognized direction")
        };

        n_dial_at_zero += n_passed_zero;

    }

    println!("{}", n_dial_at_zero);
}

fn turn_left(mut pos: i32, val: i32) -> (i32, i32) {
    let mut n_passed_zero = 0;
    for _ in 0..val {
        pos += 1;
        if pos == 100 {
            pos = 0;
            n_passed_zero +=1;
        }
    }
    return (pos, n_passed_zero);
}

fn turn_right(mut pos: i32, val: i32) -> (i32, i32) {
    let mut n_passed_zero = 0;
    for _ in 0..val {
        pos -= 1;
        if pos == -1 {
            pos = 99;
        }
        if pos == 0 {
            n_passed_zero +=1;
        }
    }
    return (pos, n_passed_zero);
}
