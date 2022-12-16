#include "Compression.h"

using  namespace std;

int main()
{
    vector<int> outputStream = CompressXML("Sample.xml");

    writeToFile_int("compressedSample.txt", outputStream);

    vector<string> decompressedVector = DecompressXML(outputStream);

    writeToFile_string("decompressedSample.txt", decompressedVector);

    return 0;
}
