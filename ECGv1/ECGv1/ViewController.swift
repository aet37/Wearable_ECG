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
        
        // Bluetooth Central manager
        centralManager = CBCentralManager(delegate: self, queue: nil)
        
        //view.backgroundColor = .systemGray
        //imageView.frame = CGRect(x: 0, y: 0, width: 300, height: 300)
        //imageView.center = view.center
        
        view.addSubview(button2)
        view.addSubview(button3)
        
        initChart()
        
        // Notification to call chart updater every time something is recived in queue
        NotificationCenter.default.addObserver(self, selector: #selector(self.updateChartValues), name: Notification.Name("push"), object: nil)
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
    
    let numVal = 1000
    
    var valuesArr = Array<ChartDataEntry>(repeating: ChartDataEntry(x: Double(0), y: Double(0)), count: 1000)
    
    
    //var globalFilterTime = 0.0
    
    // Listen for pushed() notification
    
    
    //new chart updater
    @objc func updateChartValues(notification: NSNotification){
        if(EKGQueue.isEmpty() == false){
            var newVal = Double(EKGQueue.pop())
                        
            // newVal = continuousFilter(newVal: newVal, oldVal: valuesArr[0])
            //newVal = continuousFilter(newVal: newVal)
            
            valuesArr.removeFirst()
            valuesArr.append(ChartDataEntry(x: Double(1199), y: Double(newVal)))
            
            for i in 0..<numVal {
                valuesArr[i].x = Double(i)
                valuesArr[i].y = Double(valuesArr[i].y)
            }
            
        }
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
        let data = LineChartData(dataSet: set1)
        
        self.lineChartView.data = data
        
    }
    /*
    func continuousFilter(newVal: Double) -> Double{
        //increment time
        globalFilterTime += 1.0
        
        //inputs
        var xOld = (globalFilterTime + 1.0)/115.0
        var yOld = newVal
        var xNew = (globalFilterTime)/115.0
        var yNew = 0.0
        
        //note: x = dt * array position
        var dt = 1.0/115.0
        var cutoff = 50.0
        var alpha = dt / (dt + 1.0 / (Double.pi * 2 * cutoff))
        
        //lowpass
        yNew = xNew * alpha + (1 - alpha) * yOld
        
        //highpass
        yNew = alpha * (yNew + xOld - xNew)
        
        
        /*
        var xVal = 0.0
        var yVal = newVal
        var lowVal = xVal * alpha + (1 - alpha) * yVal
        var highVal = alpha * (yVal + xVal)
        */
        
        //returns double
        return yNew
    }
    */
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
