use rand::Rng;
use rand::seq::IteratorRandom;

fn main() {
    let sample_size = 10000000;
    
    let win_rate_keep_guess = evaluate_strategy(simulate_game_keep_guess, sample_size);
    let win_rate_change_guess = evaluate_strategy(simulate_game_change_guess, sample_size);

    println!("Win rate when keeping the initial choice: {:.2}%", win_rate_keep_guess * 100.0);
    println!("Win rate when changing the initial choice: {:.2}%", win_rate_change_guess * 100.0);    
}

fn evaluate_strategy(f: fn() -> bool, n: u32) -> f64 {
    (0..n).filter(|_| f()).count() as f64 / n as f64
}

fn simulate_game_keep_guess() -> bool {
    let wining_door: u8 = rand::thread_rng().gen_range(1..=3);
    let player_choice: u8 = rand::thread_rng().gen_range(1..=3);
    player_choice == wining_door
}

fn simulate_game_change_guess() -> bool {
    let wining_door: u8 = rand::thread_rng().gen_range(1..=3);
    let player_choice: u8 = rand::thread_rng().gen_range(1..=3);
    let host_choice = (1..=3).filter(|&door| door != player_choice && door != wining_door).choose(&mut rand::thread_rng()).unwrap();
    let new_choice = (1..=3).find(|&door| door != host_choice && door != player_choice).unwrap();
    new_choice == wining_door
}