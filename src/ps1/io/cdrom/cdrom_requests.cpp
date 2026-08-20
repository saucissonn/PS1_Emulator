#include "ps1/io/cdrom/cdrom.hpp"

#include "utils/error.hpp"

// Requests

uint8_t Cdrom::readRequest() {
	switch (index) {
		case 0:
			return interruptEnable;

		case 1:
			return interruptFlag;

		case 2:
			return interruptEnable;

		case 3:
			return interruptFlag;
	}

	return 0;
}

int Cdrom::writeRequest(uint8_t value) {
    switch (index) {
        case 0:
            request = value;
            return ERR_OK;

        case 1:
            interruptFlag = value;
            return ERR_OK;
    
        case 2:
            return ERR_OK; // Audio volume apply changes

        case 3:
            interruptFlag = value; 
            return ERR_OK;
    }

    return ERR_UNEXPECTED_RESULT;
}

