//
//  BTQueue.swift
//  ECGv1
//
//  Created by Andrew Toader on 23.02.22 .
//

import Foundation
import CoreBluetooth

class BTQueue {
    
    // The queue to store the values recived by Bluetooth
    var valuesArr: [UInt16] = []
    
    // Function to add to array (ONLY BLUETOOTH SHOULD ADD)
    func push(val: UInt16, periph: CBPeripheral, charach: CBCharacteristic) {
        
        // Make sure the phone memory does not overfill if app is not handling data
        if(valuesArr.count >= 1200) {
            print("Queue Limit Reached")    // Debug log
            
            // Disable Send to BT
            periph.writeValue(Data([0]), for: charach, type: .withoutResponse)
            
            // Empty the queue
            valuesArr = []
            
        } else {
            // Add value to queue
            valuesArr.append(val)
            
            print("Recived", val)   // Debug log
            //print(valuesArr.count)
        }
    }
    
    // Function to remove to array
    func pop() -> UInt16 {
        
        // Get the first item off of queue
        let to_return = valuesArr[0]
        
        // Remove the item from the queue
        valuesArr.remove(at: 0)
        
        // Return the popped value
        return to_return
    }
}
