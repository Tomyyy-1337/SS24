use rand::thread_rng;
use rand::seq::SliceRandom;

fn main() {
    println!("Aufgabenteil b):");

    let omega = vec![(0,0), (0,1), (1,0), (1,1)];

    let m = |(_, _): &(u8, u8)| 1.0/4.0;

    let x = |&(a, b): &(u8, u8)| (a as f64 + b as f64) * (a as f64 - b as f64);

    let (v,e) = verteilung_erwartungswert(&omega, m, x);
    println!("Erwartungswert: {}, Varianz: {}", e, v);
    

    println!("Aufgabenteil c):");
    println!("Probe für A3");

    let omega = vec![1,2,3,4,5,6];

    let m = |_: &u8| 1.0/6.0;

    let x = |x: &u8| (*x as f64 + 1.0) * 2.0;

    let (v,e) = verteilung_erwartungswert(&omega, m, x);
    println!("Erwartungswert: {}, Varianz: {}", e, v);

    println!("Probe für A4 b)");
    for n in 1..1000 {
        let omega = (1..=n).collect::<Vec<u64>>();

        let m = |_: &u64| 1.0/n as f64;

        let mut shuffled_omega = omega.clone();
        shuffled_omega.shuffle(&mut thread_rng());

        let x = |&x: &u64| shuffled_omega[x as usize - 1] as f64;

        let (varianz, erwartungswert) = verteilung_erwartungswert(&omega, m, x);
        
        let calculated_varianz = (n as f64 + 1.0) * (n as f64 - 1.0) / 12.0;
        let calculated_erwartungswert = (n as f64 + 1.0) / 2.0;

        assert!((varianz - calculated_varianz).abs() < 1e-9, "Varianz stimmt nicht überein");
        assert!((erwartungswert - calculated_erwartungswert).abs() < 1e-9, "Erwartungswert stimmt nicht überein");
    }
    println!("Alle Tests bestanden");
}

// finction with generic type 
fn verteilung_erwartungswert<T>(omega: &Vec<T>, m: impl Fn(&T) -> f64, x: impl Fn(&T) -> f64) -> (f64, f64) {
    let erwartungsert = omega.iter()
        .map(|e| m(e) * x(e))
        .sum::<f64>();
    let varianz = omega.iter()
        .map(|e| m(e) * (x(e) - erwartungsert).powi(2))
        .sum::<f64>();

    (varianz, erwartungsert)
} 
