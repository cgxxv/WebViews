//
//  ChatGPTsSettings.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/26.
//

import SwiftUI

struct ChatGPTsSettings: View {
    @EnvironmentObject var modelData: ModelData
    
    @State var name: String = ""
    @State var url: String = ""
//    @State var uuid: String = ""
    
    @State private var errorMessage: String?
    @State private var showErrorAlert = false
    
    private func showError(_ error: ChatGPTsError) {
        errorMessage = error.localizedDescription
        showErrorAlert = true
    }

    var body: some View {
        Form {
            TextField("Name", text: $name)
            TextField("URL", text: $url)
//            TextField("UUID", text: $uuid)
            
            Button("Add") {
                do {
                    try modelData.addChatGPT(name: name, url: url)
//                    uuid = ""
                    name = ""
                    url = ""
                } catch let error as ChatGPTsError {
                    showError(error)
                } catch {
                    print("Unexpected error: \(error)")
                }
            }
            .padding(.top, 20)
        }
        .frame(width: 300)
        .navigationTitle("ChatGPTs Settings")
        .padding(80)
        .alert(isPresented: $showErrorAlert) {
            Alert(title: Text("Error"),
                  message: Text(errorMessage ?? "An unknown error occured"),
                  dismissButton: .default(Text("Close")))
        }
    }
}

#Preview {
    ChatGPTsSettings()
        .environmentObject(ModelData())
}
