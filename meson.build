
project('cosmoverse', 'cpp', default_options: ['cpp_std=c++20'])

inc = include_directories('include')
srcs = files()
foreach f : ['src']
  srcs += files(meson.project_source_root() / f / 'core' / 'config_env.cpp') # ensure at least one src
endforeach
# Fallback to glob if needed
srcs += files('src/core/plugin_loader.cpp')
lib = library('cosmoverse', srcs, include_directories: inc, install: true)
app = executable('cosmoverse', 'apps/cosmoverse.cpp', link_with: lib, include_directories: inc, install: true)
test('version', app, args: ['--json','version'])
