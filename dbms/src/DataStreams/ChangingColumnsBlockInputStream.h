#include "IBlockInputStream.h"
#include <Storages/ColumnsDescription.h>


namespace DB
{

class ChangingColumnsBlockInputStream : public IBlockInputStream
{
public:
    ChangingColumnsBlockInputStream(const BlockInputStreamPtr & input, const std::function<void(ColumnWithTypeAndName &)> & column_change)
        : input(input), column_change(column_change)
    {
    }

    String getName() const override;
    Block getHeader() const override;

protected:
    Block readImpl() override;

private:
    BlockInputStreamPtr input;
    std::function<void(ColumnWithTypeAndName &)> column_change;
};

}
