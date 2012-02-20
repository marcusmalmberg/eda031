#include "coding.h"

unsigned char Coding::encode(unsigned char c) {
	return c + 1;
}

unsigned char Coding::decode(unsigned char c) {
	return c - 1;
}
