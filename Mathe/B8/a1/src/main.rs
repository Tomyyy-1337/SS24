use rayon::iter::{IntoParallelIterator, ParallelIterator};

fn main() {
    // (5..50).into_par_iter().for_each(|exponent| {
    //     let sample_size = 1u64 << exponent;
    //     let total_win = (0..sample_size)
    //         .map(|_| 1u64 << ((0..).position(|_| rand::random::<u8>() % 2 == 0).unwrap().min(47)))
    //         .sum::<u64>();

    //     let expected_win = total_win as f64 / sample_size as f64;
    //     println!("Expected win: {} with exponent {}", expected_win, exponent);
    // });

    let mut exprected_win = 0.0;
    
    for i in 1..= 100000 {
        exprected_win += 2f64.powi(i.min(47)) / 2f64.powi(i);
    }

    println!("Expected win: {}", exprected_win);

    
}
