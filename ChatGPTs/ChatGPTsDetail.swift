//
//  ChatGPTsDetail.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/26.
//

import SwiftUI

struct ChatGPTsDetail: View {
    let chatGPT: ChatGPT
    
    var body: some View {
        print("switch to \(chatGPT)")
        return SimpleWebView(chatGPT: chatGPT)
            .frame(width: 1024, height: 768)
    }
}

#Preview {
    let modelData = ModelData()
    ChatGPTsDetail(chatGPT: modelData.chatGPTs[0])
}
