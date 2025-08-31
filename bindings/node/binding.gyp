
{
  "targets": [{
    "target_name": "cosmoverse",
    "sources": ["src/addon.cc"],
    "include_dirs": ["<!@(node -p \"require('node-addon-api').include\")", "../../include"],
    "defines": ["NAPI_DISABLE_CPP_EXCEPTIONS"],
    "cflags!": [ "-fno-exceptions" ],
    "cflags_cc!": [ "-fno-exceptions" ],
    "libraries": ["-lcosmoverse"],
    "conditions": [
      ["OS=='win'", { "libraries": ["-lcosmoverse"] }]
    ]
  }]
}
