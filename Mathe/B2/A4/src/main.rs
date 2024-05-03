use itertools::Itertools;

fn main() {
    let sample_size = 100000;

    let result = (6..).find(|&rounds| {
        let win_count = (0..sample_size)
            .filter(|_| (0..rounds).map(|_| rand::random::<usize>() % 6).unique().count() == 6)
            .count();
        let win_rate = win_count as f64 / sample_size as f64;
        println!("Round: {}, Win rate: {}", rounds, win_rate);
        win_rate > 0.5
    }).unwrap();

    println!("Ab {} Runden hat der Spieler einen Vorteil. Die Bank darf demnach maximal n = {} wählen.", result, result - 1);
}
