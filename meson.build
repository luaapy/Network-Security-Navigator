project('nsn', 'c',
  version: '1.0.0',
  license: 'MIT',
  default_options: ['c_std=c11', 'optimization=2']
)

# Dependencies
openssl_dep = dependency('openssl', required: true)
pcap_dep = dependency('pcap', required: true)
threads_dep = dependency('threads')

# Include directories
inc = include_directories('Include')

# Core library source
nsn_sources = [
  'Nsn/nsn.c',
  'Nsn/ceval.c',
  'Nsn/nsn_memory.c',
  'Nsn/nsn_state.c',
  'Objects/object.c',
  'Objects/intobject.c',
  'Objects/dictobject.c',
  'Parser/lexer.c',
  'Parser/parser.c'
]

# Build the main executable
executable('nsn',
  'Programs/nsn.c',
  sources: nsn_sources,
  include_directories: inc,
  dependencies: [openssl_dep, pcap_dep, threads_dep],
  install: true
)
