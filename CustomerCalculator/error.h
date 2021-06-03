#pragma once

typedef struct {
	unsigned int err_code;
	unsigned int err_position;
	char err_msg[16];
} CalcError;