use std::fs;
use std::io::{BufRead, BufReader};

pub fn treehouse_1() {
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut n_visible: u32 = 0;
    let mut rows: Vec<Vec<u32>> = Vec::new();
    let mut cols: Vec<Vec<u32>> = Vec::new();

    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!").trim().parse().expect("Failed to parse line!");
        let mut digits: Vec<u32> = Vec::new();
        for c in parsed.chars() {
            digits.push(c.to_digit(10).expect("Failed to parse char as digit!"))
        }
        rows.push(digits);
    }

    let n_rows = rows.len();
    let n_cols = rows[0].len();


    for col_idx in 0..n_cols {
        let mut col: Vec<u32> = Vec::new();
        for row_idx in 0..n_rows {
            col.push(rows[row_idx][col_idx]);
        }
        cols.push(col);
    }

    for row_idx in 0..n_rows {
        for col_idx in 0..n_cols {
            let height = rows[row_idx][col_idx];
            let visible_from_left = visible(height, rows[row_idx][0..col_idx].to_vec());
            let visible_from_right = visible(height, rows[row_idx][col_idx+1..n_cols].to_vec());
            let visible_from_top = visible(height, cols[col_idx][0..row_idx].to_vec());
            let visible_from_bottom = visible(height, cols[col_idx][row_idx+1..n_rows].to_vec());

            if visible_from_left || visible_from_right || visible_from_top || visible_from_bottom {
                n_visible += 1;
            }
        }
    }

    println!("{}", n_visible);
}

fn visible(height: u32, heights: Vec<u32>) -> bool {
    for h in heights {
        if h >= height {
            return false;
        }
    }
    return true;
}