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
//

import UIKit
import CoreBluetooth
import Charts
import Numerics
import Foundation
import Accelerate
import NVDSP


class ViewController: UIViewController, CBPeripheralDelegate, CBCentralManagerDelegate {
    
    /*-------------------------------Bluetooth-------------------------------*/
    private var centralManager: CBCentralManager!
    private var peripheral: CBPeripheral!
    private var arduCh: CBCharacteristic?

    
    // For reciving values from BT
    var b1 = UInt16(0)
    var b2 = UInt16(0)
    var recieved = UInt16(0)
    
    var EKGQueue = BTQueue() //devliery queue
    
    /*-------------------------------Bluetooth Start Transmission Switche-------------------------------*/
    @IBOutlet weak var startSwitch: UISwitch!
    
    // Send transmission state to Arduino
    private func toggleTransmission(withCharachteristic charachteristic: CBCharacteristic) {
        if peripheral != nil {
            if startSwitch.isOn {
                peripheral.writeValue(Data([8]), for: charachteristic, type: .withoutResponse)
                print("Start Sending")
            } else {
                peripheral.writeValue(Data([0]), for: charachteristic, type: .withoutResponse)
                print("Stop Sending")
            }
        } else {
            print("Problem with BT connection while requesting Send.")
        }
    }
    
    // Action on button
    @IBAction func toggleTransmission(_ sender: Any) {
        // Send correct state via Bluetooth
        toggleTransmission(withCharachteristic: arduCh!)
    }
    
    
    /*-------------------------------Graph-------------------------------*/
    @IBOutlet weak var lineChartView: LineChartView!
    
    
    /*-------------------------------Buttons-------------------------------*/
    //heart rate value
    public let button2: UIButton = {
       let button2 = UIButton()
        button2.backgroundColor = .systemBlue
        button2.setTitle("72", for: .normal)
        button2.setTitleColor(.white, for: .normal)
        button2.layer.cornerRadius = 20
        button2.layer.masksToBounds = true
       return button2
    }()
    
    //Lead Status value
    public let button3: UIButton = {
        let button3 = UIButton()
        button3.backgroundColor = .systemBlue
        button3.setTitle("OK", for: .normal)
        button3.setTitleColor(.white, for: .normal)
        button3.layer.cornerRadius = 20
        button3.layer.masksToBounds = true
        return button3
    }()
    
//    @IBOutlet weak var Addtest: UILabel!
    
    /*-------------------------------Main-------------------------------*/
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // Bluetooth Central manager
        centralManager = CBCentralManager(delegate: self, queue: nil)
        
        //view.backgroundColor = .systemGray
        //imageView.frame = CGRect(x: 0, y: 0, width: 300, height: 300)
        //imageView.center = view.center
        
        
        
        view.addSubview(button2)
        view.addSubview(button3)
        //self.lineChartView.leftAxis.axisMinimum = 0
        //self.lineChartView.rightAxis.axisMinimum = 0
        
        initChart()
   
        // Notification to call chart updater every time something is recived in queue
        //NotificationCenter.default.addObserver(self, selector: #selector(self.updateChartValues), name: Notification.Name("push"), object: nil)
        _ = Timer.scheduledTimer(timeInterval: 0.01, target:self, selector: #selector(self.updateChartValues), userInfo: nil, repeats: true)
    }
    
    /*-------------------------------Button Layout-------------------------------*/
    override func viewDidLayoutSubviews() {
        super.viewDidLayoutSubviews()
        button2.frame = CGRect(
            x: 57,
            y: 185,
            width: 60,
            height: 55
        )
        button3.frame = CGRect(
            x: view.frame.size.width - 117,
            y: 185,
            width: 60,
            height: 55
        )
        
    }
    
    
    
    
    /*-------------------------------Chart Values-------------------------------*/
    
    let numVal = 1000
    
    var valuesArr = Array<ChartDataEntry>(repeating: ChartDataEntry(x: Double(0), y: Double(0)), count: 1000)
    
    var currVal = 0.0
    var testECGdata : [[Double]] = []
    var currDataIndex = 1000
    //var globalFilterTime = 0.0
    
