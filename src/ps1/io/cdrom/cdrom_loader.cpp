#include "ps1/io/cdrom/cdrom.hpp"

#include <cstdlib>
#include <cstdio>

#include "utils/error.hpp"

uint8_t Disc::intToBcd(uint8_t value) {
    return ((value / 10) << 4) | (value % 10);
}

int Disc::putAddressInTrack(Track *track, uint32_t address) {
	if (!track) {
		return ERR_INVALID_ARGUMENT;
	}

    uint8_t minutes = address / (60 * 75);
    address %= 60 * 75;

    uint8_t seconds = address / 75;
    uint8_t frames = address % 75;

	track->minute = intToBcd(minutes);
	track->second = intToBcd(seconds);
	track->frame = intToBcd(frames);

	return ERR_OK;
}

Track *Disc::createTrack(uint32_t id, uint32_t address) {
	Track *track = (Track *)malloc(sizeof(Track));

	track->id = id;
	track->index = 0;
	int ret = putAddressInTrack(track, address);
	
	if (ret != ERR_OK) {
		free(track);
		return NULL;
	}

	return track;
}

int Disc::destroyTracks() {
	if (!tracks) {
		return ERR_OK;
	}

	for (uint32_t i = 0; i < nbTrack && tracks[i]; i++) {
		free(tracks[i]);
	}

	free(tracks);

	return ERR_OK;
}

int Disc::createTracks() {
	tracks = (Track **)malloc(nbTrack * sizeof(Track *));

    for (uint32_t i = 0; i < nbTrack && tracks[i]; i++) {
		tracks[i] = NULL;
    }

	for (uint32_t i = 0; i < nbTrack; i++) {
		Track *currentTrack = createTrack(i, 0); // TODO: parse .cue to have every addresses
		
		if (!currentTrack) {
			destroyTracks();
			return ERR_UNEXPECTED_RESULT;
		}

		tracks[i] = currentTrack;
	}

	return ERR_OK;
}

int Disc::load(const char *filename) { // TODO handle multiple tracks
    std::FILE *file;

    file = fopen(filename, "r");

    if (!file) {
        printf("Error: Disc::Load, Can't read this file\n");
        return ERR_FILE_NOT_FOUND;
    }

    fseek(file, 0, SEEK_END); // Get the file size
    long int size = ftell(file);
    rewind(file);

	maxAddress = size - 1;
	nbSector = size / sectorSize;
	data = (uint8_t *)calloc(sectorSize * nbSector, sizeof(uint8_t));

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
	nbTrack = 1;
	
	int ret = createTracks();

    if (ret != ERR_OK) {
        return; // TODO: handle error
    }

	currentTrack = tracks[0]; // TODO change

	ret = load("src/ps1/roms/games/Final Fantasy VI.bin"); // Update nbSector, maxAddress and data

	if (ret != ERR_OK) {
		return;
	}

	return;
};

Disc::~Disc() {
	free(data);
	destroyTracks();

	return;
};

uint8_t Disc::read(uint32_t address) {
	return data[address];
}

uint32_t Disc::getMaxAddress() {
	return maxAddress;
}

Track *Disc::getCurrentTrack() {
	return currentTrack;
}
