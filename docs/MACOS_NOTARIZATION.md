
# macOS Notarization
- Create an Apple Developer account.
- Build an unsigned .dmg via CPack (DragNDrop).
- Sign with Developer ID using `codesign --timestamp`.
- Notarize with `xcrun notarytool submit` and staple using `xcrun stapler staple`.
