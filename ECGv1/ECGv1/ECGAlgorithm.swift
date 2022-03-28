//
//  ECGAlgorithm.swift
//  ECGv1
//
//  Created by Lucio Santella on 3/23/22.
//

import Foundation
import UIKit
import CoreBluetooth
import Charts
import Numerics
import Accelerate
//import SwiftMatrix
import LASwift

/*-------------------------------CSV Read-------------------------------*/
func getCSVData(dataFile: String) -> [[Double]] {
    enum CustomError: Error {
        case notAnItOrADouble(String)
    }

    do {
        let content = try String(contentsOfFile: dataFile)
        let numberRows = try content
            .split(separator: "\n")
            .map { line in
                try line.split(separator: ",").map { substring -> Double in
                    let token = String(substring)
                    guard let value: Double = Double(token) ?? Double(token) else {
                        throw CustomError.notAnItOrADouble(token)
                    }
                    return value
                }
            }
        return numberRows

    } catch (let error) {
        print(error)
    }
    
    return [[1,2,3]]
}

/*-------------------------------Mean function-------------------------------*/
func calculateMean(array: [Int]) -> Double {
    
    // Calculate sum ot items with reduce function
    let sum = array.reduce(0, { a, b in
        return a + b
    })
    
    let mean = Double(sum) / Double(array.count)
    return Double(mean)
}

/*-------------------------------Transpose function-------------------------------*/
//func transpose(_ A: [[Double]]) -> [[Double]] {
//
//    var c = Array(repeating: Array(repeating: 0.0, count: A.count), count: A[0].count)
//
//    for i in stride(from: 0, to: A.count, by: 1) {
//        for j in stride(from: 0, to: A[i].count, by: 1) {
//            c[j][i] = Double(Int(A[i][j]));
//        }
//    }
//    return c;
//}

public func transpose(_ A: Matrix) -> Matrix {
    let C: Matrix = zeros(A.cols, A.rows)
    vDSP_mtransD(A.flat, 1, &(C.flat), 1, vDSP_Length(A.cols), vDSP_Length(A.rows))
    return C
}

/*-------------------------------Overwriting Power Operator-------------------------------*/
infix operator ** : MultiplicationPrecedence
func ** (num: Double, power: Double) -> Double{
    return pow(num, power);
}

/*-------------------------------Dot Product function-------------------------------*/
//func dot(a: [Float], b: [Float]) -> Float {
//    return zip(a, b).map(*).reduce(0, +);
//}

public func mtimes(_ A: Matrix, _ B: Matrix) -> Matrix {
    precondition(A.cols == B.rows, "Matrix dimensions must agree")
    let C: Matrix = zeros(A.rows, B.cols)
    vDSP_mmulD(A.flat, 1, B.flat, 1, &(C.flat), 1, vDSP_Length(A.rows), vDSP_Length(B.cols), vDSP_Length(A.cols))
    return C
}

/*-------------------------------Inverse function-------------------------------*/
//func invert(matrix : [Double]) -> [Double] {
//    var inMatrix = matrix
//    var N = __CLPK_integer(sqrt(Double(matrix.count)))
//    var pivots = [__CLPK_integer](repeating: 0, count: Int(N))
//    var workspace = [Double](repeating: 0.0, count: Int(N))
//    var error : __CLPK_integer = 0
//
//    withUnsafeMutablePointer(to: &N) {
//        dgetrf_($0, $0, &inMatrix, $0, &pivots, &error)
//        dgetri_($0, &inMatrix, $0, &pivots, &workspace, $0, &error)
//    }
//    return inMatrix
//}

/*-------------------------------Predict y given x-------------------------------*/
func predict(x: Int, coefficients: [Int]) -> Int{

    var prediction = 0

    for i in 0...coefficients.count {

        prediction += coefficients[i] * Int((Double(x)**Double(i)));

  }

    return prediction;

}


/*-------------------------------Algorithm-------------------------------*/
//    let ECG_data = [100,200]
//    let heartRate = UnsafeMutablePointer<Double>.allocate(capacity: 1)
//    heartRate.initialize(to: 0.1)
//    let leadsFlipped = UnsafeMutablePointer<Bool>.allocate(capacity: 2)
//    leadsFlipped.initialize(to: false)

//reading test data from CSV file
let testECGdata = getCSVData(dataFile: "./data1.csv");

public func polynomialFit(samples: Int, values: [[Double]], order: Int) -> Matrix {
    
    var xMatrix: [[Double]] = [];
    
    let yMatrix = transpose(Matrix(values));

    for i in 0...samples {

        var temp: [[Double]] = [];

        for j in 0...order  {
            
            let powTemp = Double(Int(i))**Double(j);
            
            temp.append([powTemp]);

        }

        xMatrix.append(contentsOf: temp);

    }

    let xMatrixT = transpose(Matrix(xMatrix));

//    let dot1 = Matrix(xMatrixT)°Matrix(yMatrix);
//    let dot2 = Matrix(xMatrixT)°Matrix(yMatrix);
    let dot1 = mtimes(xMatrixT, Matrix(xMatrix));
    let dot2 = mtimes(xMatrixT, yMatrix);
    let dotInv = inv(dot1);

    let coefficients = mtimes(dotInv, dot2);

    print(coefficients);
    return coefficients;

}


func AlgHRandLeads(ECG_data: [[Double]]) -> (Double, Bool, [Int]) {
    //init return vars
    var heartRate = 0.1;
    var leadsFlipped = false;

    //getting the length of the array
    let t = ECG_data.count;

    //fitting the data and detrending it
    let pol_order = 9;
    let coeffs = polynomialFit(samples: t, values: ECG_data, order: 9);
//    var f_y.push()
    
//    var ECG_detrend = ECG_data - f_y;
//
//    //Find local maxima which corresponds to top of the QRS complex
//    let highest_values : [Double] = []
//    let highest_index : [Double] = []
//    for i in ECG_detrend.count {
//        var max_val = max(ECG_detrend)
//        var mean_val = calculateMean(array: ECG_detrend)
//
//        if (ECG_detrend[i] >= (max_val + mean_val)/2) {
//            highest_values.insert(ECG_detrend[i])
//            highest_index.insert(i)
//        }
//
//    }
//
//    //Find local minima which corresponds to top of the QRS complex if flipped
//    var modified_detrend = -ECG_detrend;
//
//    var lowest_values : [Double] = []
//    var lowest_index : [Double] = []
//    for i in modified_detrend.count {
//        let max_val = max(modified_detrend)
//        let mean_val = calculateMean(array: modified_detrend)
//
//        if (modified_detrend[i] >= (max_val + mean_val)/2) {
//            lowest_values.insert(ECG_detrend[i])
//            lowest_index.insert(i)
//        }
//
//    }
//
//    let avg_highest_value = calculateMean(array: highest_values);
//    let avg_lowest_value = calculateMean(array: lowest_values);
//
//
//    if (avg_lowest_value > avg_highest_value) {
//        leadsFlipped = true;
//        heartRate = 0;
//    }
//    else {
//        leadsFlipped = false;
////            r_index = find(highest_values);
//        heartRate = highest_values.count * 6.0;
//    }
//
//    return (heartRate, leadsFlipped, polyfitData)
    
    return (70, true, [1,2])
}
