use std::fs;
use std::io::{BufRead, BufReader};

pub fn ropes_2() {
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut max_score: u32 = 0;
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
            let mut left_view = rows[row_idx][0..col_idx].to_vec();
            left_view.reverse();
            let left_score = score(height, left_view);
            let right_score = score(height, rows[row_idx][col_idx+1..n_cols].to_vec());
            let mut top_view = cols[col_idx][0..row_idx].to_vec();
            top_view.reverse();
            let top_score = score(height, top_view);
            let bottom_score = score(height, cols[col_idx][row_idx+1..n_rows].to_vec());

            let total_score = left_score * right_score * top_score * bottom_score;
            if  total_score > max_score {
                max_score = total_score;
            }
        }
    }

    println!("{}", max_score);
}

fn score(height: u32, heights: Vec<u32>) -> u32 {
    for (i, h) in heights.iter().enumerate() {
        if h >= &height {
            return i as u32 + 1;
        }
    }
    return heights.len() as u32;
}