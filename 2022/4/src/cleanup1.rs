use std::fs;
use std::io::{BufRead, BufReader};

pub fn cleanup_1() {
    let mut n_overlaps = 0;
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        } else {
            let mut line_split = line.trim().split(',');
            let interval1 = line_split.next().unwrap();
            let interval2 = line_split.next().unwrap();

            let mut interval_split_1 = interval1.split('-');
            let min1: i32 = interval_split_1.next().unwrap().parse().unwrap();
            let max1: i32 = interval_split_1.next().unwrap().parse().unwrap();

            let mut interval_split_2 = interval2.split('-');
            let min2: i32 = interval_split_2.next().unwrap().parse().unwrap();
            let max2: i32 = interval_split_2.next().unwrap().parse().unwrap();

            if is_overlap(min1, max1, min2, max2) {
                n_overlaps += 1;
            }
        }
    }

    println!("{}", n_overlaps);
}

fn is_overlap(min1: i32, max1: i32, min2: i32, max2: i32) -> bool {
    (min1 >= min2 && max1 <= max2) || (min1 <= min2 && max1 >= max2)
}