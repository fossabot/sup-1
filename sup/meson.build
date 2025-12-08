inc = include_directories('include')
sup = library('sup', 'sup.cpp', include_directories: inc, install: true)
sup_dep = declare_dependency(link_with: sup, include_directories: inc)
install_headers('include/sup.hpp')

pkg = import('pkgconfig')
pkg.generate(libraries : [sup],
             subdirs : ['include'],
             version : '1.0',
             name : 'libsup',
             filebase : 'sup',
             description : 'Object trees and supervision for C++')
