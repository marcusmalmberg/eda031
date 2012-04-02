#include <string>

#include "protocol.h"

using namespace std;

namespace protocol {
	string Protocol::getTextualError(const size_t errorCode) {
		switch(errorCode) {
		case ERR_NG_ALREADY_EXISTS: return "newsgroup already exists";
		case ERR_NG_DOES_NOT_EXIST: return "newsgroup does not exist";
		case ERR_ART_DOES_NOT_EXIST: return "article does not exist";
		default: return "undefined error";
		}
	}
}
