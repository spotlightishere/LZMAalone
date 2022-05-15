from setuptools import setup, Extension

# Needed across all files.
include_dirs = [
    "src/lzma/C",
    "src/lzma/CPP/Common",
    "src/lzma/CPP/Windows",
    "src/lzma/CPP/7zip/Common",
    "src/lzma/CPP/7zip/Compress",
]

sdk_sources = [
    "src/lzma/C/Alloc.c",
    "src/lzma/C/CpuArch.c",
    "src/lzma/C/Delta.c",
    "src/lzma/C/LzFind.c",
    "src/lzma/C/LzmaDec.c",
    "src/lzma/CPP/7zip/Common/StreamUtils.cpp",
    "src/lzma/CPP/7zip/Common/StreamObjects.cpp",
    "src/lzma/CPP/7zip/Compress/LzmaDecoder.cpp"
]

module_sources = [
    "src/lzmaalone/LZMAalone_module.cpp",
    "src/lzmaalone/LZMAalone_object.cpp",
]

sources = module_sources
sources += sdk_sources

# Let's not bother with threading.
define_macros = [("_7ZIP_ST", 1)]

lzma_alone = Extension(
    "LZMAalone", sources, include_dirs=include_dirs, define_macros=define_macros
)

setup(
    name="LZMAalone",
    version="1.0",
    description="The decompression logic from LZMA Alone, packaged with Python bindings",
    ext_modules=[lzma_alone],
)
