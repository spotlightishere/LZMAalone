# LZMAAlone
The decompression logic from LZMA Alone, packaged with Python bindings.

This is necessary because 7-Zip does some magic for various LZMA files. It, quite frankly, is a hack all around.

## Usage
Don't, thank you!

If you feel like ignoring the above advice, it's really simple:
```python
decompressed = LZMAAlone.decompress(compressed)
```
