//
//  ViewController.swift
//  BTTest
//
//  Created by Andrew Toader on 05.02.22 .
//

import UIKit
import CoreBluetooth

class ViewController: UIViewController, CBPeripheralDelegate, CBCentralManagerDelegate {
    
    // Properties
    private var centralManager: CBCentralManager!
    private var peripheral: CBPeripheral!
    
    // Characteristics
    private var arduCh: CBCharacteristic?
    
    // Wrie to device function
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
    
    // Transmission switch
    @IBOutlet weak var startSwitch: UISwitch!
    @IBOutlet weak var Num0: UILabel!
    @IBOutlet weak var Num1: UILabel!
    @IBOutlet weak var Num2: UILabel!
    
    // When Switch state Changed
    @IBAction func toggleTransmissionState(_ sender: Any) {
        // Send correct state via Bluetooth
        toggleTransmission(withCharachteristic: arduCh!)
    }
    
    
    // Additional Setup
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        centralManager = CBCentralManager(delegate: self, queue: nil)
    }
    
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
    
    // Handle Vaue recived from Ardu
    func peripheral(_ peripheral: CBPeripheral, didUpdateValueFor characteristic: CBCharacteristic, error: Error?) {
        Num2.text = Num1.text
        Num1.text = Num0.text
        Num0.text = String(characteristic.value![0])
        
        print("Received", String(characteristic.value![0]))
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
