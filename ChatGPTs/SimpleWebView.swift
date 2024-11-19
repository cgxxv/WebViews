//
//  SimpleWebView.swift
//  ChatGPTs
//
//  Created by cgxxv on 2024/10/23.
//

import SwiftUI
import WebKit

struct SimpleWebView: NSViewRepresentable {
    var chatGPT: ChatGPT

    func makeNSView(context: Context) -> WKWebView {
        let dataStore = WKWebsiteDataStore.default()

        let preference = WKWebpagePreferences()
        preference.preferredContentMode = .desktop
        preference.allowsContentJavaScript = true

        let configuration = WKWebViewConfiguration()
        configuration.defaultWebpagePreferences = preference
        configuration.websiteDataStore = dataStore

        let webView = WKWebView(frame: .zero, configuration: configuration)

        webView.uiDelegate = context.coordinator as? WKUIDelegate

        let request = URLRequest(url: chatGPT.url)
        webView.load(request)

        return webView
    }

    func updateNSView(_ nsView: WKWebView, context: Context) {
        let request = URLRequest(url: chatGPT.url)
        nsView.load(request)
    }

    func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }

    class Coordinator: NSObject, WKNavigationDelegate {
        var parent: SimpleWebView

        init(_ parent: SimpleWebView) {
            self.parent = parent
        }

        // implement file upload dialog process
        func webView(_ webView: WKWebView, runOpenPanelWithFileChooserParameters parameters: WKOpenPanelParameters, initiatedByFrame frame: WKFrameInfo, completionHandler: @escaping ([URL]?) -> Void) {
            let openPanel = NSOpenPanel()
            openPanel.allowsMultipleSelection = true
            openPanel.canChooseFiles = true
            openPanel.canChooseDirectories = false

            openPanel.begin { response in
                if response == .OK, let url = openPanel.urls.first {
                    completionHandler([url])
                } else {
                    completionHandler(nil)
                }
            }
        }
    }
}
