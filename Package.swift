
// swift-tools-version:5.7
import PackageDescription

let package = Package(
    name: "Cosmoverse",
    products: [
        .library(name: "Cosmoverse", targets: ["Cosmoverse"])
    ],
    targets: [
        .systemLibrary(name: "CCosmoverse", pkgConfig: "cosmoverse", providers: [
            .brew(["cosmoverse"]), .apt(["cosmoverse"])
        ]),
        .target(name: "Cosmoverse", dependencies: ["CCosmoverse"], path: "Sources/Cosmoverse")
    ]
)
