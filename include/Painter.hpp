#include "Field.hpp"
#include "Structs.hpp"

class Painter {
    public:
        void printCellValue(Field self, Coordinate coordinate) const;
        void printField(Field self) const;
        void printFields(Field self, Field other) const;
};