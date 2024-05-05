use itertools::Itertools;
use rayon::prelude::*;

fn main() {
    let sample_size = 10000000;

    let result = (6..).find(|&rounds| {
        let win_count = (0..sample_size).into_par_iter()
            .filter(|_| (0..rounds).map(|_| rand::random::<usize>() % 6).unique().count() == 6)
            .count();
        let win_rate = win_count as f64 / sample_size as f64;
        println!("Round: {}, Win rate: {}", rounds, win_rate);
        win_rate > 0.5
    }).unwrap();

    println!("Ab {} Runden hat der Spieler einen Vorteil. Die Bank darf demnach maximal n = {} wählen.", result, result - 1);

    for i in 6..=result {
        let prob = 1.0 - (1.0f64 - 1.0/6.0).powi(i);
        println!("Die Wahrscheinlichkeit, dass der Spieler  gewinnt, beträgt: {:.2}%", prob.powi(6)); 
    }
}
