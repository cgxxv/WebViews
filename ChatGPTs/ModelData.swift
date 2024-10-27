//
//  ModelData.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/25.
//

import Foundation
import SwiftUI

struct ChatGPT: Codable, Hashable, Identifiable {
    var id: String
    var url: URL
}

enum ChatGPTsError: LocalizedError {
//    case invalidUUID(String)
    case invalidURL(String)

    var errorDescription: String? {
        switch self {
//        case .invalidUUID(let message): return message
        case .invalidURL(let message): return message
        }
    }
}

class ModelData: ObservableObject {
    @Published var chatGPTs: [ChatGPT]

    init() {
        if let loadedChatGPTs: [ChatGPT] = load() {
            self.chatGPTs = loadedChatGPTs
        } else {
            self.chatGPTs = []
            debugPrint("Failed to load ChatGPTs config")
        }
    }
}

extension ModelData {
    func addChatGPT(name: String, url: String) throws {
//        guard let uuid = UUID(uuidString: uuid) else {
//            throw ChatGPTsError.invalidUUID("Invalid UUID: \(uuid)")
//        }
        guard let url = URL(string: url) else {
            throw ChatGPTsError.invalidURL("Invalid URL: \(url)")
        }
        let charGPT = ChatGPT(id: name, url: url)
        chatGPTs.append(charGPT)
        saveChatGPTs()
    }
    
    private func saveChatGPTs() {
        let fileURL = getCacheFileURL()

        do {
            let data = try JSONEncoder().encode(chatGPTs)
            try data.write(to: fileURL)
            debugPrint("Successfully saved to \(fileURL.path)")
        } catch {
            debugPrint("Failed to save ChatGPTs: \(error)")
        }
    }
}

private func load<T: Decodable>() -> [T]? {
    let fileURL = getCacheFileURL()

    do {
        let data = try Data(contentsOf: fileURL)
        let chatGPTs = try JSONDecoder().decode([T].self, from: data)
        return chatGPTs
    } catch {
        debugPrint("Failed to load ChatGPTs config: \(error)")
        return nil
    }
}

private func getCacheFileURL() -> URL {
    let cacheDirectory = FileManager.default.urls(for: .cachesDirectory, in: .userDomainMask).first!
    let configFilepath = cacheDirectory.appendingPathComponent("config.json")

    if !FileManager.default.fileExists(atPath: configFilepath.path) {
        FileManager.default.createFile(atPath: configFilepath.path, contents: nil, attributes: nil)
    }
    
    return configFilepath
}
