//
//  Peripheral.swift
//  BTTest
//
//  Created by Andrew Toader on 05.02.22 .
//

import UIKit
import CoreBluetooth

    class ArduPeripheral: NSObject {

        // UUID of Arduino
//        public static let ArduUUID_str = "11E311C4-1914-F393-E5A7-ECF0469C89EB"
        public static let ArduUUID_str = "19A57917-F2D9-CAA0-6C3E-ECDBE5BA4C0F"
        public static let Serv1UUID_str = "FFE0" //"00001800-0000-1000-8000-00805F9B34FB"
        public static let Char1UUID_str = "FFE1" //"00002A03-0000-1000-8000-00805F9B34FB"
        
        public static let ArduUUID = CBUUID.init(string: ArduUUID_str)
        public static let Serv1UUID = CBUUID.init(string: Serv1UUID_str)
        public static let Char1UUUID = CBUUID.init(string: Char1UUID_str)
    }
