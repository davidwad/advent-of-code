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
    let mut dir_contents: HashMap<String, Vec<String>> = HashMap::new();
    // let mut n_dirs: usize = 0;
    let buff_reader = BufReader::new(fs::File::open("example.txt").expect("Failed to open file!"));
    let mut dir_name: String =  String::new();
    let mut content: Vec<String> = Vec::new();
    let mut line_idx: u32 = 0;
    for line in buff_reader.lines() {
        let parsed: String = line.expect("Failed to parse line!");
        if parsed.contains("$ cd ") {
            if !parsed.contains(" ..") {
                if line_idx != 0 {
                    dir_contents.insert(dir_name, content);
                    content = Vec::new();
                }
                let mut split = parsed.split_whitespace();
                split.next();
                split.next();
                dir_name = split.next().expect("Failed to split line!").parse::<String>().expect("Failed to parse string!");
                // n_dirs += 1;
            }
        } else if !parsed.contains("$ ls") {
            content.push(parsed);
        }
        line_idx += 1;
    }
    dir_contents.insert(dir_name, content);

    for k in dir_contents.keys() {
        dir_sizes.insert(k.to_string(), 0);
    }

    dir_size(&dir_sizes, &dir_contents, String::from("/"));

    // for (name, content) in dir_contents.iter() {
    //     println!("Contents of dir {}:", name);
    //     for line in content {
    //         println!("{}", line);
    //     }
    //     println!("----------------------------------");
    // }

    //println!("{}", n_dirs)
}

fn dir_size(dir_sizes: &HashMap<String, u32>, dir_contents: &HashMap<String, Vec<String>>, dir_name: String) {
    let mut contents = dir_contents.get(&dir_name).expect("Key not found in hashmap!");
    for line in contents {
        if line.contains("dir ") {
            dir_size(&dir_sizes, &dir_contents, dir_name);
        }
    }
}