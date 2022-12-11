use std::fs;
use std::io::{BufRead, BufReader};

pub fn part_1() {
    const N_ROUNDS: usize = 20;

    let mut buff_reader = BufReader::new(fs::File::open("example.txt").expect("Failed to open file!"));
    let mut monkeys: Vec<Monkey> = Vec::new();
    let mut targets: Vec<Targets> = Vec::new();
    loop {
        let mut line = String::new();
        let num_bytes = buff_reader.read_line(&mut line).expect("Failed to read input!");
        if num_bytes == 0 {
            break;
        } else {
            let parsed: String = String::from(line.trim());
            if parsed.contains("Monkey ") {
                buff_reader.read_line(&mut line).expect("Failed to read input!");
                let parsed: String = String::from(line.trim());
                let items: Vec<u32> = parsed.split_at(29).1.split(", ").map(|s| s.parse::<u32>().expect("Failed to parse string as digit!")).collect();

                let mut line = String::new();
                buff_reader.read_line(&mut line).expect("Failed to read input!");
                let parsed: String = String::from(line.trim());
                let operand = parsed.chars().nth(21).expect("Failed to parse operand char!");
                // let value = parsed.split_at(23).1.parse::<u32>();
                let value = parsed.split_at(23).1;
                let operation: Operation;
                if value == "old" {
                    operation = Operation::Square;
                } else {
                    let value = value.parse::<u32>().expect("Failed to parse value as digit!");
                    if operand == '+' {
                        operation = Operation::Add(value);
                    } else if operand == '*' {
                        operation = Operation::Multiply(value);
                    } else {
                        panic!("Unknown operand!");
                    }
                }
                // println!("{}", value);

                let mut line = String::new();
                buff_reader.read_line(&mut line).expect("Failed to read input!");
                let parsed: String = String::from(line.trim());
                let divisor: u32 = parsed.split_at(19).1.parse::<u32>().expect("Failed to parse divisor as digit!");
                //println!("{}", divisor);

                let mut line = String::new();
                buff_reader.read_line(&mut line).expect("Failed to read input!");
                let parsed: String = String::from(line.trim());
                let success_target: u32 = parsed.split_at(25).1.parse::<u32>().expect("Failed to parse success target as digit!");
                // println!("{}", success_target);
                

                let mut line = String::new();
                buff_reader.read_line(&mut line).expect("Failed to read input!");
                let parsed: String = String::from(line.trim());
                let failure_target: u32 = parsed.split_at(26).1.parse::<u32>().expect("Failed to parse failure target as digit!");
                // println!("{}", failure_target);

                let monkey = Monkey {
                    items: items,
                    operation: operation,
                    divisor: divisor,
                    on_success: success_target,
                    on_failure: failure_target,
                    inspect_count: 0
                };
                targets.push(Targets { failure: failure_target, success: success_target });
                monkeys.push(monkey);
            }
        }
    }

    for _ in 0..N_ROUNDS {
        // let mut monkey = monkeys.pop().expect("Monkey");
        // monkey.inspect_items();

        for i in 0..monkeys.len() {
            // let mut monkey_iter = monkeys.iter_mut();
            let mut monkey: Monkey;
            let mut monkeys_copy: Vec<Monkey> = Vec::new();
            for (j, m) in monkeys.iter().enumerate() {
                if i == j {
                    monkey = *m;
                }
                monkeys_copy.push(*m);
            }
            let mut success_monkey: Monkey;
            let mut failure_monkey: Monkey;
            // let monkey = monkey_iter.nth(i).expect("Monkey out of range!");
            // let success_monkey = monkey_iter.nth(monkey.on_success as usize).expect("Monkey out of range!");
            // let failure_monkey = monkey_iter.nth(monkey.on_failure as usize).expect("Monkey out of range!");
            let throws: Vec<Throw> = monkey.inspect_items();
            for throw in throws.iter() {
                if throw.target == monkey.on_success {
                    success_monkey.receive_item(throw.item);
                } else if throw.target == monkey.on_success {
                    failure_monkey.receive_item(throw.item);
                } else {
                    panic!("Unknown target!");
                }
            }
        }
        
        // for mut monkey in &monkeys {
        //     let throws: Vec<Throw> = monkey.inspect_items();
        //     for throw in throws.iter() {
        //         //monkeys.iter().nth(throw.target as usize).expect("l").receive_item(throw.item);

        //     }
        // }

        // for mut monkey in monkeys.iter_mut() {
        //     monkey.inspect_items(monkeys);
        // }
    }

    let mut inspection_counts: Vec<u32> = monkeys.iter().map(|m: &Monkey| -> u32 {m.inspect_count}).collect();
    inspection_counts.sort();
    let monkey_business = inspection_counts[0] * inspection_counts[1];
    println!("{}", monkey_business);
}

struct Monkey {
    items: Vec<u32>,
    // operation_type: char,
    // operation_value: u32,
    operation: Operation,
    divisor: u32,
    on_success: u32,
    on_failure: u32,
    inspect_count: u32
}

impl Monkey {
    fn inspect_items(&mut self) -> Vec<Throw> {
        let mut throws: Vec<Throw> = Vec::new();
        self.items.reverse();
        while self.items.len() > 0 {
            let mut item = self.items.pop().expect("Expected items to be non-empty!");
            item = match self.operation {
                Operation::Add(x) => x + item,
                Operation::Multiply(x) => x * item,
                Operation::Square => item * item,
                _ => 0
            };
            // item = (self.operation)(item);
            item = item  / 3;
            let target = match item % self.divisor {
                0 => self.on_success,
                _ => self.on_failure
            };

            let throw = Throw {item: item, target: target};
            throws.push(throw);
            self.inspect_count += 1;
        }
        // for throw in throws {
        //     monkeys[throw.target as usize].receive_item(throw.item);
        // }

        throws
    }

    fn receive_item(&mut self, item: u32) {
        self.items.push(item);
    }
}

enum Operation {
    Add(u32),
    Multiply(u32),
    Square
}

struct Targets {
    failure: u32,
    success: u32
}
// struct Monkey {
//     items: Vec<u32>,
//     operation: fn(u32) -> u32,
//     test: fn(u32) -> u32
// }
// DIVISOR, OPERAND TYPE, OPERAND VALUE, SUCCESS TARGET AND FAILURE TARGET
// impl Monkey {
//     fn inspect_items(&mut self) -> Vec<Throw> {
//         let mut instructions: Vec<Throw> = Vec::new();
//         self.items.reverse();
//         while self.items.len() > 0 {
//             let mut item = self.items.pop().expect("Expected items to be non-empty!");
//             item = (self.operation)(item);
//             item = item  / 3;
//             let to_monkey = (self.test)(item);
//             let throw = Throw {worry: item, to_monkey: to_monkey};
//             instructions.push(throw);
//         }
//         instructions
//     }

//     fn set_operation(&mut self, operation: fn (u32) -> u32) {
//         self.operation = operation;
//     }

//     fn set_test(&mut self, operation: fn (u32) -> u32) {
//         self.operation = operation;
//     }
// }

struct Throw {
    item: u32,
    target: u32
}
