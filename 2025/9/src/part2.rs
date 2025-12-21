use std::collections::HashSet;
use std::fs;
use std::io::{BufRead, BufReader};
use std::panic;

pub fn part2() {
    let mut corners = Vec::<(i64, i64)>::new();
    let mut walls = HashSet::<(i64, i64)>::new();

    let mut buff_reader =
        BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    let mut prev_corner = (0 as i64, 0 as i64);
    let mut i = 0;
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader
            .read_line(&mut line)
            .expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split(",").collect();
        let corner = (
            split[0]
                .parse::<i64>()
                .expect("Failed to parse coordinate as i32"),
            split[1]
                .parse::<i64>()
                .expect("Failed to parse coordinate as i32"),
        );
        corners.push(corner);

        if i > 0 {
            build_wall(&mut walls, prev_corner, corner);
        }

        prev_corner = corner;
        i += 1;
    }

    build_wall(&mut walls, corners[corners.len() - 1], corners[0]);

    let start_pos1: (i64, i64);
    let start_pos2: (i64, i64);
    let x_diff = corners[0].0 - corners[1].0;
    if x_diff == 0 {
        // Vertical start
        start_pos1 = (corners[0].0 - 1, corners[0].1);
        start_pos2 = (corners[0].0 + 1, corners[0].1);
    } else {
        // Horizontal start
        start_pos1 = (corners[0].0, corners[0].1 - 1);
        start_pos2 = (corners[0].0, corners[0].1 + 1);
    }

    let outside: HashSet<(i64, i64)>;
    let mut outside1 = HashSet::<(i64, i64)>::new();
    let mut outside2 = HashSet::<(i64, i64)>::new();
    crawl_along_wall(&walls, &mut outside1, start_pos1);
    crawl_along_wall(&walls, &mut outside2, start_pos2);

    if outside1.len() > outside2.len() {
        outside = outside1;
    } else {
        outside = outside2;
    }

    let mut max_area: i64 = 0;
    for i in 0..corners.len() {
        for j in i + 1..corners.len() {
            let t1 = corners[i];
            let t2 = corners[j];

            if rectangle_contains_outside(&outside, t1, t2) {
                continue;
            }

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

fn build_wall(walls: &mut HashSet<(i64, i64)>, previous: (i64, i64), current: (i64, i64)) {
    if previous.0 < current.0 {
        // Going right
        for x in previous.0..current.0 + 1 {
            walls.insert((x, current.1));
        }
    } else if previous.0 > current.0 {
        // Going left
        for x in current.0..previous.0 + 1 {
            walls.insert((x, current.1));
        }
    } else if previous.1 < current.1 {
        // Going down
        for y in previous.1..current.1 + 1 {
            walls.insert((current.0, y));
        }
    } else if previous.1 > current.1 {
        // Going up
        for y in current.1..previous.1 + 1 {
            walls.insert((current.0, y));
        }
    } else {
        panic!("Failed to calculate direction");
    }
}

fn crawl_along_wall(
    walls: &HashSet<(i64, i64)>,
    outside: &mut HashSet<(i64, i64)>,
    pos: (i64, i64),
) {
    if walls.contains(&pos) || outside.contains(&pos) {
        return;
    }

    let mut wall_adjacent = false;
    for x in pos.0 - 1..pos.0 + 2 {
        for y in pos.1 - 1..pos.1 + 2 {
            if walls.contains(&(x, y)) {
                wall_adjacent = true;
            }
        }
    }

    if wall_adjacent {
        outside.insert(pos);
        crawl_along_wall(walls, outside, (pos.0 + 1, pos.1));
        crawl_along_wall(walls, outside, (pos.0 - 1, pos.1));
        crawl_along_wall(walls, outside, (pos.0, pos.1 + 1));
        crawl_along_wall(walls, outside, (pos.0, pos.1 - 1));
    }
}

fn rectangle_contains_outside(
    outside: &HashSet<(i64, i64)>,
    t1: (i64, i64),
    t2: (i64, i64),
) -> bool {
    for tile in outside {
        if rectangle_contains_tile(*tile, t1, t2) {
            return true;
        }
    }

    return false;
}

fn rectangle_contains_tile(tile: (i64, i64), t1: (i64, i64), t2: (i64, i64)) -> bool {
    if tile == t1 || tile == t2 {
        return false;
    }

    if t1.0 < t2.0 {
        if tile.0 <= t1.0 || tile.0 >= t2.0 {
            return false;
        }
    } else if t1.0 > t2.0 {
        if tile.0 <= t2.0 || tile.0 >= t1.0 {
            return false;
        }
    } else {
        return false;
    }

    if t1.1 < t2.1 {
        if tile.1 <= t1.1 || tile.1 >= t2.1 {
            return false;
        }
    } else if t1.1 > t2.1 {
        if tile.1 <= t2.1 || tile.1 >= t1.1 {
            return false;
        }
    } else {
        return false;
    }

    return true;
}

fn print_tiles(
    corners: &Vec<(i64, i64)>,
    walls: &HashSet<(i64, i64)>,
    outside: &HashSet<(i64, i64)>,
) {
    for y in 0..9 {
        for x in 0..13 {
            if corners.contains(&(x, y)) {
                assert!(walls.contains(&(x, y)));
                print!("#");
            } else if walls.contains(&(x, y)) {
                print!("X");
            } else if outside.contains(&(x, y)) {
                print!("O");
            } else {
                print!(".");
            }
        }
        println!();
    }
}
