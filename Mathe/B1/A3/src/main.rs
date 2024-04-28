fn main() {
    let result = (1..=100000).filter(|x| x % 3 == 0 || x % 5 == 0 || x % 7 == 0 || x % 11 == 0).count();
    println!("Correct Value: {}", result);
    
    let n = 100000;
    let a = n / 3;
    let b = n / 5;
    let c = n / 7;
    let d = n / 11;
    let ab = n / (3 * 5);
    let ac = n / (3 * 7);
    let ad = n / (3 * 11);
    let bc = n / (5 * 7);
    let bd = n / (5 * 11);
    let cd = n / (7 * 11);
    let abc = n / (3 * 5 * 7);
    let abd = n / (3 * 5 * 11);
    let acd = n / (3 * 7 * 11);
    let bcd = n / (5 * 7 * 11);
    let abcd = n / (3 * 5 * 7 * 11);

    let result = a + b + c + d - ab - ac - ad - bc - bd - cd + abc + abd + acd + bcd - abcd;
    println!("Calculation Result: {}", result);
}
