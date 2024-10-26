//
//  ChatGPTsList.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/25.
//

import SwiftUI

struct ChatGPTsList: View {
    @EnvironmentObject var modelData: ModelData

    var body: some View {
        NavigationSplitView {
            List(modelData.chatGPTs) { chatGPT in
                NavigationLink(chatGPT.name) {
                    ChatGPTsDetail(chatGPT: chatGPT)
                }
            }
            .navigationTitle("Switch GPT")
        } detail: {
            Text("Select a GPT")
        }
        .navigationTitle("ChatGPTS")
    }
}

#Preview {
    ChatGPTsList().environmentObject(ModelData())
}
