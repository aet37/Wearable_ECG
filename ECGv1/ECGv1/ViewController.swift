//
//  ViewController.swift
//  ECGv1
//
//  Created by Bobby Rouse on 2/22/22.
//  Currently simulating for iphone 12 pro
//
//
// TOADER/LUCIO: lines 87-92 is where you should connect the data coming in to be displayed
// you can change the graphs refresh rate on line 51, it's currently set for 250hz

import UIKit
import Charts

class ViewController: UIViewController {

    /*-------------------------------Graph-------------------------------*/
    @IBOutlet weak var lineChartView: LineChartView!
    
    
    /*-------------------------------Buttons-------------------------------*/
    //heart rate value
    public let button2: UIButton = {
       let button2 = UIButton()
        button2.backgroundColor = .gray
        button2.setTitle("72", for: .normal)
        button2.setTitleColor(.black, for: .normal)
       return button2
    }()
    
    //Lead Status value
    public let button3: UIButton = {
       let button3 = UIButton()
        button3.backgroundColor = .gray
        button3.setTitle("OK", for: .normal)
        button3.setTitleColor(.black, for: .normal)
       return button3
    }()
    
    
    /*-------------------------------Main-------------------------------*/
    override func viewDidLoad() {
        super.viewDidLoad()
        
        view.addSubview(button2)
        view.addSubview(button3)
        
        setChartValues()
        
        //currently set for 250 hz, timeInterval is in ms
        _ = Timer.scheduledTimer(timeInterval: 0.04, target:self, selector: #selector(self.setChartValues), userInfo: nil, repeats: true)
    }
    
    /*-------------------------------Button Layout-------------------------------*/
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        button2.frame = CGRect(
            x: 57,
            y: 225,
            width: 60,
            height: 55
        )
        button3.frame = CGRect(
            x: view.frame.size.width - 117,
            y: 225,
            width: 60,
            height: 55
        )
        
    }
    
    
    /*-------------------------------Chart Values-------------------------------*/
    
    var valuesArr = Array<ChartDataEntry>(repeating: ChartDataEntry(x: Double(0), y: Double(0)), count: 1200)
    
    @objc func setValues(){
        
        //This loop demonstrates functionality, comment out when you have our input connected
        for i in 0..<1200 {
            valuesArr[i] = ChartDataEntry(x: Double(i), y: Double(arc4random_uniform(UInt32(20)) + 3))
        }
        
        //This will add our data to the graph
        /*
        var newVal = /*NEWVALUE*/ //should be a number
        let first1 = valuesArr.removeFirst()
        valuesArr.append(ChartDataEntry(x: Double(1199), y: Double(newVal))
        */
        
    }
    
    @objc func setChartValues(){
        setValues()
        
        let set1 = LineChartDataSet(entries: valuesArr, label: "dataset 1")
        set1.drawCirclesEnabled = false
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
        
    }


}

