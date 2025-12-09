use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut tiles = Vec::<(i64, i64)>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split(",").collect();
        let tile = (split[0].parse::<i64>().expect("Failed to parse coordinate as i32"), split[1].parse::<i64>().expect("Failed to parse coordinate as i32"));
        tiles.push(tile);
    }

    let mut max_area: i64 = 0;
    for i in 0..tiles.len() {
        for j in i+1..tiles.len() {
            let t1 = tiles[i];
            let t2 = tiles[j];
            let dx = (t1.0 - t2.0 + 1).abs();
            let dy = (t1.1 - t2.1 + 1).abs();
            let area = dx * dy;
            if area > max_area {
                max_area = area;
            }
        }
    }

    println!("{max_area}")

}
