use std::collections::HashMap;
use std::fs;
use std::io::{BufRead, BufReader};

// Hashmap with dir as key and size as value. Size needs to be a pointer

// Recursion with a list of already calculated dir sizes.

// 1: For loop creates Hashmap with dir as key and size as value.
// 2: Input is iterated and

// 1: For loop fills HashMap<String, Vec<String>> with contents of each folder

pub fn nospace_1() {
    let mut dir_sizes: HashMap<String, u32> = HashMap::new();
    let mut dir_contents: HashMap<Vec<String>, u32> = HashMap::new();
    let mut n_dirs: usize = 0;
    let mut lines: Vec<String> = Vec::new();
    let mut buff_reader = BufReader::new(fs::File::open("example.txt").expect("Failed to open file!"));
    let mut line = String::new();

    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!");
        if parsed.contains("$ cd ") {
            n_dirs += 1;
        }
        lines.push(parsed);
    }

    let mut dir_name = String::new();
    let mut content: Vec<String> = Vec::new();
    for line in &lines {
        if line.contains("$ cd ") {
            
            if !line.contains(" ..") {
                dir_name = line.split_whitespace().next().expect("Failed to split line").parse::<String>().expect("Failed to parse string!");
            }
        } else {
            if !line.contains("$ ls") {
                // if line.contains("dir ") {

                // } else {
                //     let file_size
                // }
            }
        }
    }

    // while dir_sizes.len() < n_dirs {
    //     let mut dir_name = String::new();
    //     for line in &lines {
    //         if line.contains("$ cd ") {
    //             if !line.contains(" ..") {
    //                 dir_name = line.split_whitespace().next().expect("Failed to split line").parse::<String>().expect("Failed to parse string!");
    //             }
    //         } else {
    //             if !line.contains("$ ls") {
    //                 if line.contains("dir ") {

    //                 } else {
    //                     let file_size
    //                 }
    //             }
    //         }
    //     }
    // }

    // loop {
    //     let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
    //     // let parsed: String = line.trim().parse().expect("Failed to parse line!");
    //     line = line.trim().parse().expect("Failed to parse line!");
    //     if num_bytes == 0 {
    //         break;
    //     } else {
    //         println!("{}", line);
    //     }
    //     // if parsed[0..2].eq("dir") {
    //     //     n_dirs += 1;
    //     // }
        
    //     // lines.push(parsed);
    // }
    
    // for line in lines {
    //     if line[0..1].eq("cd") {
    //         let split = line.split_whitespace();
    //         split.next();
    //         let dir_name = split.next().expect("Dir name is None!");
    //         if dir_name != ".." {

    //         }
    //     }

    // }
    println!("{}", n_dirs)
}

fn dir_size(dir_sizes: &HashMap<String, u32>, lines: Vec<String>) {

}