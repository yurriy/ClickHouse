#include "ChangingColumnsBlockInputStream.h"


namespace DB
{

String ChangingColumnsBlockInputStream::getName() const
{
    return "ColumnsDescription";
}

Block ChangingColumnsBlockInputStream::getHeader() const
{
    Block block = input->getHeader();
    for (ColumnWithTypeAndName & column : block)
    {
        column_change(column);
    }
    return block;
}

Block ChangingColumnsBlockInputStream::readImpl()
{
    Block block = input->read();
    for (ColumnWithTypeAndName & column : block)
    {
        column_change(column);
    }
    return block;
}

}
