#ifndef CODING_H
#define CODING_H

class Coding {
public:
	/* For any character c, encode(c) is a character different from c */
	static unsigned char encode(unsigned char c);

	/* For any character c, decode(encode(c)) == c */
	static unsigned char decode(unsigned char c);
};

#endif