    // Listen for pushed() notification
    
    
    //new chart updater
   // @objc func updateChartValues(notification: NSNotification){
    @objc func updateChartValues(){
       // if(EKGQueue.isEmpty() == false){
          //  var newVal = Double(EKGQueue.pop())
                        
            // newVal = continuousFilter(newVal: newVal, oldVal: valuesArr[0])
           // newVal = continuousFilter(arr: newVal)
            var newVal = testECGdata[0][currDataIndex]
        
            valuesArr.removeFirst()
            valuesArr.append(ChartDataEntry(x: Double(999), y: Double(newVal)))
            
            //let testECGdata = getCSVData(dataFile: "/Users/lsantella/Documents/GitHub/ECGv1/ECGv1/data1.csv");
            
//            let coeffs = polynomialFit(samples: testECGdata[0].count, values: testECGdata, order: 9);
//            print(coeffs);
            //let (HR, leads, polydata) = AlgHRandLeads(ECG_data: testECGdata);
            
           // button2.setTitle(String(HR), for: .normal)
            
           // button3.setTitle(String(leads), for: .normal)
            
           /* for i in 0...polydata.count {
                valuesArr[i].x = Double(i)
                valuesArr[i].y = Double(polydata[i])
            }*/
            
            //calls filter
            //valuesArr = continuousFilter(arr: valuesArr)
            
            for i in 0..<numVal {
                valuesArr[i].x = Double(i)
                valuesArr[i].y = Double(valuesArr[i].y)
            }
            
            //filtering
            valuesArr[999].y = (currVal * 0.2) + (0.8 * valuesArr[999].y)
            currDataIndex += 1
            /*
            var currVal = valuesArr[0].y
            for i in 0...999{
                currVal = (currVal * 0.2) + (0.8 * valuesArr[i].y)
                valuesArr[i].y = currVal
            }*/
            
        //}
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        set1.drawValuesEnabled = false
        set1.lineWidth = 3.0
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
    }
    /*
    @objc func updateChartValues(arr: Array<ChartDataEntry>){
        if(EKGQueue.isEmpty() == false){
            var newVal = Double(EKGQueue.pop())
                        
            // newVal = continuousFilter(newVal: newVal, oldVal: valuesArr[0])
           // newVal = continuousFilter(arr: newVal)
            
            valuesArr.removeFirst()
            valuesArr.append(ChartDataEntry(x: Double(999), y: Double(newVal)))
            
            valuesArr = continuousFilter(arr: valuesArr)
            
            //valuesArr = arr
            for i in 0..<numVal {
                valuesArr[i].x = Double(i)
                valuesArr[i].y = Double(valuesArr[i].y)
            }
            
            
            
        }
        for i in 0...999{
            if(i<100){
                valuesArr[i].y = Double(50)
            }
            if(i>=100 && i<200){
                valuesArr[i].y = Double(0)
            }
            if(i>=200 && i<300){
                valuesArr[i].y = Double(50)
            }
            if(i>=300 && i<400){
                valuesArr[i].y = Double(0)
            }
            if(i>=400 && i<500){
                valuesArr[i].y = Double(50)
            }
            if(i>=500 && i<600){
                valuesArr[i].y = Double(0)
            }
            if(i>=600 && i<700){
                valuesArr[i].y = Double(50)
            }
            if(i>=700 && i<800){
                valuesArr[i].y = Double(0)
            }
            if(i>=800 && i<900){
                valuesArr[i].y = Double(50)
            }
            if(i>=900 && i<1000){
                valuesArr[i].y = Double(0)
            }
            
        }
        
        valuesArr = continuousFilter(arr: valuesArr)
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        set1.drawValuesEnabled = false
        set1.lineWidth = 3.0
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
    }
 */
    
    @objc func initChart(){
        /*
         for i in 0..<numVal {
            valuesArr[i] = ChartDataEntry(x: Double(i), y: Double(0))
            
        }
   
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        let data = LineChartData(dataSet: set1)
       
        self.lineChartView.data = data
        
        */
        
        
        testECGdata = getCSVData(dataFile: "/Users/bobbyrouse/Downloads/Wearable_ECG/ECGv1/ECGv1/data1.csv");
        for i in 0..<numVal {
            valuesArr[i] = ChartDataEntry(x: Double(i), y: Double(testECGdata[0][i]))
        }
        /*
        for i in 0...999{
            if(i<100){
                valuesArr[i].y = Double(50)
            }
            if(i>=100 && i<200){
                valuesArr[i].y = Double(0)
            }
            if(i>=200 && i<300){
                valuesArr[i].y = Double(50)
            }
            if(i>=300 && i<400){
                valuesArr[i].y = Double(0)
            }
            if(i>=400 && i<500){
                valuesArr[i].y = Double(50)
            }
            if(i>=500 && i<600){
                valuesArr[i].y = Double(0)
            }
            if(i>=600 && i<700){
                valuesArr[i].y = Double(50)
            }
            if(i>=700 && i<800){
                valuesArr[i].y = Double(0)
            }
            if(i>=800 && i<900){
                valuesArr[i].y = Double(50)
            }
            if(i>=900 && i<1000){
                valuesArr[i].y = Double(0)
            }
            
        }*/
        
        currVal = valuesArr[0].y
        for i in 0...999{
            currVal = (currVal * 0.2) + (0.8 * valuesArr[i].y)
            valuesArr[i].y = currVal
        }
        
        //valuesArr = continuousFilter(arr: valuesArr)
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
        
    }
    
