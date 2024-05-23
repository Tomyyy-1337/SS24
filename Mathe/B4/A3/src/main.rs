#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Direction {
    Left,
    Right,
    Empty,
}

impl Direction {
    fn random() -> Direction {
        match rand::random::<u8>() % 3 {
            0 => Direction::Left,
            1 => Direction::Right,
            _ => Direction::Empty,
        }
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
enum Outcome {
    Win,
    Lose,
}

fn main() {
    let wins = (0..10000000).map(|_| round()).filter(|&x| x == Outcome::Win).count();
    let winrate = wins as f64 / 10000000.0;
    println!("Winrate: {:.2}%", winrate * 100.0);
}

fn round() -> Outcome {
    let a = [Direction::random(), Direction::random(), Direction::random()];
    let left = a.iter().filter(|&x| *x == Direction::Left).count();
    let right = a.iter().filter(|&x| *x == Direction::Right).count();
    if (left >= 2 && right == 0) || (right >= 2 && left == 0) {
        Outcome::Win
    } else {
        Outcome::Lose
    }
}