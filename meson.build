project('FiniteElementesIF', 'cpp',
        version : '1.0.0',
        default_options : ['warning_level=3', 'cpp_std=c++23'])


src = [
    'main.cpp',
    'parse_msh.cpp',
]

FiniteElementesIF = executable('FiniteElementesIF',
                                src,
                                install : false)

test('test', FiniteElementesIF)