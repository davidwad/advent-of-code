use std::collections::HashMap;
use std::fs;
use std::io::{BufRead, BufReader};

pub fn nospace_2() {
    let mut dir_sizes: &mut HashMap<String, u32> = &mut HashMap::new();
    let mut dir_contents: HashMap<String, Vec<String>> = HashMap::new();
    let mut dir_stack: Vec<String> = Vec::new();
    let buff_reader = BufReader::new(fs::File::open("input.txt").expect("Failed to open file!"));
    let mut content: Vec<String> = Vec::new();
    let mut line_idx: u32 = 0;
    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!");
        if parsed.contains("$ cd ") {
            if !parsed.contains(" ..") {
                if line_idx != 0  && content.len() > 0 {
                    dir_contents.insert(dir_stack.join("/"), content);
                    content = Vec::new();
                }
                let mut split = parsed.split_whitespace();
                split.next();
                split.next();
                let dir_name = split.next().expect("Failed to split line!").parse().expect("Failed to parse line as string!");
                dir_stack.push(dir_name);

            } else {
                if line_idx != 0  && content.len() > 0 {
                    dir_contents.insert(dir_stack.join("/"), content);
                    content = Vec::new();
                }
                dir_stack.pop();
            }
        } else if !parsed.contains("$ ls") {
            content.push(parsed);
        }
        line_idx += 1;
    }
    dir_contents.insert(dir_stack.join("/"), content);

    for k in dir_contents.keys() {
        dir_sizes.insert(k.to_string(), 0);
    }

    dir_size(&mut dir_sizes, &dir_contents, String::from("/"));

    const AVAILABLE_SPACE: u32 = 70000000;
    const REQUIRED_SPACE: u32 = 30000000;

    let root_dir_size = dir_sizes.get("/").expect("Root dir not in dir_sizes!");
    let unused_space = AVAILABLE_SPACE - root_dir_size;
    let mut best_dir_size = u32::MAX;
    for size in dir_sizes.values() {
        if unused_space + size >= REQUIRED_SPACE {
            if *size < best_dir_size {
                best_dir_size = *size;
            }
        }
    }

    println!("{}", best_dir_size);
}

fn dir_size(dir_sizes: &mut HashMap<String, u32>, dir_contents: &HashMap<String, Vec<String>>, dir_name: String) -> u32 {
    let contents = dir_contents.get(&dir_name).expect("Key not found in hashmap!");
    let mut total_size = 0;
    for line in contents {
        if line.contains("dir ") {
            let mut split = line.split_whitespace();
            split.next();
            let mut subdir_name = String::new();
            subdir_name += &dir_name;
            subdir_name += "/";
            subdir_name += split.next().expect("Failed to split line!");
            let subdir_size = dir_sizes.get(&subdir_name).expect("Subdir not found in hashmap!");
            if *subdir_size != 0 {
                total_size += subdir_size;
            } else {
                total_size += dir_size(dir_sizes, &dir_contents, subdir_name);
            }
            
        } else {
            let mut split = line.split_whitespace();
            let file_size: u32 = split.next().expect("Could not parse line!").parse().expect("Failed to parse file size!");
            total_size += file_size;
        }
    }
    dir_sizes.insert(dir_name, total_size).expect("Failed to insert dir size!");
    return total_size;
}