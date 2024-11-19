//
//  ChatGPTsList.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/25.
//

import SwiftUI

struct ChatGPTsList: View {
    @EnvironmentObject var modelData: ModelData
    @State private var errorMessage: String?
    
    var body: some View {
        NavigationSplitView {
            if modelData.chatGPTs.isEmpty {
                Text(errorMessage ?? "No ChatGPT configurations available.")
                    .foregroundColor(.red)
            } else {
                List(modelData.chatGPTs) { chatGPT in
                    NavigationLink(chatGPT.id) {
                        ChatGPTsDetail(chatGPT: chatGPT)
                    }
                }
                .navigationTitle("Switch GPT")
            }
        } detail: {
            Text("Select a GPT")
        }
        .navigationTitle("ChatGPTS")
        .onAppear {
            if modelData.chatGPTs.isEmpty {
                errorMessage = "Failed to load ChatGPT configurations."
            }
        }
    }
}

#Preview {
    ChatGPTsList().environmentObject(ModelData())
}
