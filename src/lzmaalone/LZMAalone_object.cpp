// Derived from LzmaAlone.cpp.
#include "LZMAalone_object.h"

#include <Common.h>
#include <CpuArch.h>

#include <MyInitGuid.h>

#include <Alloc.h>
#include <NtCheck.h>

#include <IntToString.h>
#include <StringConvert.h>

#include <FileStreams.h>
#include <StreamUtils.h>
#include <StreamObjects.h>

#include <LzmaDecoder.h>

PyObject* decompress(PyObject* self, PyObject *args) {
	const char *inData = NULL;
	Py_ssize_t inLength = 0;
	if (!PyArg_ParseTuple(args, "s#", &inData, &inLength)) {
		return NULL;
	}

	// Create an input buffer from our provided bytes object.
	CMyComPtr<ISequentialInStream> inStream;
	Create_BufInStream_WithNewBuffer(inData, inLength, &inStream);

	// LZMA decoder!
	NCompress::NLzma::CDecoder *decoderSpec = new NCompress::NLzma::CDecoder;
	CMyComPtr<ICompressCoder> decoder = decoderSpec;
	decoderSpec->FinishStream = true;

	// Parse our header.
	const unsigned kPropertiesSize = 5;
	Byte header[kPropertiesSize + 8];

	if (ReadStream_FALSE(inStream, header, kPropertiesSize + 8) != S_OK) {
		PyErr_SetString(PyExc_ValueError, "Unable to read LZMA file header!");
		return NULL;
	}

	if (decoderSpec->SetDecoderProperties2(header, kPropertiesSize) != S_OK) {
		PyErr_SetString(PyExc_ValueError, "SetDecoderProperties error");
		return NULL;
	}
	
    // Determine our input size.
	UInt64 unpackSize = 0;
	for (int i = 0; i < 8; i++)
		unpackSize |= ((UInt64)header[kPropertiesSize + i]) << (8 * i);

	// Based on this, we'll create an output buffer with the same length to write to.
	Byte* outputBuf = (Byte *)malloc(unpackSize);
	if (outputBuf == NULL) {
		return PyErr_NoMemory();
	}

	CMyComPtr<ISequentialOutStream> outStream;
	CBufPtrSeqOutStream *outStreamSpec = new CBufPtrSeqOutStream;
	outStreamSpec->Init(outputBuf, unpackSize);
	outStream = outStreamSpec;


	HRESULT res = decoder->Code(inStream, outStream, NULL, &unpackSize, NULL);

	if (res != S_OK) {
		if (res == S_FALSE) {
			PyErr_SetString(PyExc_ValueError, "Decoding error");
		} else {
				PyErr_Format(PyExc_ValueError, "Decoding error: %d", res);
		}
		free(outputBuf);
		return NULL;
	}

	if (unpackSize != decoderSpec->GetOutputProcessedSize()) {
		PyErr_SetString(PyExc_ValueError, "incorrect uncompressed size in header");
		free(outputBuf);
		return NULL;
	}

	// TODO: close stream
	PyObject* result = PyBytes_FromStringAndSize((const char*)outputBuf, unpackSize);
	free(outputBuf);
	return result;
}