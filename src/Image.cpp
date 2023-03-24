#include "Image.h"
#include <string.h>
Image::~Image()
{

}

int Image::loadImage(const std::string& fileName)
{
	// For now only TGA is supported
	return loadTGA(fileName);
}

int Image::loadTGA(const std::string& fileName)
{
	TGAHEADER tgaHeader;
	// Holds bitwise flags for TGA file
	int tgaDesc = 0;

	std::cout << "Loading TGA: " << fileName.c_str() << std::endl;

	std::ifstream tgaFile(fileName, std::ios::in | std::ios::binary);

	if (!tgaFile.is_open())
	{
		std::cout << "Error opening " << fileName.c_str() << std::endl;
		return ERROR;
	}

	// Go to end of file to check TGA version
	tgaFile.seekg(0, std::ios::end);

	// We need to store the file size for a worst case scenario
	// RLE compression can increase the amount of data
	// depending on the image. (This scenario will only arise, in
	// an image with very few same pixel runs).
	int fileSize = (int)tgaFile.tellg();

	//std::cout << "Filesize: " << fileSize << " bytes" << std::endl;

	// Seek to version identifier (Always specified as being 18
	// characters from the end of the file)
	tgaFile.seekg(-18, std::ios::end);

	// Read version identifier
	char versionCheck[17] = "";
	tgaFile.read(versionCheck, 16);

	// Check version
	int version = 1;
	if (strcmp(versionCheck, "TRUEVISION-XFILE") == 0)
		version = 2;

	//std::cout << "TGA Version: " << version << std::endl;

	// Back to the beginning of the file
	tgaFile.seekg(0, std::ios::beg);

	// Read Header
	//std::cout << "Reading Header" << std::endl;

	// Need to read each field in one at a time since the structure padding likes
	// to eat the 4th and 10th bytes
	tgaFile.read(&tgaHeader.idLength, sizeof(tgaHeader.idLength));
	tgaFile.read(&tgaHeader.colourMapType, sizeof(tgaHeader.colourMapType));
	tgaFile.read(&tgaHeader.imageType, sizeof(tgaHeader.imageType));

	// If colourMapType is 0 and these 3 fields below are not 0, something may have went wrong
	tgaFile.read((char*)(&tgaHeader.firstEntry), sizeof(tgaHeader.firstEntry));
	tgaFile.read((char*)(&tgaHeader.numEntries), sizeof(tgaHeader.numEntries));
	tgaFile.read(&tgaHeader.bitsPerEntry, sizeof(tgaHeader.bitsPerEntry));


	tgaFile.read((char*)(&tgaHeader.xOrigin), sizeof(tgaHeader.xOrigin));
	tgaFile.read((char*)(&tgaHeader.yOrigin), sizeof(tgaHeader.yOrigin));
	tgaFile.read((char*)(&tgaHeader.width), sizeof(tgaHeader.width));
	tgaFile.read((char*)(&tgaHeader.height), sizeof(tgaHeader.height));
	tgaFile.read(&tgaHeader.bitsPerPixel, sizeof(tgaHeader.bitsPerPixel));
	tgaFile.read(&tgaHeader.descriptor, sizeof(tgaHeader.descriptor));

	header.width = tgaHeader.width;
	header.height = tgaHeader.height;

	// Output image header
	//std::cout << "ID LENGTH: " << (int)tgaHeader.idLength << std::endl;
	//std::cout << "CM TYPE: " << (int)tgaHeader.colourMapType << std::endl;
	//std::cout << "IMAGE TYPE: " << (int)tgaHeader.imageType << std::endl;
	//std::cout << "FIRST MAP ENTRY: " << tgaHeader.firstEntry << std::endl;
	//std::cout << "NUM MAP ENTRIES: " << tgaHeader.numEntries << std::endl;
	//std::cout << "BYTES PER ENTRY: " << (int)tgaHeader.bitsPerEntry << std::endl;
	//std::cout << "ORIGIN: " << tgaHeader.xOrigin << "," << tgaHeader.yOrigin << std::endl;
	//std::cout << "SIZE: " << tgaHeader.width << "," << tgaHeader.height << ":" << (int)tgaHeader.bitsPerPixel << std::endl;
	width = tgaHeader.width;
	height = tgaHeader.height;
	//std::cout << "DESCRIPTOR: " << (int)tgaHeader.descriptor << std::endl;*/
	return 0;
}

int Image::getWidth()
{
	return width;
}

int Image::getHeight()
{
	return height;
}
