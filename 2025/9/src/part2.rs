use core::panic;
use std::collections::HashSet;
use std::fs;
use std::io::{BufRead, BufReader};

// NEW IDEA: Fill matrix of outside tiles by expanding from a tile outside of the inner tiles, e.g. (0,0)
// TODO: 422041553 and 1554335760 was too low. Probably need to handle some special case, maybe
// ..............
// .#XXXXX#XXX#..
// .#.........X..
// .#XXX#.....X..
// ..#XX#.....X..
// ..#XXXXXX#.X..
// .........X.X..
// .........#X#..
// ..............

pub fn part2() {
    let clockwise = true;
    let mut tiles = Vec::<(i64, i64)>::new();
    let mut mines = Vec::<(i64, i64)>::new();
    let mut buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    let mut previous_tile = (0 as i64, 0 as i64);
    let mut i = 0;
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split(",").collect();
        let tile = (split[0].parse::<i64>().expect("Failed to parse coordinate as i32"), split[1].parse::<i64>().expect("Failed to parse coordinate as i32"));
        tiles.push(tile);

        if i > 0 {
            let mine_coordinates = get_mine_coordinates(previous_tile, tile, clockwise);
            for c in mine_coordinates {
                mines.push(c);
            }
        }
        previous_tile = tile;
        i += 1;

        if (tile.0 - previous_tile.0).abs() == 1 || (tile.1 - previous_tile.1).abs() == 1 {
            println!("Special case: ({},{}) - ({},{})", previous_tile.0, previous_tile.1, tile.0, tile.1);
        }
    }

    let mine_coordinates = get_mine_coordinates(tiles[tiles.len() - 1], tiles[0], clockwise);
    for c in mine_coordinates {
        mines.push(c);
    }

    let mut max_area: i64 = 0;
    for i in 0..tiles.len() {
        for j in i+1..tiles.len() {
            let t1 = tiles[i];
            let t2 = tiles[j];
            // if rectangle_contains_tile(&tiles, t1, t2) || rectangle_contains_tile(&mines, t1, t2) {
            //     continue;
            // }
            if rectangle_contains_tile(&mines, t1, t2) {
                continue;
            }

            let dx = (t1.0 - t2.0 + 1).abs();
            let dy = (t1.1 - t2.1 + 1).abs();
            let area = dx * dy;
            if area > max_area {
                max_area = area;
                // println!("({}, {})  ({}, {})", t1.0, t1.1, t2.0, t2.1);
            }
        }
    }

    // print_tiles(&tiles, &mines);

    println!("{max_area}")

}

fn get_mine_coordinates(previous: (i64, i64), current: (i64, i64), clockwise: bool) -> HashSet::<(i64, i64)> {
    let mut res = HashSet::<(i64, i64)>::new();
    if previous.0 < current.0 { // Going right
        if clockwise {
            for x in previous.0..current.0 + 1 {
                res.insert((x, current.1 - 1));
            }
            return res;
        } else {
            for x in previous.0..current.0 + 1 {
                res.insert((x, current.1 + 1));
            }
            return res;
        }
    } else if previous.0 > current.0 { // Going left
        if clockwise {
            for x in current.0..previous.0 + 1 {
                res.insert((x, current.1 + 1));
            }
            return res;
        } else {
            for x in current.0..previous.0 + 1 {
                res.insert((x, current.1 - 1));
            }
            return res;
        }
    } else if previous.1 < current.1 { // Going down
        if clockwise {
            for y in previous.1..current.1 + 1 {
                res.insert((current.0 + 1, y));
            }
            return res;
        } else {
            for y in previous.1..current.1 + 1 {
                res.insert((current.0 - 1, y));
            }
            return res;
        }
    } else if previous.1 > current.1 { // Going up
        if clockwise {
            for y in current.1..previous.1 + 1 {
                res.insert((current.0 - 1, y));
            }
            return res;
        } else {
            for y in current.1..previous.1 + 1 {
                res.insert((current.0 + 1, y));
            }
            return res;
        }
    } else {
        panic!("Failed to calculate direction");
    }
}

fn rectangle_contains_tile(tiles: &Vec::<(i64, i64)>, t1: (i64, i64), t2: (i64, i64)) -> bool {
    for tile in tiles {
        if is_tile_inside_rectangle(*tile, t1, t2) {
            // println!("({}, {})  ({}, {})", t1.0, t1.1, t2.0, t2.1);
            return true;
        }
    }

    return false;
}

fn is_tile_inside_rectangle(tile: (i64, i64), t1: (i64, i64), t2: (i64, i64)) -> bool {
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
        // if tile.0 != t1.0 {
        //     return false;
        // }
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
        // if tile.1 != t1.1 {
        //     return false;
        // }
        return false;
    }

    return true;
}

fn print_tiles(tiles: &Vec::<(i64, i64)>, mines: &Vec::<(i64, i64)>) {
    let mut min_x = i64::MAX;
    let mut min_y = i64::MAX;
    let mut max_x = i64::MIN;
    let mut max_y = i64::MIN;
    for t in tiles {
        if t.0 < min_x {
            min_x = t.0;
        }
        if t.1 < min_y {
            min_y = t.1;
        }
        if t.0 >  max_x {
            max_x = t.0;
        }
        if t.1 > max_y {
            max_y = t.1;
        }
    }

    for y in min_y-1..max_y+2 {
        for x in min_x-2..max_x+3 {
            assert!(!(tiles.contains(&(x, y)) && mines.contains(&(x, y))));

            if tiles.contains(&(x, y)) {
                print!("#");
            } else if mines.contains(&(x, y)) {
                print!("X");
            } else {
                print!(".");
            }
        }
        println!();
    }
}