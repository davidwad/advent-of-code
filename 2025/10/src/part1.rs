use std::collections::HashSet;
use std::fs;
use std::io::{BufRead, BufReader};

pub fn part1() {
    let mut sum = 0;
    let mut buff_reader =
        BufReader::new(fs::File::open("input.txt").expect("Failed to read input!"));
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader
            .read_line(&mut line)
            .expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        }

        let split: Vec<&str> = line.trim().split(" ").collect();

        let mut target = Vec::<bool>::new();
        let mut buttons = Vec::<Vec<usize>>::new();
        for (i, s) in split.iter().enumerate() {
            if i == 0 {
                for j in 1..s.len() - 1 {
                    let c = s.chars().nth(j).expect("Index out of bounds");
                    target.push(c == '#');
                }
            } else if i == split.len() - 1 {
                continue;
            } else {
                let mut button = Vec::<usize>::new();
                let trimmed = s.trim_start_matches("(").trim_end_matches(")");
                let button_split = trimmed.split(",");
                for c in button_split {
                    button.push(
                        c.parse::<usize>()
                            .expect("Failed to parse character as u32"),
                    );
                }
                buttons.push(button);
            }
        }
        let mut lights = HashSet::<Vec<bool>>::new();
        let mut light = Vec::<bool>::new();
        for _ in 0..target.len() {
            light.push(false);
        }
        lights.insert(light);

        let mut i = 0;
        while !lights.contains(&target) {
            let mut new_lights = HashSet::<Vec<bool>>::new();
            for button in &buttons {
                for light in &lights {
                    let new_light = push_button(&light, &button);
                    new_lights.insert(new_light);
                }
            }
            lights = new_lights;
            i += 1;
        }
        sum += i;
    }

    println!("{sum}");
}

fn push_button(lights: &Vec<bool>, button: &Vec<usize>) -> Vec<bool> {
    let mut res = Vec::<bool>::new();
    for light in lights {
        res.push(*light);
    }
    for light_idx in button {
        res[*light_idx] = !res[*light_idx];
    }

    return res;
}
