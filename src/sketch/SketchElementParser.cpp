#include "SketchElementParser.h"
#include "StyleMap.h"
#include "TransformParser.h"
#include "SketchElement.h"
#include "Parser.h"

#include "../tinyxml/tinyxml.h"

#include "../core/LogManager.h"
using namespace jvgs::core;

#include "../math/AffineTransformationMatrix.h"
using namespace jvgs::math;

using namespace std;

namespace jvgs
{
    namespace sketch
    {
        SketchElementParser::SketchElementParser(Parser *parser)
        {
            this->parser = parser;
        }

        SketchElementParser::~SketchElementParser()
        {
        }

        Parser *SketchElementParser::getParser() const
        {
            return parser;
        }

        void SketchElementParser::parseStyle(SketchElement *sketchElement,
                TiXmlElement *element)
        {
            StyleMap *styleMap = sketchElement->getStyleMap();
            if(element->Attribute("fill"))
                styleMap->setValue("fill", element->Attribute("fill"));
            if(element->Attribute("stroke"))
                styleMap->setValue("stroke", element->Attribute("stroke"));
        }

        void SketchElementParser::parseTransform(SketchElement *sketchElement,
                const std::string &data)
        {
            TransformParser *tranformParser = new TransformParser();
            AffineTransformationMatrix matrix = tranformParser->parse(data);
            sketchElement->setMatrix(matrix);
            delete tranformParser;
        }
    }
}