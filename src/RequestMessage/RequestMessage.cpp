#include "RequestMessage.hpp"
#include "utils.hpp"
#include <stdexcept>

RequestMessage::RequestMessage() : method_(NONE), bodyLength_(0), status_(REQ_INIT), metaConnection_(KEEP_ALIVE), metaContentLength_(0), metaTransferEncoding_(NONE_ENCODING) {}
RequestMessage::~RequestMessage() {}

EnumMethod RequestMessage::getMethod() const {
	return this->method_;
}

std::string RequestMessage::getTargetURI() const {
	return this->targetURI_;
}

RequestMessage::TypeField RequestMessage::getFields() const {
	return this->fieldLines_;
}

std::string RequestMessage::getBody() const {
	return this->body_;
}

size_t RequestMessage::getBodyLength() const {
	return this->bodyLength_;
}

void RequestMessage::setMethod(const EnumMethod &method) {
	this->method_ = method;
}

void RequestMessage::setTargetURI(const std::string &targetURI) {
	this->targetURI_ = targetURI;
}

void RequestMessage::addFieldLine(const std::string &name, const std::vector<std::string> &values) {
	if (this->fieldLines_.find(name) == this->fieldLines_.end())
		this->fieldLines_[name] = values;
	else {
		std::vector<std::string> &finded = this->fieldLines_[name];
		finded.insert(finded.end(), values.begin(), values.end());
	}
}

void RequestMessage::addBody(const std::string &bodyData) {
	this->body_.append(bodyData);
	this->bodyLength_ += bodyData.length();
}

EnumReqStatus RequestMessage::getStatus() const {
	return this->status_;
}

std:: string RequestMessage::getMetaHost() const {
	return this->metaHost_;
}

EnumConnection RequestMessage::getMetaConnection() const {
	return this->metaConnection_;
}

size_t RequestMessage::getMetaContentLength() const {
	return this->metaContentLength_;
}

EnumTransEnc RequestMessage::getMetaTransferEncoding() const {
	return this->metaTransferEncoding_;
}

std::string RequestMessage::getMetaContentType() const {
	return this->metaContentType_;
}

void RequestMessage::setStatus(const EnumReqStatus &status) {
	this->status_ = status;
}

void RequestMessage::setMetaHost(const std::string &value) {
	this->metaHost_ = value;
}

void RequestMessage::setMetaConnection(const EnumConnection &value) {
	this->metaConnection_ = value;
}

void RequestMessage::setMetaContentLength(const size_t &value) {
	this->metaContentLength_ = value;
}

void RequestMessage::setMetaTransferEncoding(const EnumTransEnc &value) {
	this->metaTransferEncoding_ = value;
}

void RequestMessage::setMetaContentType(const std::string &value) {
	this->metaContentType_ = value;
}

// Parser 구현 후, 파싱 테스트용 함수, C++98 X
#include <iostream>
#include <iterator>
void RequestMessage::printResult() const {
	std::cout << "\033[32;7m StartLine :\033[0m"<<std::endl;
	std::cout <<"\033[37;2mmethod: \033[0m";
	const char *method;
	switch (this->method_) {
		case NONE:
			method = "NONE";
			break;
		case GET:
			method = "GET";
			break;
		case POST:
			method = "POST";
			break;
		case DELETE:
			method = "DELETE";
			break;
	}
	std::cout <<method<<";"<<std::endl;
	
	std::cout <<"\033[37;2muri: \033[0m";
	std::cout <<this->targetURI_<<";"<<std::endl;
	this->printFields();
	this->printBody();
	this->printMetaData();
}

void RequestMessage::printFields(void) const {
	std::cout << "\033[32;7m Fields :\033[0m"<< std::endl;
	for (std::map<std::string, std::vector<std::string> >::const_iterator it = this->fieldLines_.begin(); it != this->fieldLines_.end(); ++it) {
		int cnt = 0;
		std::cout << it->first << ": {";
		for (std::vector<std::string>::const_iterator itt = it->second.begin(); itt != it->second.end(); ++itt) {
			if (cnt != 0)
				std::cout << ", ";
			std::cout << *itt;
			cnt++;
		}
		std::cout <<"};"<< std::endl;
	}
}

void RequestMessage::printBody(void) const {
	std::cout << "\033[32;7m Body :\033[0m"<< std::endl;
	std::cout << "\033[37;2mcount: " << this->body_.length() << "\033[0m\n";
	for (std::string::const_iterator it = this->body_.begin(); it != this->body_.end(); ++it) {
		if (*it == '\n')
			std::cout << "\\n" << std::endl;
		else if (*it == '\r')
			std::cout << "\\r";
		else
			std::cout << *it;
	}
}
void RequestMessage::printMetaData(void) const {
	std::cout << "\033[37;7m MetaData :\033[0m"<<std::endl;
	std::cout <<"\033[37;2mHost_: "<<this->metaHost_ <<";\033[0m\n";
	std::cout <<"\033[37;2mConnection_: ";
	const char *connection;
	switch (this->metaConnection_) {
		case KEEP_ALIVE:
			connection = "keep-alive";
		case CLOSE:
			connection = "close";
	}
	std::cout<<connection <<";\033[0m\n";
	std::cout <<"\033[37;2mContentLength_: "<<this->metaContentLength_ <<";\033[0m\n";
}