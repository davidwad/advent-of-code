use std::collections::HashMap;
use std::fs;
use std::io::{BufRead, BufReader};

pub fn ropes_1() {
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut visited: HashMap<(i32, i32), bool> = HashMap::new();
    let mut head_coords = (0, 0);
    let mut tail_coords = (0, 0);

    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!").trim().parse().expect("Failed to parse line!");
        let mut split = parsed.split_whitespace();
        let direction: char = split.next().expect("Iterator out of bounds!").chars().next().expect("Failed to parse char!");
        let steps: i32 = split.next().expect("Iterator out of bounds!").parse().expect("Failed to parse string as u32!");

        for _ in 0..steps {
            match direction {
                'U' => head_coords.1 += 1,
                'R' => head_coords.0 += 1,
                'D' => head_coords.1 -= 1,
                'L' => head_coords.0 -= 1,
                _ => panic!("Unexpected char!")
            }
            tail_coords = calc_tail_coords(head_coords, tail_coords);
            visited.insert(tail_coords, true);
        }
    }

    println!("{}", visited.len());
}

fn calc_tail_coords(head_coords: (i32, i32), tail_coords: (i32, i32)) -> (i32, i32) {
    let dx: i32 = head_coords.0 - tail_coords.0;
    let dy: i32 = head_coords.1 - tail_coords.1;
    
    if dx.abs() > 1 && dy == 0 { // Horizontally straight
        return (tail_coords.0 + dx / 2, tail_coords.1);
    } else if dx == 0 && dy.abs() > 1 { // Vertically straight
        return (tail_coords.0, tail_coords.1 + dy / 2);
    } else if dx.abs() > 1 && dy.abs() == 1 { // Horizontally diagonal
        return (tail_coords.0 + dx / 2, tail_coords.1 + dy);
    } else if dx.abs() == 1 && dy.abs() > 1 { // Vertically diagonal
        return (tail_coords.0 + dx, tail_coords.1 + dy / 2);
    } else { // Don't need to move
        return tail_coords;
    }
}