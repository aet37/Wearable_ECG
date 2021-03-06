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
    
    var returnValue: [[Double]] = [];

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
        returnValue = numberRows;

    } catch (let error) {
        print(error)
    }
    
    return returnValue
}

/*-------------------------------Mean function-------------------------------*/
func calculateMean(array: [Double]) -> Double {
    
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

/*-------------------------------To Voltage Operator-------------------------------*/
//public func (inputVal: Double) -> Double{
//    return inputVal ;
//}

/*-------------------------------Dot Product function-------------------------------*/
//func dot(a: [Float], b: [Float]) -> Float {
//    return zip(a, b).map(*).reduce(0, +);
//}

//public func mtimes(_ A: Matrix, _ B: Matrix) -> Matrix {
//    precondition(A.cols == B.rows, "Matrix dimensions must agree")
//    let C: Matrix = zeros(A.rows, B.cols)
//    vDSP_mmulD(A.flat, 1, B.flat, 1, &(C.flat), 1, vDSP_Length(A.rows), vDSP_Length(B.cols), vDSP_Length(A.cols))
//    return C
//}

func dotProduct(A: Matrix, B: Matrix) -> Matrix {
    var output: Matrix = zeros(A.rows, B.cols);

    for i in 0...A.rows - 1 {
        for j in 0...B.cols - 1 {
            var tempSum: Double = 0.0;
            for k in 0...A.cols - 1 {
                tempSum = tempSum + (A[i,k] * B[k,j]);
            }
            output[i,j] = tempSum;
        }
    }

    return Matrix(output)
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
func predict(x: Double, coefficients: [Double]) -> Double{

    var prediction = 1.1

    for i in 0...coefficients.count - 1 {

        prediction += coefficients[i] * (pow(x,Double(i)));

  }

    return prediction;

}


/*-------------------------------Algorithm-------------------------------*/
public func polynomialFit(samples: Int, values: [[Double]], order: Int) -> [Double] {
    
    var xMatrix: [[Double]] = [];
    
    let yMatrix = transpose(Matrix(values));
    
    print("samples: \(samples)")
    
    print("yMatrix size: (\(yMatrix.rows), \(yMatrix.cols))")

    for i in 0...samples - 1 {

        var temp: [Double] = [];

        for j in 0...order  {
            
            let powTemp: Double = pow(Double(i),Double(order - j));
            
            temp.append(powTemp);

        }

        xMatrix.append(temp);

    }

    let xMatrixT = transpose(Matrix(xMatrix));
    
    print("xMatrix size: (\(Matrix(xMatrix).rows), \(Matrix(xMatrix).cols))")
    print("xMatrixT size: (\(xMatrixT.rows), \(xMatrixT.cols))")

    let dot1 = dotProduct(A: xMatrixT, B: Matrix(xMatrix));
    let dot2 = dotProduct(A: xMatrixT, B: yMatrix);
    
    let dotInv = inv(dot1);
    
    
    print("dot1 size: (\(dot1.rows), \(dot1.cols))")
    print("dot2 size: (\(dot2.rows), \(dot2.cols))")
    
    print("dotInv size: (\(dotInv.rows), \(dotInv.cols))")

    let Matcoefficients = dotProduct(A: dotInv, B: dot2);
    
    var coeffs: [Double] = [];
    for i in 0...Matcoefficients.rows - 1 {
        coeffs.append(Matcoefficients[i]);
    }
    return coeffs;

}


func AlgHRandLeads(ECG_data: [[Double]]) -> (Double, Bool, [Double]) {
    //init return vars
    var heartRate = 0.1;
    var leadsFlipped = false;

    //getting the length of the array
    let t = ECG_data[0].count;

    //fitting the data and detrending it
//    let pol_order = 7;
//    let coeffs = polynomialFit(samples: t, values: ECG_data, order: pol_order);
//
//    var f_y: [Double] = [];
//    for i in 0...1000-1 {
//        let newVal = predict(x: ECG_data[0][i], coefficients: coeffs);
//
//        f_y.append(newVal);
//    }
//
//    let ECG_detrend: [Double] = ECG_data[0] - f_y;
    let ECG_detrend: [Double] = ECG_data[0];

    //Find local maxima which corresponds to top of the QRS complex
//    var highest_values : [Double] = []
//    var highest_index : [Double] = []
//    for i in 0...ECG_detrend.count - 1 {
//        let max_val = max(ECG_detrend)
//        let mean_val = calculateMean(array: ECG_detrend)
//
//        if (ECG_detrend[i] >= (max_val + mean_val)/2) {
//            highest_values.append(ECG_detrend[i])
//            highest_index.append(Double(i))
//        }
//
//    }
    
//    //Find local minima which corresponds to top of the QRS complex if flipped
//    let modified_detrend = -ECG_detrend;
//
//    var lowest_values : [Double] = []
//    var lowest_index : [Double] = []
//    for i in 0...modified_detrend.count - 1 {
//        let max_val = max(modified_detrend)
//        let mean_val = calculateMean(array: modified_detrend)
//
//        if (modified_detrend[i] >= (max_val + mean_val)/2) {
//            lowest_values.append(ECG_detrend[i])
//            lowest_index.append(Double(i))
//        }
//
//    }
    
    //FOR CHECKOFF 2 SINCE BLUETOOTH BROKE
    //check if leads flipped
    var highest_values : [Double] = []
    var highest_index : [Double] = []
    
    var modified_detrend = ECG_detrend;
    let max_val = max(modified_detrend)
    let min_val = min(modified_detrend)
    let mean_val = calculateMean(array: modified_detrend)
    
    //check if the leads are flipped
    var integral = 0
    for i in 0...modified_detrend.count - 1 {
        integral += modified_detrend[i];
    }
    
    if (integral < mean_val) {
        leadsFlipped = true;
    } else {
        leadsFlipped = false;
    }
    
    //flip the data so that you can still calculate heart rate even if the leads are flipped
//    if (leadsFlipped == true) {
//        modified_detrend = -ECG_detrend
//    }
    
//    var inc = 1
//    while (inc < modified_detrend.count) {
//        if (modified_detrend[inc] >= (max_val * 0.8)) {
//            highest_values.append(modified_detrend[inc])
//            highest_index.append(Double(inc))
//
//            if (inc < modified_detrend.count - 1 - 20) {
//                inc += 20
//            } else {
//                inc = 999
//            }
//        }
//        inc += 1
//    }
    
    var inc = 1
    var count = 0
    var zeroNeighborhood = false;
    while (inc < modified_detrend.count) {
        if (modified_detrend[inc] >= (max_val * 0.8) && zeroNeighborhood == false) {
            zeroNeighborhood = true;
            count += 1;
            
        } else if (modified_detrend[inc] < (max_val * 0.8)){
            zeroNeighborhood = false;
        }
        inc += 1
    }
    
    //calcualte heart rate
//    heartRate = Double(highest_values.count) * 6.0;
    heartRate = Double(count) * 16.0;
    print(heartRate);

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
//        heartRate = Double(highest_values.count) * 6.0;
//    }
    
//    print("r peaks count: \(highest_values.count)")
//    print("heart rate: \(heartRate)")
//    print("leads: \(leadsFlipped)")

    return (heartRate, leadsFlipped, ECG_detrend)
}
