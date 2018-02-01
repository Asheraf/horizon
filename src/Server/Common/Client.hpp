//
// Created by SagunKho on 31/01/2018.
//

#ifndef HORIZON_CLIENT_HPP
#define HORIZON_CLIENT_HPP

#ifndef CHAR_NAME_LENGTH
	#define CHAR_NAME_LENGTH 24
#endif

#ifndef CLIENT_EMAIL_LENGTH
	#define CLIENT_EMAIL_LENGTH 40
#endif

#ifndef MAP_NAME_LENGTH
	// For Map Names, which the client considers to be 16 in length including the .gat extension.
	#define MAP_NAME_LENGTH (11 + 1)
	#define MAP_NAME_LENGTH_EXT (MAP_NAME_LENGTH + 4)
#endif

#endif //HORIZON_CLIENT_HPP
