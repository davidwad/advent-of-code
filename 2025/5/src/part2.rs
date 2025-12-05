use std::fs;
use std::io::{BufRead, BufReader};

pub fn part2() {
    let mut count: u64 = 0;
    let mut ranges = Vec::<(u64, u64)>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 || line.trim().len() == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split("-").collect();
        let left = split[0].parse::<u64>().expect("Failed to parse left part of range as u32");
        let right = split[1].parse::<u64>().expect("Failed to parse right part of range as u32");
        ranges.push((left, right));
    }

    let mut keep_going = true;
    while keep_going {
        keep_going = merge_ranges(&mut ranges);
    }

    ranges.sort_by(|a, b| a.0.cmp(&b.0));

    for (l, r) in ranges.iter() {
        count += r - l + 1;
    }

    println!("{}", count);
}

fn merge_ranges(ranges: &mut Vec::<(u64, u64)>) -> bool {
    for (i, (l1, r1)) in ranges.iter().enumerate() {
        let mut j = i+1;
        for (l2, r2) in &ranges[i+1..] {
            let mut merge_ranges = false;
            let mut new_range: (u64, u64) = (*l1, *r1);
            if l1 >= l2 && l1 <= r2 {
                merge_ranges = true;
                new_range.0 = *l2;
            }
            if r1 >= l2 && r1 <= r2 {
                merge_ranges = true;
                new_range.1 = *r2;
            }
            if *l1 <= *l2 && *r1 >= *r2 {
                merge_ranges = true;
            }

            if merge_ranges {
                ranges.remove(i);
                ranges.remove(j-1);
                ranges.push(new_range);
                return true;
            }

            j += 1;
        }
    }

    return false;
}