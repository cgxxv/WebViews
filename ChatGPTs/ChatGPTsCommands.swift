//
//  ChatGPTsCommands.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/25.
//

import SwiftUI

struct ChatGPTsCommands: Commands {
    var body: some Commands {
        SidebarCommands()
        
        CommandMenu("Switch GPT") {
            Button {
                print("chatgpt clicked")
            } label: {
                Text("ChatGPT")
            }
            Button {
                print("doubao clicked")
            } label: {
                Text("Doubao")
            }
        }
    }
}