    func continuousFilter(arr: Array<ChartDataEntry>) -> Array<ChartDataEntry>{
        //convert to y-only array for filtering
        var yArr = Array<Float>(repeating: 0.0, count: 1000)
        
        for i in 0...999 {
            yArr[i] = Float(arr[i].y)
        }
        
        //calls NVDSP library
        let bandpass : NVBandpassFilter = NVBandpassFilter(samplingRate: 115.0)
        bandpass.centerFrequency = 19.75
        bandpass.q = 0.10101010101
        bandpass.filterData(&yArr, numFrames: 1000, numChannels: 1)
        
        //convert back values
        
        for i in 0...999 {
            arr[i].y = Double(yArr[i])
        }
        
        
        return arr
    }
    
    /*-------------------------------Bluetooth-------------------------------*/
    
    // Start Scanning for BT devices
    func centralManagerDidUpdateState(_ central: CBCentralManager) {
        print("Central state update")
            if central.state != .poweredOn {
                print("Central is not powered on")
            } else {
                print("Central scanning for", ArduPeripheral.ArduUUID);
                centralManager.scanForPeripherals(withServices: nil, options: [CBCentralManagerScanOptionAllowDuplicatesKey : false])
            }
        }

    // Handles the result of the scan
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {

        // We've found it so stop scan
        if peripheral.identifier.uuidString == ArduPeripheral.ArduUUID_str {
            self.centralManager.stopScan()
            
            // Copy the peripheral instance
            self.peripheral = peripheral
            self.peripheral.delegate = self
            
            // Connect!
            self.centralManager.connect(self.peripheral, options: nil)
        }
    }
    
    // The handler if we do connect succesfully
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        if peripheral == self.peripheral {
            print("Connected to Arduino")
            peripheral.discoverServices(nil) //[ArduPeripheral.Serv1UUID]
        }
    }
    
    // Handles discovery event
   func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
       if let services = peripheral.services {
           for service in services {
               if service.uuid == ArduPeripheral.Serv1UUID {
                   print("Arduino service found")
                   
                   //Now kick off discovery of characteristics
                   peripheral.discoverCharacteristics(nil, for: service)
                   return
               }
           }
       }
   }

    // Handling discovery of characteristics
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        if let characteristics = service.characteristics {
            for characteristic in characteristics {
                if characteristic.uuid == ArduPeripheral.Char1UUUID {
                    print("Arduino characteristic found")
                    arduCh = characteristic
                    peripheral.setNotifyValue(true, for: characteristic)
                    
                    // Enable switch
                    startSwitch.isEnabled = true
                }
            }
        }
    }
    
    //
    /** Handle Vaue recived from Ardu  **/
    //
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        
        for i in 0..<(characteristic.value!.count)/2 {
            
            // Get value recived as 2 seperate bytes
            b1 = UInt16(characteristic.value![i*2])
            b2 = UInt16(characteristic.value![(i*2) + 1])
            
            // Insert b1 and b2 in recieved integer
            recieved = (b1 << 8) | b2
            
            // Push the recived value onto the queue
            EKGQueue.push(val: recieved, periph: peripheral, charach: characteristic)
            }
        }

    // Handle Disconnect
    func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
        if peripheral == self.peripheral {
            print("Disconnected")
            
            // Disable the switch
            startSwitch.isEnabled = false
        }
        
        // Don't write to unwanted place
        self.peripheral = nil
        
        // Start Scanning again
        print("Central scanning for", ArduPeripheral.ArduUUID);
        centralManager.scanForPeripherals(withServices: nil, options: [CBCentralManagerScanOptionAllowDuplicatesKey : false])
    }
    
}
