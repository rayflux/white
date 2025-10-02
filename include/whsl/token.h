#pragma once

#include <type.h>

#include <string>

namespace white::whsl {

enum class TokenType {
	OP_GT,
	NUMBER,
};

struct Token {
	TokenType _Type;
	u32 _LineNo;
	std::string _Lexeme;
};

}  // namespace white::whsl
