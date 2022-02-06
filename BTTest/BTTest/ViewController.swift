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
                print("Central scanning for", Peripheral.ArduUUID);
                centralManager.scanForPeripherals(withServices:[Peripheral.ArduUUID], options: [CBCentralManagerScanOptionAllowDuplicatesKey : true])
            }
        }

    // Handles the result of the scan
    func centralManager(_ central: CBCentralManager, didDiscover peripheral: CBPeripheral, advertisementData: [String : Any], rssi RSSI: NSNumber) {

        // We've found it so stop scan
        self.centralManager.stopScan()

        // Copy the peripheral instance
        self.peripheral = peripheral
        self.peripheral.delegate = self

        // Connect!
        self.centralManager.connect(self.peripheral, options: nil)

    }
    
    // The handler if we do connect succesfully
    func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
        if peripheral == self.peripheral {
            print("Connected to Arduino")
            peripheral.discoverServices([Peripheral.ArduUUID])
        }
    }
    
    // Handles discovery event
   func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
       if let services = peripheral.services {
           for service in services {
               if service.uuid == Peripheral.ArduUUID {
                   print("Arduino service found")
                   
                   //Now kick off discovery of characteristics
                   peripheral.discoverCharacteristics([Peripheral.ArduUUID], for: service)
                   return
               }
           }
       }
   }

    // Handling discovery of characteristics
    func peripheral(_ peripheral: CBPeripheral, didDiscoverCharacteristicsFor service: CBService, error: Error?) {
        if let characteristics = service.characteristics {
            for characteristic in characteristics {
                if characteristic.uuid == Peripheral.ArduUUID {
                    print("Arduino characteristic found")
                }
            }
        }
    }
}
