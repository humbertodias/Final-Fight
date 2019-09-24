//
// Created by leandro on 10/9/19.
//
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>

#include "Locator.h"

using namespace std;
//using namespace xercesc;

Configuracion::Configuracion(const string &path) {
    try {
        xercesc::XMLPlatformUtils::Initialize();

        parser = new xercesc::XercesDOMParser();
        errHandler = (xercesc::ErrorHandler *) new xercesc::HandlerBase();
        parser->setIncludeIgnorableWhitespace(false);
        parser->setErrorHandler(errHandler);

        ifstream infile(path);

        if(infile.good()){
            parser->parse(path.c_str());
        }else{
            parser->parse(defaultPath.c_str());
        }
    }
    catch (const xercesc::SAXException &toCatch) {
        char *message = xercesc::XMLString::transcode(toCatch.getMessage());
        cout << "No se pudo abrir archivo de configuracion. Mensaje: \n"
             << message << "\n";
        xercesc::XMLString::release(&message);
    }
    catch (...) {
        cout << "No se pudo abrir archivo de configuracion.\n";
    }
}

Configuracion::~Configuracion() {
    delete parser;
    delete errHandler;
}

string Configuracion::getValue(const string &xPath, const string &defaultValue) {
    XMLCh *tag = xercesc::XMLString::transcode(("/configuracion" + xPath).c_str());

    xercesc::DOMXPathResult *result = parser->getDocument()->evaluate(
            tag,
            parser->getDocument()->getDocumentElement(),
            nullptr,
            xercesc::DOMXPathResult::ORDERED_NODE_SNAPSHOT_TYPE,
            nullptr);

    xercesc::XMLString::release(&tag);

    if (!result->getNodeValue()){
        return defaultValue;
    }

    char* finalValue = xercesc::XMLString::transcode(result->getNodeValue()->getFirstChild()->getNodeValue());
    result->release();

    std::string returnValue(finalValue);
    xercesc::XMLString::release(&finalValue);
    return returnValue;
}

int Configuracion::getIntValue(const string &xPath, int defaultValue) {
    string result = getValue(xPath, "");
    if(result.empty()){
        return defaultValue;
    }
    return stoi(result);
}

float Configuracion::getFloatValue(const string &xPath, float defaultValue) {
    string result = getValue(xPath, "");
    if(result.empty()){
        return defaultValue;
    }
    return stof(result);
}