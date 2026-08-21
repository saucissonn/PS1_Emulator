#include "ps1/io/cdrom/cdrom.hpp"

#include <cstdlib>
#include <cstdio>

#include "utils/error.hpp"

int Disc::load(const char *filename) {
    std::FILE *file;

    file = fopen(filename, "r");

    if (!file) {
        printf("Error: Disc::Load, Can't read this file\n");
        return ERR_FILE_NOT_FOUND;
    }

    fseek(file, 0, SEEK_END); // Get the file size
    long int size = ftell(file);
    rewind(file);

	nbSector = size / sectorSize;

    fread(data, sizeof(uint8_t), size, file);
/*  // To debug
    for (int i = 0; i < size && i < 1000; i++) {
        printf("%3d: %02X\n", i, data[i]);
    }
*/
    fclose(file);

    return ERR_OK;
}

Disc::Disc() {
	sectorSize = 2352;
	nbSector = 1;
	data = (uint8_t *)calloc(sectorSize * nbSector, sizeof(uint8_t));

	int ret = load("src/ps1/roms/games/Final Fantasy VI.bin"); // Update nbSector and data

	if (ret != ERR_OK) {
		return; // TODO: handle error
	}

	return;
};

Disc::~Disc() {
	free(data);

	return;
};

uint8_t Disc::read(uint32_t address) {
	return data[address];
}
