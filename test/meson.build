sup_test_sources = [
  'main.cpp',
]

sup_test_deps = [
  sup_dep,
  dependency('catch2-with-main'),
]

test_exe = executable('sup-test', sup_test_sources,
  dependencies: sup_test_deps,
  install: true,
)

test('Unit Tests', test_exe)