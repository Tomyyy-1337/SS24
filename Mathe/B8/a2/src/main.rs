fn main() {
    let sample_size = 1000;
    
    let money: i64 = (0..sample_size)
        .map(|_| match roll_dice(2) {
            7 | 11 => 1,
            2 | 3 | 12 => -1,
            s => loop {
                match roll_dice(2) {
                    7 => return -1,
                    n => if n == s { return 1; }
                }   
            }
        })
        .sum();

    println!("Mittlerer Gewinn: {:.2}€", money as f64 / sample_size as f64)
}

fn roll_dice(number: usize) -> u8 {
    (0..number).map(|_| rand::random::<u8>() % 6 + 1).sum()
}   