#include "tidyhtml_wrapper.hpp"
namespace epub 
{
    namespace html
    {


tidyhtml::tidyhtml()
{
    this->tdoc = tidyCreate();
    tidyOptSetBool( tdoc, TidyXhtmlOut, yes);
    tidyOptSetBool( tdoc, TidyForceOutput, yes);
    tidyOptSetBool( tdoc, TidyShowWarnings, no);
    tidyOptSetBool( tdoc, TidyQuiet, yes);
    tidyOptSetInt( tdoc, TidyShowErrors, 0);
    tidySetCharEncoding(tdoc, "utf8");
}
void tidyhtml::parse(std::string x, std::string path)
{
        tidySetErrorBuffer(tdoc, NULL);
        tidyParseString(tdoc, x.c_str());
        tidyCleanAndRepair( tdoc );
        tidyRunDiagnostics( tdoc );
        tidySaveFile(tdoc, path.c_str());


}
}
}
