use rand::random;

fn main() {
    let A = Matrix::from_vec(vec![
        1.0, 2.0, 
        3.0, 4.0
        ], 2, 2);
    let B = Matrix::from_vec(vec![
        5.0, 6.0, 
        7.0, 8.0
        ], 2, 2);
    let C = A.multiply(&B);
    let D = Matrix::from_vec(vec![
        5.0, 5.0, 
        3.0, 50.0
        ], 2, 2);

    println!("C = A * B: {:?}", monte_carlo_test(&A, &B, &C));
    println!("D = A * B: {:?}", monte_carlo_test(&A, &B, &D));
}

fn monte_carlo_test(A: &Matrix, B: &Matrix, C: &Matrix) -> bool {
    // random x vector with size of C.cols using rand crate#
    for i in 0..10 {
        let x = (0..C.cols).map(|_| random::<f32>() as f64).collect::<Vec<f64>>();
        let P = C.vec_multiply(&x);
        let Q = A.vec_multiply(&B.vec_multiply(&x));
        if P != Q {
            return false;
        }
    }
    true
}

#[derive(Debug, Clone)]
struct Matrix {
    data: Vec<f64>,
    rows: usize,
    cols: usize,
}

impl Eq for Matrix {}

impl PartialEq for Matrix {
    fn eq(&self, other: &Self) -> bool {
        if self.rows != other.rows || self.cols != other.cols {
            return false;
        }
        for i in 0..self.rows {
            for j in 0..self.cols {
                if (self.get(i, j) - other.get(i, j)).abs() > 1e-6 {
                    return false;
                }
            }
        }
        true
    }
}

impl Matrix {
    fn from_vec(data: Vec<f64>, rows: usize, cols: usize) -> Self {
        Matrix { data, rows, cols }
    }

    fn get(&self, row: usize, col: usize) -> f64 {
        self.data[row * self.cols + col]
    }

    fn set(&mut self, row: usize, col: usize, value: f64) {
        self.data[row * self.cols + col] = value;
    }

    fn vec_multiply(&self, x: &Vec<f64>) -> Vec<f64> {
        let mut result = vec![0.0; self.rows];
        for i in 0..self.rows {
            for j in 0..self.cols {
                result[i] += self.get(i, j) * x[j];
            }
        }
        result
    }

    fn multiply(&self, other: &Matrix) -> Matrix {
        let mut result = vec![0.0; self.rows * other.cols];
        for i in 0..self.rows {
            for j in 0..other.cols {
                for k in 0..self.cols {
                    result[i * other.cols + j] += self.get(i, k) * other.get(k, j);
                }
            }
        }
        Matrix::from_vec(result, self.rows, other.cols)
    }
}