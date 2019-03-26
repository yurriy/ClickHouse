#pragma once

#include <Columns/IColumn.h>
#include <DataTypes/IDataType.h>


namespace DB
{

class WriteBuffer;


/** Column data along with its data type and name.
  * Column data could be nullptr - to represent just 'header' of column.
  * Name could be either name from a table or some temporary generated name during expression evaluation.
  */

struct ColumnWithTypeAndName
{
    ColumnPtr column;
    DataTypePtr type;
    String name;
    String orig_name;
    String table;
    String orig_table;
    String database;

    ColumnWithTypeAndName() {}
    ColumnWithTypeAndName(const ColumnPtr & column_, const DataTypePtr & type_, const String & name_)
        : column(column_), type(type_), name(name_) {}

    /// Creates column with data from the first argument and type and metadata from the second argument
    ColumnWithTypeAndName(ColumnPtr column_raw, const ColumnWithTypeAndName & empty_column)
        : column(std::move(column_raw))
        , type(empty_column.type)
        , name(empty_column.name)
        , orig_name(empty_column.orig_name)
        , table(empty_column.table)
        , orig_table(empty_column.orig_table)
        , database(empty_column.database)
    {
    }

    /// Uses type->createColumn() to create column
    ColumnWithTypeAndName(const DataTypePtr & type_, const String & name_)
        : column(type_->createColumn()), type(type_), name(name_) {}

    ColumnWithTypeAndName cloneEmpty() const;
    bool operator==(const ColumnWithTypeAndName & other) const;

    void dumpStructure(WriteBuffer & out) const;
    String dumpStructure() const;
};

}
