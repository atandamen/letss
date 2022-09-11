#pragma once

constexpr bool IsWinHandleValid(HANDLE h) {
	return h && h != INVALID_HANDLE_VALUE;
}
