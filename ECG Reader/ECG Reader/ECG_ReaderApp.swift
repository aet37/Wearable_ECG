//
//  ECG_ReaderApp.swift
//  ECG Reader
//
//  Created by Andrew Toader on 02.02.22 .
//

import SwiftUI

@main
struct ECG_ReaderApp: App {
    let persistenceController = PersistenceController.shared

    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, persistenceController.container.viewContext)
        }
    }
}
