use rayon::iter::{IntoParallelIterator, ParallelIterator};
use rust_xlsxwriter::Workbook;

fn main() {
    let mut workbook = Workbook::new();
    let worksheet = workbook.add_worksheet();

    worksheet.write(0, 0, "#Elements").unwrap();
    worksheet.write(1, 0, "#Comparisions").unwrap();

    let sample_size = 20;
    for i in 1..=25 {
        let count_sum = (0..sample_size).into_par_iter().map(|_| {
            let mut vec = Vec::with_capacity(2usize.pow(i));
            for _ in 0..2usize.pow(i) {
                vec.push(rand::random::<i32>());
            }
            let mut truth = vec.clone();
            truth.sort_unstable();
            
            let (sorted, count) = quicksort(vec);
            // überprüfe ob das Ergebnis korrekt ist
            assert_eq!(sorted, truth);
            count
        }).sum::<u64>();

        // berechne den Durchschnitt der Vergleiche
        let count = (count_sum as f32 / sample_size as f32) as i32;
        
        println!("Elements: {:10}, Comparisions: {:13}", 2usize.pow(i), count);
        
        // Schreibe Ergebiss in Excel Datei
        worksheet.write(0, i as u16, 2usize.pow(i) as i32).unwrap();
        worksheet.write(1, i as u16, count).unwrap();
    }
    workbook.save("quicksort.xlsx").unwrap();
}

fn quicksort(vec: Vec<i32>) -> (Vec<i32>, u64) {
    if vec.len() <= 1 {
        return (vec, 0);
    }
    let num_comparisons = vec.len() as u64 - 1;
    let mut iter = vec.into_iter();
    let pivot = iter.next().unwrap();
    let (left, right) = iter.partition(|&x| x < pivot);

    let (mut result, count) = quicksort(left);
    let (right_result, right_count) = quicksort(right);
    result.push(pivot);
    result.extend(right_result);
    (result, count + right_count + num_comparisons)
}