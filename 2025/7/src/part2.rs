use std::fs;
use std::io::{BufRead, BufReader};

pub fn part2() {
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    let mut line = String::new();
    buff_reader.read_line(&mut line).expect("Failed to read input!");
    let beam_idx = parse_line(&line);
    let mut beams: Vec<u64> = vec![0; line.trim().len()];
    beams[beam_idx[0]] = 1;
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0{
            break;
        }

        let splitter_idx = parse_line(&line);
        if splitter_idx.len() == 0 {
            continue;
        }

        for i in splitter_idx {
            let n_beams = beams[i];
            beams[i-1] += n_beams;
            beams[i+1] += n_beams;
            beams[i] = 0;
        }
    }

    let mut sum: u64 = 0;
    for n in beams {
        sum += n;
    }

    println!("{}", sum);
}

fn parse_line(line: &String) -> Vec<usize> {
    let mut idx = Vec::<usize>::new();
    for (i, c) in line.trim().chars().enumerate() {
        if c != '.' {
            idx.push(i);
        }
    }

    return idx;
}
