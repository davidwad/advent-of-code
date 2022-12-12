use std::collections::HashMap;
use std::fs;
use std::hash::Hash;
use std::io::{BufRead, BufReader};
use std::ops::Deref;
use priority_queue::PriorityQueue;

pub fn part_1() {
    let mut grid: Vec<Vec<i32>> = Vec::new();
    let mut start: (usize, usize) = (0, 0);
    let mut end: (usize, usize) = (0, 0);
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));

    for (i, line) in buff_reader.lines().enumerate() {
        let mut row: Vec<i32> = Vec::new();
        for (j, c) in line.expect("Failed to parse line as string!").trim().chars().enumerate() {
            let value: i32;
            if c == 'S' {
                value = 0;
                start = (i, j);
            } else if c == 'E' {
                value = 'z' as i32 - 'a' as i32;
                end = (i, j);
            } else {
                value = c as i32 - 'a' as i32;
                
            }
            row.push(value);
        }
        grid.push(row);
    }

    let n_grids = grid.len() * grid[0].len();
    // let mut distances = vec![vec![i32::MIN; grid[0].len()]; grid.len()];
    // distances[start.0][start.1] = 0;
    let mut distances: HashMap<(usize, usize), i32> = HashMap::new();
    
    let mut Q: PriorityQueue<(usize, usize), i32> = PriorityQueue::new();
    for i in 0..grid.len() {
        for j in 0..grid[0].len() {
            if i == start.0 && j == start.1 {
                Q.push((i, j), 0);
                distances.insert((i, j), 0);
            } else {
                Q.push((i, j), i32::MIN);
                distances.insert((i, j), i32::MIN);
            }
        }
    }
    // let mut explored: HashSet<(usize, usize)> = HashSet::new();
    // let mut candidates: HashSet<(usize, usize)> = HashSet::new();
    // candidates.insert(start);
    // let mut candidates: Vec<(usize, usize)> = Vec::new();
    // candidates.push(start);
    //let mut hm: HashMap<(u32, u32), u32> = HashMap::new();
    let mut counter: usize = 0;
    while !Q.is_empty() {
        // println!("Size of candidates: {}", candidates.len());
        // println!("Size of explored: {}", explored.len());
        // println!("----------------------");
        // let candidate = candidates.pop().expect("Candidates empty!");
        let u = Q.pop().expect("Expected Q to be non-empty!");

        // for i in 0..grid.len() {
        //     for j in 0..grid[0].len() {
        //         if (i, j) == u.0 {
        //             print!("{}", 'X');
        //         } else {
        //             let mut v: u8 = grid[i][j].try_into().expect("Failure!");
        //             v = v + 'a' as u8;
        //             let c: char = v as char;
        //             print!("{}", c);
        //         }

        //     }
        //     println!();
        // }
        // println!("--------------------------------------------------------------------------------------------------------------------");

        // explored.insert(candidate);
        // let distance = distances[candidate.0][candidate.1];
        let neighbours = available_neighbours(u.0, &grid);
        println!("Enter square ({},{})", u.0.0, u.0.1);
        // print!("Available neighbours:");
        // for n in neighbours.iter() {
        //     print!(" ({},{}) |", n.0, n.1);
        // }
        // println!("\n---------------------------");
        print!("Available neighbours:");
        for neighbour in neighbours {
            print!(" ({},{}) |", neighbour.0, neighbour.1);
            // let old_distance = distances[neighbour.0][neighbour.1];
            // let v = Q.get(&neighbour);
            let v = distances.get(&neighbour);
            if v.is_some() {
                let v = v.unwrap();
                let v_dist = v;
                // let vi = v.0.0;
                // let vj = v.0.1;
                //println!("Square: ({},{}) | {}", u.0.0, u.0.1, u.1);
                if u.1 - 1 > *v_dist {
                    Q.change_priority(&neighbour, u.1 - 1);
                    // distances[*vv).0.0][1] = 1;
                    distances.insert(neighbour, u.1 - 1);
                }
            }
            // let v = Q.get(&neighbour);

            // if !candidates.contains(&neighbour) {
            //     candidates.push(neighbour);
            // }
        }
        println!("\n---------------------------");
        // counter += 1;
        // if counter > 10 {
        //     break;
        // }
    }
    //TODO: Add unavailable neighbours to explored somehow
    
    // for loc in distances.iter() {
    //     println!("({},{})={}", loc.0.0, loc.0.1, loc.1);
    // }
    //println!("{}", distances.len());
    //println!("{}", n_grids);

    println!("{}", distances.get(&end).expect("Expected end to be in distances!"));
}

fn available_neighbours(loc: (usize, usize), grid: &Vec<Vec<i32>>) -> Vec<(usize, usize)> {
    let height = grid[loc.0][loc.1];
    let n_rows = grid.len();
    let n_cols = grid[0].len();
    let row = loc.0;
    let col = loc.1;
    let mut neighbours: Vec<(usize, usize)> = Vec::new();
    if row > 0 && !too_steep(height, grid[row-1][col]) {
        neighbours.push((row-1, col));
    }
    if row < n_rows-1 && !too_steep(height, grid[row+1][col]) {
        neighbours.push((row+1, col));
    }
    if col > 0 && !too_steep(height, grid[row][col-1]) {
        neighbours.push((row, col-1));
    }
    if col < n_cols-1 && !too_steep(height, grid[row][col+1]) {
        neighbours.push((row, col+1));
    }

    neighbours
}

fn too_steep(height1: i32, height2: i32) -> bool {
    (height1 - height2).abs() > 1
}