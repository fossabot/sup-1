inc = include_directories('include')
sup = library('sup', 'sup.cpp', include_directories: inc, install: true)
sup_dep = declare_dependency(link_with: sup, include_directories: inc)