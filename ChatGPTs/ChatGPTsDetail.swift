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
        return SimpleWebView(chatGPT: chatGPT)
    }
}

#Preview {
    let modelData = ModelData()
    ChatGPTsDetail(chatGPT: modelData.chatGPTs[0])
}
