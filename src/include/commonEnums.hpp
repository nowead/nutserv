#ifndef COMMON_ENUMS_HPP
#define COMMON_ENUMS_HPP

typedef enum EnumSessionStatus {
	REQUEST_ERROR,
	READ_CONTINUE,
	READ_COMPLETE,
	WRITE_CONTINUE,
	WRITE_COMPLETE,
	CONNECTION_CLOSED
} EnumSesStatus;

enum EnumEvent {
	READ_EVENT,
	WRITE_EVENT,
	EXCEPTION_EVENT,
	UNKNOWN_EVENT
};

#endif
