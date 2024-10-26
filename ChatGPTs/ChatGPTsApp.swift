//
//  ChatGPTsApp.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/20.
//

import SwiftUI

@main
struct ChatGPTsApp: App {
    @State private var modelData = ModelData()

    var body: some Scene {
        WindowGroup {
            ChatGPTsList()
                .environmentObject(modelData)
        }
//        .commandsRemoved()
        .commands {
            ChatGPTsCommands()
        }
        
        Settings {
            ChatGPTsSettings()
                .environmentObject(modelData)
        }
    }
}
