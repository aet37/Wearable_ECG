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
//        self.lineChartView.leftAxis.axisMinimum = 0
//        self.lineChartView.rightAxis.axisMinimum = 0
        
        initChart()
   
        // Notification to call chart updater every time something is recived in queue
        NotificationCenter.default.addObserver(self, selector: #selector(self.updateChartValues), name: Notification.Name("push"), object: nil)
        
//        _ = Timer.scheduledTimer(timeInterval: 0.01, target:self, selector: #selector(self.updateChartValues), userInfo: nil, repeats: true)
        
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
    
    //Global Variables for the EKG Algorithm and Graph
    var addpoint = 0
    var HR: Double = 1.1
    var leads = false
    var polydata: [Double] = []
    var currVal = 0.0
    var arr = [[Int]](repeating: [Int](repeating: 0, count: 5), count: 5)
    var ECGdata = [[Double]](repeating: [Double](repeating: 0, count: 1000), count: 1);
    
    var firstTime = true
    var newValues: [Double] = [];
    var overwriteSignal: Double = 0;
    var overwriteCounter: Int = 50;
    
    var testIncBool = true;
    var testInc = 1000;
    
    
    //var globalFilterTime = 0.0
    
    // Listen for pushed() notification
    // @objc func updateChartValues(notification: NSNotification){
    @objc func updateChartValues(){
        if(EKGQueue.isEmpty() == false) {
            newValues.append(Double(EKGQueue.pop()))
            overwriteSignal += 1;
            if(newValues.count == 1000) {
                firstTime = false;
            }
        }
        
        //importing test data
//        var testECGdata : [[Double]] = []
//        testECGdata = getCSVData(dataFile: "/Users/lsantella/Documents/GitHub/ECGv1/ECGv1/ds1.csv");
//
//        for i in testInc - 1000...testInc - 1 {
//            if (testInc == 2000) {
//                ECGdata[0][i - 1000] = (testECGdata[i][0])
//            } else {
//                ECGdata[0][i] = (testECGdata[i][0])
//            }
//        }
//        if (testIncBool == true) {
//            testInc = 2000
//            testIncBool = false
//        } else {
//            testInc = 1000
//            testIncBool = true
//        }
//        (HR, leads, polydata) = AlgHRandLeads(ECG_data: ECGdata);
        
        
        //NEWVAL is added to array of 1000
        //once arrays length is 1000 in if statement
        //execute stuff below
        
        //if newValues gets 1000 new values from the EKG Queue
        if (newValues.count == 1000) {

            //bound the data around 0 and scaled between -5 and 5
            let mean = calculateMean(array: newValues)
            for i in 0...1000 - 1 {
                ECGdata[0][i] = 5*((newValues[i] - mean)/(pow(2,10) - 1))
            }

            //place data into ECG algoritm for HR and Lead Status
            (HR, leads, polydata) = AlgHRandLeads(ECG_data: ECGdata);

            //update the HR
            button2.setTitle(String(HR), for: .normal)

            //update the Lead Status
            if (leads == false) {
                button3.setTitle("Ok", for: .normal)
            } else {
                button3.setTitle("Flipped", for: .normal)
            }
            
            //resetting newValues array
            newValues = [];
        }

        //when 50 new values are added overwrite the next set of 50
        if (overwriteSignal == 50 && !firstTime) {
            overwriteSignal = 0;

            for i in overwriteCounter - 50...overwriteCounter-1 {
                valuesArr[i].x = Double(i)
                valuesArr[i].y = Double(polydata[i])
            }

            if (overwriteCounter == 1000) {
                overwriteCounter = 50;
            } else {
                overwriteCounter += 50;
            }
        }

        
            
            
            //filtering
//        valuesArr[999].y = (currVal * 0.2) + (0.8 * valuesArr[999].y)
        
            
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        set1.drawValuesEnabled = false
        set1.lineWidth = 3.0
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
    }

    @objc func initChart(){
        
        for i in 0..<numVal {
            valuesArr[i] = ChartDataEntry(x: Double(i), y: Double(0))
        }
        
    
        let set1 = LineChartDataSet(entries: valuesArr, label: "EKG")
        set1.drawCirclesEnabled = false
        set1.drawValuesEnabled = false
        set1.lineWidth = 3.0
        
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
