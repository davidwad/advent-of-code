use std::collections::HashSet;
use std::fs;
use std::io::{BufRead, BufReader};

struct Connection {
    idx1: usize,
    idx2: usize,
    distance: f64,
}

pub fn part1() {
    let joins: usize = 1000;
    let mut product: u64 = 1;
    let mut coordinates = Vec::<(i32, i32, i32)>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split(",").collect();
        let coords = (split[0].parse::<i32>().expect("Failed to parse coordinate as i32"), split[1].parse::<i32>().expect("Failed to parse coordinate as i32"), split[2].parse::<i32>().expect("Failed to parse coordinate as i32"));
        coordinates.push(coords);
    }

    let mut connections = Vec::<Connection>::new();
    for i in 0..coordinates.len() {
        for j in i+1..coordinates.len() {
            let c = Connection {
                idx1: i,
                idx2: j,
                distance: distance(coordinates[i], coordinates[j])
            };
            connections.push(c);
        }
    }
    connections.sort_by(|a, b| a.distance.partial_cmp(&b.distance).expect("Failed to compare"));

    let mut circuits = Vec::<HashSet::<usize>>::new();
    for conn in &connections[0..joins] {
        let mut i: usize = 0;
        let mut idx = Vec::<usize>::new();
        for circuit in &mut circuits {
            if circuit.contains(&conn.idx1) || circuit.contains(&conn.idx2) {
                circuit.insert(conn.idx1);
                circuit.insert(conn.idx2);
                idx.push(i);
            }
            i += 1;
        }
        if idx.len() == 2 {
            let idx_to_remove = usize::max(idx[0], idx[1]);
            let idx_to_append: usize = usize::min(idx[0], idx[1]);
            let c = circuits.remove(idx_to_remove);
            if idx [0] < idx[1] {
                circuits[idx_to_append].extend(c);
            }
        } else if idx.len() == 0 {
            circuits.push(HashSet::from([conn.idx1, conn.idx2]))
        }
    }

    circuits.sort_by_key(|k| usize::MAX - k.len());
    for i in 0..3 {
        if i >= circuits.len() {
            break;
        }
        product = product * circuits[i].len() as u64;
    }

    println!("{}", product);
}


fn distance(c1: (i32, i32, i32), c2: (i32, i32, i32)) -> f64 {
    let d1 = (c1.0 - c2.0) as f64;
    let d2 = (c1.1 - c2.1) as f64;
    let d3 = (c1.2 - c2.2) as f64;
    let d = d1.powf(2 as f64) + d2.powf(2 as f64) + d3.powf(2 as f64);
    return d.sqrt();
}