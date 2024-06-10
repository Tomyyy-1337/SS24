fn main() {
    let input = vec![56, 64, 58, 61, 75, 86, 17, 62, 8, 50, 87, 99, 67, 10, 74];

    let (_, num_comparisons) = bad_quicksort(input);

    println!("Number of comparisons: {}", num_comparisons);
}

fn bad_quicksort(mut vec: Vec<i32>) -> (Vec<i32>, u64) {
    if vec.len() <= 1 {
        return (vec, 0);
    }
    let num_comparisons = vec.len() as u64 - 1;
    let pivot = *vec.iter().min().unwrap();
    vec.retain(|&x| x != pivot);
    let (left, right) = vec.into_iter().partition(|&x| x < pivot);

    let (mut result, count) = bad_quicksort(left);
    let (right_result, right_count) = bad_quicksort(right);
    result.push(pivot);
    result.extend(right_result);
    (result, count + right_count + num_comparisons)
}