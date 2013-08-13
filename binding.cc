#include <node.h>
#include <v8.h>
#include <string>
#include <iostream>
#include <sstream>
#include "wrapper.h"

using namespace v8;

// int bbb_enableADC();
Handle<Value> bind_enableADC(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 0) {
		ThrowException(Exception::TypeError(String::New("No arguments!")));
		return scope.Close(Undefined());
	}
	
	if (bbb_enableADC() < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_getADC(int id);
Handle<Value> bind_getADC(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || !args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int index = args[0]->Int32Value();
	return scope.Close(Int32::New(bbb_getADC(index)));
}

// int bbb_enableI2Cdevice(int bus, unsigned char address, char *module);
Handle<Value> bind_enableI2Cdevice(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsString() || !args[2]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	v8::String::Utf8Value addr_value(args[1]->ToString());
	v8::String::Utf8Value module(args[2]->ToString());
	
	int bus = args[0]->Int32Value();
	unsigned char addr = strtol(*addr_value, NULL, 0);

	if (bbb_enableI2Cdevice(bus, addr, *module) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_disableI2Cdevice(int bus, unsigned char address)
Handle<Value> bind_disableI2Cdevice(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	v8::String::Utf8Value addr_value(args[1]->ToString());
	
	int bus = args[0]->Int32Value();
	unsigned char addr = strtol(*addr_value, NULL, 0);

	if (bbb_disableI2Cdevice(bus, addr) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

Handle<Value> bind_getGpio(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = -1;

	if (args[0]->IsInt32()) {
		gpio = args[0]->Int32Value();
	} else {
		if (args[0]->IsString()) {
			v8::String::Utf8Value value(args[0]->ToString());
			gpio = bbb_getGpio(bbb_getIndexByStr(*value));
		} else {
			ThrowException(Exception::TypeError(String::New("Wrong argument!")));
			return scope.Close(Undefined());
		}
	}

	return scope.Close(Int32::New(gpio));
}

// int bbb_enableGpio(int gpio);
Handle<Value> bind_enableGpio(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();

	if (bbb_enableGpio(gpio) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_disableGpio(int gpio);
Handle<Value> bind_disableGpio(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();

	if (bbb_disableGpio(gpio) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setGpioDirection(int gpio, int direction);
Handle<Value> bind_setGpioDirection(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || args[0]->IsInt32() || args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();
	int direc = args[1]->Int32Value();
	direc = (direc == 0) ? 0 : 1;

	if (bbb_setGpioDirection(gpio, direc) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_getGpioDirection(int gpio);
Handle<Value> bind_getGpioDirection(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || !args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();
	int direc = -1;

	if ((direc = bbb_getGpioDirection(gpio)) < 0) {
		return scope.Close(Undefined());
	}

	return scope.Close(Int32::New(direc));
}

// int bbb_setGpioValue(int gpio, int value);
Handle<Value> bind_setGpioValue(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();
	int value = args[1]->Int32Value();

	value = (value == 0) ? 0 : 1;

	if (bbb_setGpioValue(gpio, value) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_getGpioValue(int gpio);
Handle<Value> bind_getGpioValue(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || !args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int gpio = args[0]->Int32Value();
	int value = -1;

	if ((value = bbb_getGpioValue(gpio)) < 0) {
		return scope.Close(False());
	}

	return scope.Close(Int32::New(value));
}

Handle<Value> bind_getHeader(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = -1;

	if (args[0]->IsInt32()) {
		header = args[0]->Int32Value();
	} else {
		if (args[0]->IsString()) {
			v8::String::Utf8Value value(args[0]->ToString());
			header = bbb_getHeader(bbb_getIndexByStr(*value));
		} else {
			ThrowException(Exception::TypeError(String::New("Wrong argument!")));
			return scope.Close(Undefined());
		}
	}

	return scope.Close(Int32::New(header));
}

Handle<Value> bind_getPin(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int pin = -1;

	if (args[0]->IsInt32()) {
		pin = args[0]->Int32Value();
	} else {
		if (args[0]->IsString()) {
			v8::String::Utf8Value value(args[0]->ToString());
			pin = bbb_getPin(bbb_getIndexByStr(*value));
		} else {
			ThrowException(Exception::TypeError(String::New("Wrong argument!")));
			return scope.Close(Undefined());
		}
	}

	return scope.Close(Int32::New(pin));
}

// int bbb_enablePwm(int header, int pin);
Handle<Value> bind_enablePwm(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();

	if (bbb_enablePwm(header, pin) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setPwmPeriod(int header, int pin, int time);
Handle<Value> bind_setPwmPeriod(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsInt32() || !args[2]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int time = args[2]->Int32Value();

	if (bbb_setPwmPeriod(header, pin, time) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setPwmDuty(int header, int pin, int time);
Handle<Value> bind_setPwmDuty(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsInt32() || !args[2]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int time = args[2]->Int32Value();

	if (bbb_setPwmDuty(header, pin, time) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setPwmHz(int header, int pin, char *hz);
Handle<Value> bind_setPwmHz(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsInt32() || !args[2]->IsString()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	v8::String::Utf8Value value(args[0]->ToString());

	if (bbb_setPwmHz(header, pin, *value) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setPwmPercent(int header, int pin, int duty);
Handle<Value> bind_setPwmPercent(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsInt32() || !args[2]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int duty = args[2]->Int32Value();

	if (bbb_setPwmPercent(header, pin, duty) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_setPwmPolarity(int header, int pin, int polarity);
Handle<Value> bind_setPwmPolarity(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 3 || !args[0]->IsInt32() || !args[1]->IsInt32() || !args[2]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int polarity = args[2]->Int32Value();

	if (bbb_setPwmPolarity(header, pin, polarity) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

// int bbb_getPwmPeriod(int header, int pin);
Handle<Value> bind_getPwmPeriod(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int ret = -1;

	if ((ret = bbb_getPwmPeriod(header, pin)) < 0) {
		return scope.Close(False());
	}

	return scope.Close(Int32::New(ret));
}

// int bbb_getPwmDuty(int header, int pin);
Handle<Value> bind_getPwmDuty(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int ret = -1;

	if ((ret = bbb_getPwmDuty(header, pin)) < 0) {
		return scope.Close(False());
	}

	return scope.Close(Int32::New(ret));
}

// char *bbb_getPwmHz(int header, int pin);
Handle<Value> bind_getPwmHz(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();

	return scope.Close(String::New(bbb_getPwmHz(header, pin)));
}

// int bbb_getPwmPercent(int header, int pin);
Handle<Value> bind_getPwmPercent(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int ret = -1;

	if ((ret = bbb_getPwmPercent(header, pin)) < 0) {
		return scope.Close(False());
	}

	return scope.Close(Int32::New(ret));
}

// int bbb_getPwmPolarity(int header, int pin);
Handle<Value> bind_getPwmPolarity(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 2 || !args[0]->IsInt32() || !args[1]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int header = args[0]->Int32Value();
	int pin = args[1]->Int32Value();
	int ret = -1;

	if ((ret = bbb_getPwmPolarity(header, pin)) < 0) {
		return scope.Close(False());
	}

	return scope.Close(Int32::New(ret));
}

//int bbb_enableSerial(int index);
Handle<Value> bind_enableSerial(const Arguments& args) {
	HandleScope scope;

	if (args.Length() != 1 || !args[0]->IsInt32()) {
		ThrowException(Exception::TypeError(String::New("Wrong argument!")));
		return scope.Close(Undefined());
	}

	int index = args[0]->Int32Value();

	if (bbb_enableSerial(index) < 0) {
		return scope.Close(False());
	}

	return scope.Close(True());
}

void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "enableADC", bind_enableADC);
	NODE_SET_METHOD(target, "getADC", bind_getADC);
	NODE_SET_METHOD(target, "enableI2Cdevice", bind_enableI2Cdevice);
	NODE_SET_METHOD(target, "disableI2Cdevice", bind_disableI2Cdevice);
	NODE_SET_METHOD(target, "getGpio", bind_getGpio);
	NODE_SET_METHOD(target, "enableGpio", bind_enableGpio);
	NODE_SET_METHOD(target, "disableGpio", bind_disableGpio);
	NODE_SET_METHOD(target, "setGpioDirection", bind_setGpioDirection);
	NODE_SET_METHOD(target, "getGpioDirection", bind_getGpioDirection);
	NODE_SET_METHOD(target, "setGpioValue", bind_setGpioValue);
	NODE_SET_METHOD(target, "getGpioValue", bind_getGpioValue);
	NODE_SET_METHOD(target, "getHeader", bind_getHeader);
	NODE_SET_METHOD(target, "getPin", bind_getPin);
	NODE_SET_METHOD(target, "enablePwm", bind_enablePwm);
	NODE_SET_METHOD(target, "setPwmPeriod", bind_setPwmPeriod);
	NODE_SET_METHOD(target, "setPwmDuty", bind_setPwmDuty);
	NODE_SET_METHOD(target, "setPwmHz", bind_setPwmHz);
	NODE_SET_METHOD(target, "setPwmPercent", bind_setPwmPercent);
	NODE_SET_METHOD(target, "setPwmPolarity", bind_setPwmPolarity);
	NODE_SET_METHOD(target, "getPwmPeriod ", bind_getPwmPeriod);
	NODE_SET_METHOD(target, "getPwmDuty", bind_getPwmDuty);
	NODE_SET_METHOD(target, "getPwmHz", bind_getPwmHz);
	NODE_SET_METHOD(target, "getPwmPercent", bind_getPwmPercent);
	NODE_SET_METHOD(target, "getPwmPolarity", bind_getPwmPolarity);
	NODE_SET_METHOD(target, "enableSerial", bind_enableSerial);
}

NODE_MODULE(bbb, init)
