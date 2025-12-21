use std::thread;

mod part1;
mod part2;

const STACK_SIZE: usize = 256 * 1024 * 1024;

fn run() {
    part1::part1();
    part2::part2();
}

fn main() {
    // Spawn thread with explicit stack size
    let child = thread::Builder::new()
        .stack_size(STACK_SIZE)
        .spawn(run)
        .unwrap();

    // Wait for thread to join
    child.join().unwrap();
}
